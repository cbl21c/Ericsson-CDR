#!/usr/bin/python

import sys
from cme20MSS14b import componentHash
from primitives import *

######################
#  global variables  #
######################

# starting column to print field values
FIELD_START = 48


# encoding P/C
PRIMITIVE   = 0
CONSTRUCTOR = 1
encodeName = ['Primitive', 'Constructor']

# define the attributes of end-of-contents
EOC = [0, 0, 0, 0]

CLASS_SHIFT  = 6
ENCODE_SHIFT = 5
CLASSNUM_MASK = 0x1f

BITS7_MASK = 0x7f
BIT8_SHIFT = 7

HIGH_CLASS_NUM = 0x1f


##############################
#   getId()                  #
##############################
def getId(data):
    ptr = 0
    bytesConsumed = 1

    initial = data[ptr]
    asnClass = initial >> CLASS_SHIFT
    encode = (initial >> ENCODE_SHIFT) % 2
    classNum = initial & CLASSNUM_MASK

    if classNum == HIGH_CLASS_NUM:
        classNum = 0
        endOfBytes = False
        ptr = ptr + 1
        while not endOfBytes:
            bytesConsumed = bytesConsumed + 1
            byte = data[ptr] & BITS7_MASK
            classNum = classNum * 128 + byte
            if data[ptr] >> BIT8_SHIFT == 0:
                endOfBytes = True
            ptr = ptr + 1

    return (asnClass, encode, classNum, bytesConsumed)


##############################
#   getLength()              #
##############################
def getLength(data):
    bytesConsumed = 1
    initial = data[0]

    # definite short form
    if initial >> BIT8_SHIFT == 0:
        return (initial, bytesConsumed)

    length = 0
    nbytes = initial & BITS7_MASK

    # indefinite form
    if nbytes == 0:
        return (nbytes, bytesConsumed)

    # definite long form
    for ptr in range(1, nbytes + 1):
        length = length * 256 + data[ptr]

    bytesConsumed = bytesConsumed + nbytes

    return (length, bytesConsumed)


############################################################
#   cdr class definition                                   #
############################################################
class cdr:
    def __init__(self, data):
        if data is None:
            return None

        self.ptr = 0
        self.data = data
        self.asnlength = len(self.data)
        self.depth = 0
        self.stack = []

    def nextTag(self):
        # return current object and move to next one
        # should return (class, pc, classnum, length, contents, depthIn, depthOut)

        # check if already at end of data
        if self.ptr >= self.asnlength:
            return None

        ptr = self.ptr
        length = 0
        contents = []
        depthIn = self.depth

        # tag
        (asnClass, pc, classNum, bytesTag) = getId(self.data[ptr:])
        ptr = ptr + bytesTag

        # length
        (length, bytesLength) = getLength(self.data[ptr:])
        ptr = ptr + bytesLength

        # deduct the number of bytes consumed from the constructor sizes
        # any negative values in the stack will mark constructors with indefinite length
        self.stack = [x - (bytesTag + bytesLength) for x in self.stack]

        if pc == CONSTRUCTOR:
        # if tag is a constructor, push its length onto the stack
            self.depth = self.depth + 1
            self.stack.append(length)
        elif [asnClass, pc, classNum, length] == EOC:
        # check for end-of-contents
            # assert(self.stack[-1] <= 0)
            del self.stack[-1]
            self.depth = self.depth - 1
        else:
        # just a normal primitive
            # deduct the object length from the constructor sizes
            self.stack = [x - length for x in self.stack]

            # isolate the contents
            if length > 0:
                contents = self.data[ptr:ptr + length]

            # check if we have reached the end of each constructor 
            n = len(self.stack) - 1
            while n >= 0 and self.stack[n] == 0:
                del self.stack[-1]
                self.depth = self.depth - 1
                n = n - 1

        # point to next object
        self.ptr = self.ptr + bytesTag + bytesLength
        if pc == PRIMITIVE:
            self.ptr = self.ptr + length

        # adjust any negative value in stack back to zero
        for n in range(len(self.stack)):
            if self.stack[n] < 0:
                self.stack[n] = 0

        depthOut = self.depth
        progress = float(self.ptr) / self.asnlength

        return (asnClass, pc, classNum, length, contents, depthIn, depthOut, progress)

    def decode(self):
        # go through the asn1 tags to decode the cdr
        self.ptr = 0
        self.depth = 0
        self.nameStack = ['root']
        self.componentList = componentHash['root']

        output = ''
        fields = self.nextTag()
        while fields is not None:
            (asnClass, pc, classNum, length, contents, depthIn, depthOut, progress) = fields

            # get the current tag name
            name = self.componentList[classNum]

            if pc == CONSTRUCTOR:
            # if tag is a constructor, push its name onto the stack
                indent = '  ' * depthIn
                output = output + indent + name + '\n'

                # components bCSMTDPData and triggerData need to be modified before pushing on stack
                if name.find('bCSMTDPData') == 0:
                    name = 'CAMELTDPData'
                if name.find('triggerData') == 0:
                    name = 'triggerData'

                self.nameStack.append(name)

                # entering a new constructor, so the componentList must be updated
                self.componentList = componentHash[name]

            elif [asnClass, pc, classNum, length] == EOC:
            # if end-of-contents element, pop one item off stack
                del self.nameStack[-1]
                key = self.nameStack[-1]
                self.componentList = componentHash[key]
            else:
            # for a primitive, print the tag name and value
                indent = '  ' * depthIn
                trail = ' ' * (FIELD_START - len(name) - depthIn * 2)
                output = output + indent + name

                # name is a key to the hash table which maps each primitive type
                # to the function that displays its value
                display = parameterMap[name]
                if display is not None:
                    output = output + trail
                    val = display(contents)
                    output = output + '%s' % val
                output = output + '\n'

                # check if we have reached the end of any constructor
                if len(self.nameStack) > depthOut + 1:
                    self.nameStack = self.nameStack[:depthOut + 1]
                    # exited one or more constructors, so the componentList must be updated
                    key = self.nameStack[-1]
                    self.componentList = componentHash[key]

                # next record is a new cdr so print a blank line to separate it
                if depthOut <= 1 and depthIn > depthOut:
                    output = output + '\n'

            fields = self.nextTag()

        return output


############################################################
#   cdrfile class definition                               #
############################################################
class cdrfile:
    def __init__(self, fname):
        try:
            # open the file and read its contents
            with open(fname, 'rb') as infile:
                self.data = bytearray(infile.read())
                infile.close()
        except IOError:
            sys.stderr.write('cdrfile(): Could not open file %s\n' % fname)
            sys.exit(-1)

        if self.data is not None:
            self.asnlength = len(self.data)

        # build a list of cdr pointers and lengths
        self.cdrPointer = []
        self.cdrLength  = []

        ptr = 0
        self.num_cdr = 0
        while ptr < self.asnlength:
            self.cdrPointer.append(ptr)

            (asnClass, pc, classNum, bytesConsumed) = getId(self.data[ptr:])
            objectlen = bytesConsumed
            ptr = ptr + bytesConsumed
            (length, bytesConsumed) = getLength(self.data[ptr:])

            if length > 0:
                objectlen = objectlen + bytesConsumed + length
                ptr = ptr + bytesConsumed + length
                self.cdrLength.append(objectlen)
            else:
                # indefinite form for length
                # assuming objects with indefinite form are not nested
                while [asnClass, pc, classNum, length] != EOC:
                    objectlen = objectlen + bytesConsumed + length
                    ptr = ptr + bytesConsumed + length

                    # get the next tag
                    (asnClass, pc, classNum, bytesConsumed) = getId(self.data[ptr:])
                    objectlen = objectlen + bytesConsumed
                    ptr = ptr + bytesConsumed

                    # get the next tag's length
                    (length, bytesConsumed) = getLength(self.data[ptr:])

                objectlen = objectlen + bytesConsumed
                ptr = ptr + bytesConsumed
                self.cdrLength.append(objectlen)

            self.num_cdr = self.num_cdr + 1

    def getCdr(self, index):
        if index >= 0 and index < self.num_cdr:
            pos = self.cdrPointer[index]
            length = self.cdrLength[index]
            cdrData = self.data[pos:pos + length]
            return cdr(cdrData)
        else:
            return None

    def dump(self):
        output = ''
        for n in range(self.num_cdr):
            cdr = self.getCdr(n)
            text = cdr.decode()
            output = output + text

        return output



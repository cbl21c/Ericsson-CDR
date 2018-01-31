#!/usr/bin/python

######################
#  global variables  #
######################

# ASN.1 class
UNIVERSAL   = 0
APPLICATION = 1
CONTEXT     = 2
PRIVATE     = 3
className = ['Universal', 'Application', 'Context-specific', 'Private']

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
#   class definition                                       #
############################################################
class asn1Object:
    # class variables go here

    def __init__(self, data=None):
        self.ptr = 0

        self.data = data
        self.asnlength = 0
        if data is not None:
            self.asnlength = len(data)

        self.depth = 0
        self.stack = []


##############################
#   first()                  #
##############################
    def first(self):
        # re-initialise variables to start decoding
        self.ptr = 0
        self.depth = 0
        self.stack = []


##############################
#   next()                   #
##############################
    def next(self):
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
            # check if we have reached the end of each constructor 
            n = len(self.stack) - 1
            while n >= 0 and self.stack[n] <= 0:
                del self.stack[-1]
                self.depth = self.depth - 1
                n = n - 1
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


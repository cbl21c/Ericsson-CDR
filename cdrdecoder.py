#!/usr/bin/python

import sys
import asn1
import argparse
from ericsson.cme20MSS14b import componentHash
from ericsson.primitives import *

# starting column to print field values
FIELD_START = 48


# instantiate an argument parser
parser = argparse.ArgumentParser(description = "Ericsson MSC CDR decoder")

# add a positional argument for the input file
parser.add_argument("infile", help="CDR file")


# parse the arguments
args = parser.parse_args()
fname = args.infile

try:
    with open(fname, 'rb') as cdrfile:
        data = bytearray(cdrfile.read())
        cdrfile.close()
except IOError:
    sys.stderr.write('Could not open file %s\n' % fname)
    sys.exit()


# instantiate an asn1 object
cdr = asn1.asn1Object(data)

stack = ['root']
componentList = componentHash['root']

cdr.first()
fields = cdr.next()
while fields is not None:
    (asnClass, pc, classNum, length, contents, depthIn, depthOut) = fields

    # get the current tag name
    name = componentList[classNum]

    if pc == asn1.CONSTRUCTOR:
    # if tag is a constructor, push its name onto the stack
        indent = '  ' * depthIn
        sys.stdout.write(indent + name + '\n')

        # components bCSMTDPData and triggerData need to be modified before pushing on stack
        if name.find('bCSMTDPData') == 0:
            name = 'CAMELTDPData'
        if name.find('triggerData') == 0:
            name = 'triggerData'

        stack.append(name)

        # entering a new constructor, so the componentList must be updated
        componentList = componentHash[name]

    elif [asnClass, pc, classNum, length] == asn1.EOC:
    # if end-of-contents element, pop one item off stack
        del stack[-1]
        key = stack[-1]
        componentList = componentHash[key]
    else:
    # for a primitive, print the tag name and value
        indent = '  ' * depthIn
        trail = ' ' * (FIELD_START - len(name) - depthIn * 2)
        sys.stdout.write(indent + name)

        display = parameterMap[name]
        if display is not None:
            sys.stdout.write(trail)
            display(contents)
        sys.stdout.write('\n')

        # check if we have reached the end of any constructor
        if len(stack) > depthOut + 1:
            stack = stack[:depthOut + 1]
            # exited one or more constructors, so the componentList must be updated
            key = stack[-1]
            componentList = componentHash[key]

        # next record is a new cdr so print a blank line to separate it
        if depthOut <= 1 and depthIn > depthOut:
            sys.stdout.write('\n')

    fields = cdr.next()



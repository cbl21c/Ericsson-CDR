#!/usr/bin/python

import os
import sys
import asn1
import argparse
from ericsson.cme20MSS14b import componentHash
from ericsson.primitives import *

# starting column to print field values
FIELD_START = 48
PROGRESS_BAR_MIN = 10


# instantiate an argument parser
parser = argparse.ArgumentParser(description='Ericsson MSC CDR decoder')

# optional arguments for:
#   output file (use stdout if not given)
#   progress bar display
#   CDR numbering
parser.add_argument('-o', dest='outfile', help='output file')
parser.add_argument('--number', action='store_true', help='number CDRs in output')
parser.add_argument('--bar', action='store_true', help='display progress bar')

# add a positional argument for the input file
parser.add_argument('infile', help='CDR file')

# parse the arguments
args = parser.parse_args()


# try to open the input file
try:
    with open(args.infile, 'rb') as cdrfile:
        data = bytearray(cdrfile.read())
        cdrfile.close()
except IOError:
    sys.stderr.write('Could not open file %s\n' % args.infile)
    sys.exit()

# default to stdout for output
outfile = sys.stdout

# if an output file is specified try to open it
if args.outfile:
    try:
        outfile = open(args.outfile, 'w')
    except IOError:
        sys.stderr.write('Could not open file %s\n' % args.outfile)
        sys.exit()
else:
    # if stdout is used, the progress bar cannot be displayed
    args.bar = False


# get the current terminal column size to see if we can display a progress bar
# number of useable columns (subtract 2 for brackets, 4 for number%, 2 for space)
fields = os.popen('stty size', 'r').read().split()
cols = int(fields[1]) - 8
full = '=' * (cols - 1) + '>'
quant = 1 / float(cols)
level = 0
nbar = -1

# instantiate an asn1 object
cdr = asn1.asn1Object(data)
cdrCount = 1

stack = ['root']
componentList = componentHash['root']

cdr.first()
fields = cdr.next()
while fields is not None:
    (asnClass, pc, classNum, length, contents, depthIn, depthOut, progress) = fields

    # get the current tag name
    name = componentList[classNum]

    if pc == asn1.CONSTRUCTOR:
    # if tag is a constructor, push its name onto the stack
        if args.number and depthIn == 0:
            outfile.write('[%d]\n' % cdrCount)
            cdrCount = cdrCount + 1

        indent = '  ' * depthIn
        outfile.write(indent + name + '\n')

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
        outfile.write(indent + name)

        # name is a key to the hash table which maps each primitive type
        # to the function that displays its value
        display = parameterMap[name]
        if display is not None:
            outfile.write(trail)
            val = display(contents)
            outfile.write('%s' % val)
        outfile.write('\n')

        # check if we have reached the end of any constructor
        if len(stack) > depthOut + 1:
            stack = stack[:depthOut + 1]
            # exited one or more constructors, so the componentList must be updated
            key = stack[-1]
            componentList = componentHash[key]

        # next record is a new cdr so print a blank line to separate it
        if depthOut <= 1 and depthIn > depthOut:
            outfile.write('\n')

    if args.bar:
        percent = int(progress * 100 + 0.5)

        if progress >= level:
            if cols >= PROGRESS_BAR_MIN:
                nbar = nbar + 1
                if nbar > 0:
                    bar = full[-nbar:]
                else:
                    bar = ''
                spaces = ' ' * (cols - len(bar))
                sys.stderr.write('\r[%s%s] %d%%' %(bar, spaces, percent))
            else:
                sys.stderr.write('\r%d%%' % percent)

            sys.stderr.flush()
            level = level + quant

    fields = cdr.next()

# when decoding finished, print a newline if progress bar was used
if args.bar:
    sys.stderr.write('\n')



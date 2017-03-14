#!/usr/bin/python

import os
import sys
import asn1
import universal
import argparse

# starting column to print field values
FIELD_START = 48
PROGRESS_BAR_MIN = 10


# instantiate an argument parser
parser = argparse.ArgumentParser(description='Generic ASN.1 decoder')

# optional arguments for:
#   output file (use stdout if not given)
#   progress bar display
parser.add_argument('-o', dest='outfile', help='output file')
parser.add_argument('--bar', action='store_true', help='display progress bar')

# add a positional argument for the input file
parser.add_argument('infile', help='ASN.1 file')

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

cdr.first()
fields = cdr.next()
while fields is not None:
    (asnClass, pc, classNum, length, contents, depthIn, depthOut, progress) = fields

    # get the current tag name
    if asnClass == asn1.UNIVERSAL:
        name = universal.tag[classNum]
    else:
        name = '[%s %d]' %(asn1.className[asnClass], classNum)
        display = None

    if pc == asn1.CONSTRUCTOR:
    # if tag is a constructor, write its name with a newline char
        indent = '  ' * depthIn
        outfile.write(indent + name + '\n')

    elif [asnClass, pc, classNum, length] == asn1.EOC:
    # if end-of-contents element, don't need to do anything
        pass
    else:
    # for a primitive, print the tag name and value
        indent = '  ' * depthIn
        trail = ' ' * (FIELD_START - len(name) - depthIn * 2)
        outfile.write(indent + name)

        # name is a key to the hash table which maps each primitive type
        # to the function that displays its value
        display = None
        if name in universal.parameterMap:
            display = universal.parameterMap[name]

        if display is not None:
            outfile.write(trail)
            val = display(contents)
            outfile.write('%s' % val)
        outfile.write('\n')

        # next record is a new cdr so print a blank line to separate it
        if depthOut == 0:
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



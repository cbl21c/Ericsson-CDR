#!/usr/bin/python

import os
import sys
import asn1
import argparse
import cypher
from ericsson.cme20MSS14b import componentHash
from ericsson.primitives import *

AU = '61'

# set of parameters used for subscriber numbers
subscriberSet = ['calledPartyNumber', 'callingPartyNumber', 'destinationAddress', 'originatingAddress']


##############################
#  main()                    #
##############################

# instantiate an argument parser
parser = argparse.ArgumentParser(description='Ericsson MSC CDR decoder')

# optional arguments for:
#   output file (use stdout if not given)
#   progress bar display
#   CDR numbering
parser.add_argument('-o', dest='outfile', help='output file')

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

#
# lists for later use...
#
commands = []
subscriberList = []


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
        # components bCSMTDPData and triggerData need to be modified before pushing on stack
        if name.find('bCSMTDPData') == 0:
            name = 'CAMELTDPData'
        if name.find('triggerData') == 0:
            name = 'triggerData'

        stack.append(name)

        # entering a new constructor, so the componentList must be updated
        componentList = componentHash[name]

        # create a new cdr object
        if name == 'mSOriginatingSMSinMSC':
            record = cypher.mSOriginatingSMSinMSC()
        elif name == 'mSTerminatingSMSinMSC':
            record = cypher.mSTerminatingSMSinMSC()

    elif [asnClass, pc, classNum, length] == asn1.EOC:
    # if end-of-contents element, pop one item off stack
        del stack[-1]
        key = stack[-1]
        componentList = componentHash[key]
    else:
    # for a primitive, print the tag name and value
        # name is a key to the hash table which maps each primitive type
        # to the function that displays its value
        display = parameterMap[name]
        if display is not None:
            val = display(contents)
            if name in subscriberSet:
                msisdn = cypher.normalise(val, AU)
                if msisdn not in subscriberList:
                    subscriberList.append(msisdn)

        # update the cdr object
        if record is not None:
            record.set(name, val)

        # check if we have reached the end of any constructor
        if len(stack) > depthOut + 1:
            stack = stack[:depthOut + 1]
            # exited one or more constructors, so the componentList must be updated
            key = stack[-1]
            componentList = componentHash[key]

        # next record is a new cdr so print a blank line to separate it
        if depthOut <= 1 and depthIn > depthOut:
            if record is not None:
                command = record.cypher()
                print command
                record = None

    fields = cdr.next()



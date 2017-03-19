#!/usr/bin/python

import sys
import argparse
import ericsson.utils

# instantiate an argument parser
parser = argparse.ArgumentParser(description='Ericsson MSC CDR decoder')

# optional arguments for:
#   output file (use stdout if not given)
parser.add_argument('-o', dest='outfile', help='output file')

# add a positional argument for the input file
parser.add_argument('infile', help='CDR file')

# parse the arguments
args = parser.parse_args()

# default to stdout for output
outfile = sys.stdout

# if an output file is specified try to open it
if args.outfile:
    try:
        outfile = open(args.outfile, 'w')
    except IOError:
        sys.stderr.write('Could not open file %s\n' % args.outfile)
        sys.exit()


cdrfile = ericsson.utils.cdrfile(args.infile)
output = cdrfile.dump()
outfile.write(output)


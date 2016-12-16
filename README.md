# Ericsson CDR Decoder

Decoder for Ericsson CME20 MSS CDRs. The decoder displays the interpreted value
of a field where appropriate, instead of just the raw value like deasn9 does.

<pre>
usage: cdrdecoder.py [-h] [-o OUTFILE] [--bar] infile

Ericsson MSC CDR decoder

positional arguments:
  infile      CDR file

optional arguments:
  -h, --help  show this help message and exit
  -o OUTFILE  output file
  --number    number CDRs in output
  --bar       display progress bar
</pre>

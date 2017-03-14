#!/usr/bin/python

########################################
# primitive methods
########################################
def _Bitstring(contents):
    return _OctetString(contents)

def _Boolean(contents):
    if contents[0] == 0:
        return 'False'
    else:
        return 'True'

def _Embedded(contents):
    pass

def _Enumerated(contents):
    pass

def _External(contents):
    pass

def _GeneralizedTime(contents):
    pass

def _Integer(contents):
    # if integer is greater than 4 bytes, it is too long to print out as decimal
    if len(contents) <= 4:
        val = 0
        for byte in contents:
            val = val * 256 + byte
        return '%d' % val
    else:
        return _OctetString(contents)

def _ObjectID(contents):
    # first subidentifier in OID encoded as (X * 40) + Y: ref. X.690 clause 8.19.4
    first = contents[0]
    X = first / 40
    Y = first - X * 40
    oid = [X, Y]

    val = 0
    for byte in contents[1:]:
        ext = byte >> 7
        lo = byte & 0x7f
        val = val * 128 + lo

        if ext == 0:
            oid.append(val)
            val = 0

    s = '%d.%d' %(X, Y)
    for x in oid[2:]:
        s = s + '.%d' % x

    return s

def _ObjectDescriptor(contents):
    pass

def _OctetString(contents):
    s = '0x'
    for x in contents:
        s = s + '%02x' % x

    return s

def _Real(contents):
    pass

def _String(contents):
    return str(contents)

def _UTCTime(contents):
    s = str(contents[:6]) + ' ' + str(contents[6:])
    return s


# X.680/Table 1: Universal class tag assignments
tag = [
    None,
    'Boolean',
    'Integer',
    'Bitstring',
    'Octetstring',
    'Null',
    'Object identifier',
    'Object descriptor',
    'External',
    'Real',
    'Enumerated',
    'Embedded-pdv',
    'UTF8String',
    None, # values 13-15 are reserved
    None,
    None,
    'Sequence',
    'Set',
    'NumericString',
    'PrintableString',
    'TeletexString',
    'VideotexString',
    'IA5String',
    'UTCTime',
    'GeneralizedTime',
    'GraphicString',
    'VisibleString',
    'GeneralString',
    'UniversalString',
    'UnrestrictedCharacterStringType',
    'BMPString'
]

parameterMap = {
    'Boolean': _Boolean,
    'Integer': _Integer,
    'Bitstring': _Bitstring,
    'Octetstring': _OctetString,
    'Null': None,
    'Object identifier': _ObjectID,
    'Object descriptor': _ObjectDescriptor,
    'External': _External,
    'Real': _Real,
    'Enumerated': _Enumerated,
    'Embedded-pdv': _Embedded,
    'UTF8String': _String,
    'NumericString': _String,
    'PrintableString': _String,
    'TeletexString': _String,
    'VideotexString': _String,
    'IA5String': _String,
    'UTCTime': _UTCTime,
    'GeneralizedTime': _GeneralizedTime,
    'GraphicString': _String,
    'VisibleString': _String,
    'GeneralString': _String,
    'UniversalString': _String,
    'UnrestrictedCharacterStringType': _String,
    'BMPString': _String
}


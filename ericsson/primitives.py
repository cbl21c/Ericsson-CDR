#!/usr/bin/python


TSC_TELEPHONY         = 0x11
TSC_EMERGENCY         = 0x12
TSC_MT_SMS            = 0x21
TSC_MO_SMS            = 0x22
TSC_ALT_FAX_SPEECH    = 0x41
TSC_FAX_GROUP3        = 0x42
TSC_ALL_PLMN_SPECIFIC = 0xd0

TZ_POSITIVE = 0
TZ_NEGATIVE = 1

PRIORITY_NOT_USED = 0x0f

PRIORITY_LEVEL_A = 0x07
PRIORITY_LEVEL_B = 0x06
PRIORITY_LEVEL_SPARE = 0x00

GSMCHAR = [None] * 128

#
# support functions
#
def luhn(s):
    # s can be list or string of digits
    # if it is a string, first convert it to a list
    if type(s) is str:
        slen = len(s)
        digits = [None] * slen
        for n in range(slen):
            digits[n] = int(s[n])
    elif type(s) is list:
        digits = s
    else:
        # not valid type, return None
        return None

    dlen = len(digits)
    if dlen % 2 == 0:
        odd = [None] * (dlen / 2)
        even = [None] * (dlen / 2)
        for n in range(dlen / 2):
            odd[n] = digits[n * 2]
            even[n] = digits[n * 2 + 1]
    else:
        odd = [None] * (dlen / 2)
        even = [None] * (dlen / 2 + 1)
        for n in range(dlen / 2):
            even[n] = digits[n * 2]
            odd[n] = digits[n * 2 + 1]
        even[dlen / 2] = digits[dlen - 1]

    oddsum = sum(odd)
    evensum = 0
    for n in even:
        x = n * 2
        if x > 9:
            x = x - 9
        evensum = evensum + x

    digitsum = oddsum + evensum
    checksum = 10 - (digitsum % 10)
    if checksum == 10:
        checksum = 0

    return checksum


def gsmchar_initialise():
    # most of these will align with ascii chars
    for n in range(32, 128):
        GSMCHAR[n] = chr(n)

    # these are the exceptions
    GSMCHAR[0x24] = '\xa4'
    GSMCHAR[0x40] = '\xa1'
    GSMCHAR[0x5b] = '\xc4'
    GSMCHAR[0x5c] = '\xd6'
    GSMCHAR[0x5d] = '\xd1'
    GSMCHAR[0x5e] = '\xdc'
    GSMCHAR[0x5f] = '\xa7'
    GSMCHAR[0x60] = '\xbf'
    GSMCHAR[0x7b] = '\xe4'
    GSMCHAR[0x7c] = '\xf6'
    GSMCHAR[0x7d] = '\xf1'
    GSMCHAR[0x7e] = '\xfc'
    GSMCHAR[0x7f] = '\xe0'

    # these are the remaining chars - mask LF and CR
    GSMCHAR[0x00] = '@'
    GSMCHAR[0x01] = '\xa3'
    GSMCHAR[0x02] = '$'
    GSMCHAR[0x03] = '\xa5'
    GSMCHAR[0x04] = '\xe8'
    GSMCHAR[0x05] = '\xe9'
    GSMCHAR[0x06] = '\xf9'
    GSMCHAR[0x07] = '\xec'
    GSMCHAR[0x08] = '\xf2'
    GSMCHAR[0x09] = '\xc7'
    GSMCHAR[0x0a] = ''
    GSMCHAR[0x0b] = '\xd8'
    GSMCHAR[0x0c] = '\xf8'
    GSMCHAR[0x0d] = ''
    GSMCHAR[0x0e] = '\xc5'
    GSMCHAR[0x0f] = '\xe5'
    GSMCHAR[0x10] = ''
    GSMCHAR[0x11] = '_'
    GSMCHAR[0x12] = ''
    GSMCHAR[0x13] = ''
    GSMCHAR[0x14] = ''
    GSMCHAR[0x15] = ''
    GSMCHAR[0x16] = ''
    GSMCHAR[0x17] = ''
    GSMCHAR[0x18] = ''
    GSMCHAR[0x19] = ''
    GSMCHAR[0x1a] = ''
    GSMCHAR[0x1b] = ''
    GSMCHAR[0x1c] = '\xc6'
    GSMCHAR[0x1d] = '\xe6'
    GSMCHAR[0x1e] = '\xdf'
    GSMCHAR[0x1f] = '\xc9'

def gsmchar_decode(s):
    if GSMCHAR[0] is None:
        gsmchar_initialise()

    nbits = 0
    remain = 0
    addr = ''
    for n in range(len(s)):
        # sys.stdout.write('%d %d %02x %02x\n' %(n, nbits, remain, sswap[n]))
        out = ((s[n] << nbits) + remain) & 0x7f
        # sys.stdout.write('%02x\n' % out)
        addr += GSMCHAR[out]
        nbits = (nbits + 1) % 7
        remain = s[n] >> (8 - nbits)

        # if we reach a multiple of 7, we should output two bytes
        if nbits == 0:
            out = s[n] >> 1
            # sys.stdout.write('%02x\n' % out)
            addr += GSMCHAR[out]

    # if the last char is '@', it's probably there only because 7 bits remain
    if out == 0:
        addr = addr[:-1]

    return addr


#
# Ericsson MSC CDR primitive types
#

################################################################################
# Generic and Common Types                                                     #
################################################################################

##############################
# _EnumeratedType            #
##############################
def _EnumeratedType(label, index):
    if index < len(label):
        return '%d (%s)' %(index, label[index])
    else:
        return 'Unexpected value: %d' % index

##############################
# _TBCDString             #
##############################
def _TBCDString(contents):
    # for all parameters which are to be interpreted as TBCD
    # returns the address string but does not display the result
    # Note: this is also a defined type in the ASN.1 specification
    addr = ''
    for x in contents:
        dig1 = x & 0x0f
        dig2 = x >> 4
        if dig1 != 0x0f:
            addr = addr + '%x' % dig1
        if dig2 != 0x0f:
            addr = addr + '%x' % dig2
    return addr

##############################
# _Integer                   #
##############################
def _Integer(contents):
    # for all parameters which are to be displayed as an integer
    value = 0
    for x in contents:
        value = value * 256 + x

    return '%d' % value

##############################
# _OctetString               #
##############################
def _OctetString(contents):
    # for all parameters which are to be displayed as octet string
    val = '0x'
    for x in contents:
        val = val + '%02x' % x

    return val


##############################
# _Raw                       #
##############################
def _Raw(contents):
    # for all parameters which are to be displayed as octet string
    val = ''
    for x in contents:
        val = val + '%02x ' % x
    return val.strip()


################################################################################
# Call Data Parameter Data Types (Section 5.2)                                 #
################################################################################

##############################
# _AccountCode               #
##############################
def _AccountCode(contents):
    code = _TBCDString(contents)
    return code

##############################
# _AddressString             #
##############################
def _AddressString(contents):
    first = contents[0]
    ton = first >> 4
    npi = first & 0x0f
    addr = _TBCDString(contents[1:])
    return 'TON=%d, NPI=%d, Digits=%s' %(ton, npi, addr)

##############################
# _AddressStringExtended     #
##############################
def _AddressStringExtended(contents):
    #return _AddressString(contents)
    first = contents[0]
    ton = first >> 4
    npi = first & 0x0f
    if ton == 14:
        addr = gsmchar_decode(contents[1:])
    else:
        addr = _TBCDString(contents[1:])

    return 'TON=%d, NPI=%d, Digits=%s' %(ton, npi, addr)

##############################
# _AgeOfLocationEstimate             #
##############################
def _AgeOfLocationEstimate(contents):
    return _Integer(contents) + ' mins'

##############################
# _AirInterfaceUserRate             #
##############################
def _AirInterfaceUserRate(contents):
    label = [
        'aIUR9600bps',
        'aIUR14400bps',
        'aIUR19200bps',
        'aIUR28800bps',
        'aIUR38400bps',
        'aIUR43200bps',
        'aIUR57600bps',
        'aIUR38400bps1',
        'aIUR38400bps2',
        'aIUR38400bps3',
        'aIUR38400bps4'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _AoCCurrencyAmountSent             #
##############################
def _AoCCurrencyAmountSent(contents):
    # only used for WCDMA Japan
    pass

##############################
# _ApplicationIdentifier             #
##############################
def _ApplicationIdentifier(contents):
    return _Integer(contents)

##############################
# _AsyncSyncIndicator             #
##############################
def _AsyncSyncIndicator(contents):
    label = [
        'syncData',
        'asyncData'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _BearerServiceCode             #
##############################
def _BearerServiceCode(contents):
    if contents[0] >> 4 != 0x01:
        return 'Unknown'

    label = [
        'All data Circuit Data Asynchronous (CDA) Services',
        'Data CDA - 300bps',
        'Data CDA - 1200bps',
        'Data CDA - 1200-75bps',
        'Data CDA - 2400bps',
        'Data CDA - 4800bps',
        'Data CDA - 9600bps',
        'General - data CDA',
        'All data Circuit Data Synchronous (CDS) Services',
        None,
        'Data CDS - 1200bps',
        None,
        'Data CDS - 2400bps',
        'Data CDS - 4800bps',
        'Data CDS - 9600bps',
        'General - data CDS'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _BitRate             #
##############################
def _BitRate(contents):
    label = [
        'Unknown',
        '4.75 kbps',
        '5.15 kbps',
        '5.9 kbps',
        '6.7 kbps',
        '7.4 kbps',
        '7.95 kbps',
        '10.2 kbps',
        '12.2 kbps',
        '14.4 kbps',
        '64.0 kbps',
        '28.8 kbps',
        '57.6 kbps',
        '4.0 kbps',
        '6.60 kbps',
        '8.85 kbps',
        '12.65 kbps'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _BladeID             #
##############################
def _BladeID(contents):
    return _Integer(contents)

##############################
# _BSSMAPCauseCode             #
##############################
def _BSSMAPCauseCode(contents):
    ext = contents[0] >> 7
    cause = contents[0] & 0x7f
    val = 'Cause=%d' % cause

    if ext == 1:
        extcause = contents[1]
        val = val + '; Extended Cause=%d' % extcause

    return val

##############################
# _CallAttemptState             #
##############################
def _CallAttemptState(contents):
    label = [
        'initialState',
        'callSentState',
        'callRejectedState',
        'callOfferedState',
        'noResponseState',
        'alertingState',
        'unknownCallState',
        'callActiveState'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _CallIDNumber             #
##############################
def _CallIDNumber(contents):
    return _Integer(contents)

##############################
# _CallPosition              #
##############################
def _CallPosition(contents):
    label = [
        'valueUsedForAllCallsToDetermineIfOutputToTakePlace',
        'callHasReachedCongestionOrBusyState',
        'callHasOnlyReachedThroughConnection',
        'b-AnswerHasBeenReceived'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _CarrierIdentificationCode             #
##############################
def _CarrierIdentificationCode(contents):
    return _TBCDString(contents)

##############################
# _CarrierInfo             #
##############################
def _CarrierInfo(contents):
    addr = _TBCDString(contents[0:2])
    val = 'ID=%s' % addr

    if len(contents) == 3:
        hi = contents[2] >> 4
        lo = contents[2] & 0x0f

        label = ['No indication', 'Hierarchy level 1', 'Heirarchy level 2']
        val = val + '; Entry POI: %s; Exit POI: %s' %(label[hi], label[lo])

    return val

##############################
# _CarrierInformation             #
##############################
def _CarrierInformation(contents):
    # only used for WCDMA Japan
    pass

##############################
# _CarrierSelectionSubstitutionInformation             #
##############################
def _CarrierSelectionSubstitutionInformation(contents):
    # descriptions are too long to make this an enumerated type
    return _Integer(contents)
    '''
        001 Presubscribed carrier exists, and carrier is not input by calling party. Presubscribed carrier is used.,
        010 Presubscribed carrier is same as carrier input by calling party.  Input carrier is used.,
        011 Presubscribed carrier exists, and input by calling party is undetermined. Presubscribed carrier is used.,
        100 Carrier is input by calling party, and it is not the presubscribed carrier for the calling party.  Input carrier is used.,
        101 Carrier given by Carrier Analysis is used instead of presubscribed carrier.,
        110 Carrier given by Carrier Analysis is used instead of carrier input by calling party.,
        111 Default carrier is used.
    '''

##############################
# _CauseCode             #
##############################
def _CauseCode(contents):
    return _Integer(contents)

##############################
# _ChangeInitiatingParty             #
##############################
def _ChangeInitiatingParty(contents):
    label = [
        'userInitiated',
        'networkInitiated'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _ChannelAllocationPriorityLevel                      #
##############################
def _ChannelAllocationPriorityLevel(contents):
    priority = (contents[0] >> 2) & 0x0f
    if priority == PRIORITY_NOT_USED:
        return 'Not used'
    else:
        return '%d' % priority

##############################
# _ChannelCodings                      #
##############################
def _ChannelCodings(contents):
    used = 0
    codings = contents[0]
    if (codings >> 3) % 2 == 1:
        val = '14.4kbps'
        used = 1
    if (codings >> 2) % 2 == 1:
        val = val + ' ' * used + '9.6kbps'
        used = 1
    if codings % 2 == 1:
        val = val + ' ' * used + '4.8kbps'

    return val

##############################
# _ChargeAreaCode                      #
##############################
def _ChargeAreaCode(contents):
    # only used for WCDMA Japan
    pass

##############################
# _ChargedParty                      #
##############################
def _ChargedParty(contents):
    label = [
        'chargingOfCallingSubscriber',
        'chargingOfCalledSubscriber',
        'noCharging'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _ChargeInformation #
##############################
def _ChargeInformation(contents):
    # only used for WCDMA Japan
    pass

##############################
# _ChargingCase #
##############################
def _ChargingCase(contents):
    return _Integer(contents)

##############################
# _ChargingIndicator #
##############################
def _ChargingIndicator(contents):
    # only used for WCDMA Japan
    pass

##############################
# _ChargingOrigin #
##############################
def _ChargingOrigin(contents):
    return _Integer(contents)

##############################
# _ChargingUnitsAddition #
##############################
def _ChargingUnitsAddition(contents):
    return _Integer(contents)

##############################
# _Counter #
##############################
def _Counter(contents):
    return _Integer(contents)

##############################
# _CRIIndicator #
##############################
def _CRIIndicator(contents):
    label = [
        'chargeRateInformationAcknowledged',
        'chargeRateInformationNotAcknowledged'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _CRIToMS #
##############################
def _CRIToMS(contents):
    val = ''
    for n in range(7):
        addr = _TBCDString(contents[n * 2 : n * 2 + 2])
        if n > 0:
            val = val + ', '
        val = val + 'e%d= %s' % (n + 1, addr)

    return val

##############################
# _CUGIndex #
##############################
def _CUGIndex(contents):
    return _Integer(contents)

##############################
# _CUGInterlockCode #
##############################
def _CUGInterlockCode(contents):
    # review
    return _OctetString(contents)

##############################
# _C7ChargingMessage #
##############################
def _C7ChargingMessage(contents):
    (hh, mm) = contents[0:2]
    val = 'Time %02d:02d' %(hh, mm)

    mi = contents[2]
    val = val + '; MsgInd=%02x' % mi

    taxQuantumA = contents[3] >> 4
    tariffIndA  = contents[3] & 0x0f
    val = val + '; Tax quantum A=%02x; Tariff Ind A=%02x' %(taxQuantumA, tariffIndA)

    tariffFactorA = contents[4]
    val = val + '; Tariff Factor A=%02x' % tariffFactorA

    timeIndB = contents[5]
    val = val + '; Time Ind B=%02x' % timeIndB

    taxQuantumB = contents[6] >> 4
    tariffIndB  = contents[6] & 0x0f
    val = val + '; Tax quantum B=%02x; Tariff Ind B=%02x' %(taxQuantumB, tariffIndB)

    tariffFactorB = contents[7]
    val = val + '; Tariff Factor B=%02x' % tariffFactorB

    return val

##############################
# _C7CHTMessage #
##############################
def _C7CHTMessage(contents):
    (hh, mm) = contents[0:2]
    val = 'Time %02d:02d' %(hh, mm)

    mi = contents[2] >> 4
    ti = contents[2] & 0x0f
    val = val + '; MsgInd=%02x; Tariff Ind=%02x' %(mi, ti)

    tariffFactor = contents[3]
    val = val + '; Tariff Factor =%02x' % tariffFactor

    timeInd = contents[4]
    val = val + '; Time Ind =%02x' % timeInd

    return val

##############################
# _Date #
##############################
def _Date(contents):
    if len(contents) == 3:
        (yy, mm, dd) = contents[0:3]

    if len(contents) == 4:
        (cc, yy, mm, dd) = contents
        yy =cc * 100 + yy

    return '%d/%02d/%02d' %(dd, mm, yy)

##############################
# _DecipheringKeys #
##############################
def _DecipheringKeys(contents):
    # review
    return _OctetString(contents)

##############################
# _DefaultCallHandling #
##############################
def _DefaultCallHandling(contents):
    label = [
        'continueCall',
        'releaseCall'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _DefaultSMSHandling #
##############################
def _DefaultSMSHandling(contents):
    label = [
        'continueTransaction',
        'releaseTransaction'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _DeliveryOfErroneousSDU #
##############################
def _DeliveryOfErroneousSDU(contents):
    label = [
        'yes',
        'no',
        'noErrorDetectionConsideration'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _DisconnectingParty #
##############################
def _DisconnectingParty(contents):
    label = [
        'callingPartyRelease',
        'calledPartyRelease',
        'networkRelease'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _Distributed #
##############################
def _Distributed(contents):
    return 'A: %d%%, B: %d%%, C: %d%%, Other: %d%%' % (contents[0], contents[1], contents[2], contents[3])

##############################
# _EmergencyServiceCategory #
##############################
def _EmergencyServiceCategory(contents):
    label = [
        'Police',
        'Ambulance',
        'Fire brigade',
        'Marine guard',
        'Mountain rescue',
        'Manually initiated eCall',
        'Automatically initiated eCall'
    ]

    used = 0
    val = ''
    for shift in range(7):
        emerg = contents[0] >> shift
        if emerg % 2 == 1:
            val = val + ', ' * used + label[shift]
            used = 1

    return val

##############################
# _EMLPPPriorityLevel #
##############################
def _EMLPPPriorityLevel(contents):
    priority = contents[0] & 0x07
    val = 'Priority level '
    if priority == PRIORITY_LEVEL_A:
        val = val + 'A'
    if priority == PRIORITY_LEVEL_B:
        val = val + 'B'
    if priority == PRIORITY_LEVEL_SPARE:
        val = val + '(Spare)'
    else:
        val = val + '%d' % (5 - priority)

    return val

##############################
# _EndToEndAccessDataMap #
##############################
def _EndToEndAccessDataMap(contents):
    # review
    return _OctetString(contents)

##############################
# _EosInfo #
##############################
def _EosInfo(contents):
    # enumerated type
    label = [None] * 64
    label[0x00] = 'Free subscriber'
    label[0x01] = 'Free subscriber. No time supervision'
    label[0x02] = 'Free subscriber. No charging'
    label[0x03] = 'Free subscriber. No time supervision.  No charging'
    label[0x04] = 'Free subscriber. Last party release'
    label[0x05] = 'Free subscriber. No time supervision.  Last party release'
    label[0x06] = 'Free subscriber. No charging. Last party release'
    label[0x07] = 'Free subscriber. No time supervision.  No charging. Last party release'
    label[0x10] = 'Set up speech condition'
    label[0x11] = 'Set up speech condition.  No time supervision'
    label[0x12] = 'Set up speech condition.  No charging'
    label[0x21] = 'Access barred'
    label[0x22] = 'Transferred subscriber'
    label[0x23] = 'Busy subscriber'
    label[0x24] = 'Busy subscriber with callback protection'
    label[0x25] = 'Unallocated number'
    label[0x26] = 'Address incomplete'
    label[0x27] = 'Call transfer protection that is "follow me" not allowed to this subscriber'
    label[0x28] = 'Subscriber line out of order'
    label[0x29] = 'Intercepted subscriber'
    label[0x2a] = 'Supervised by an operator.  Trunk offering marked'
    label[0x2b] = 'Rerouting to service centre'
    label[0x2c] = 'Line lock out'
    label[0x2d] = 'Send acceptance tone'
    label[0x2e] = 'No answer/incompatible destination (used for ISDN)'
    label[0x2f] = 'Send refusal tone. Only used at subscriber services'
    label[0x33] = 'Digital path not provided'
    label[0x34] = 'Congestion without differentiation'
    label[0x35] = 'Time release'
    label[0x36] = 'Technical fault'
    label[0x37] = 'Congestion in group selection network'
    label[0x38] = 'Lack of devices'
    label[0x39] = 'Congestion in subscriber selection network'
    label[0x3a] = 'Congestion in international network'
    label[0x3b] = 'Congestion in national network'
    label[0x3c] = 'Conditional congestion (Region option)'
    label[0x3d] = 'Route congestion'
    label[0x3e] = 'Unpermitted traffic case'
    label[0x3f] = 'No acknowledgement from mobile subscriber'
    return _EnumeratedType(label, contents[0])

##############################
# _ErrorRatio #
##############################
def _ErrorRatio(contents):
    return '1 per %dx10^%d' % (contents[0], contents[1])

##############################
# _EventCRIToMS #
##############################
def _EventCRIToMS(contents):
    e3 = _TBCDString(contents[0:2])
    e4 = _TBCDString(contents[2:4])
    return 'e3=%s e4=%s' % (e3, e4)

##############################
# _ExchangeIdentity #
##############################
def _ExchangeIdentity(contents):
    return str(bytearray(contents))

##############################
# _FaultCode #
##############################
def _FaultCode(contents):
    return _Integer(contents)

##############################
# _FirstRadioChannelUsed #
##############################
def _FirstRadioChannelUsed(contents):
    label = [
        'fullRateChannel',
        'halfRateChannel'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _FixedNetworkUserRate #
##############################
def _FixedNetworkUserRate(contents):
    label = [
        None,
        'fNUR9600bps',
        'fNUR14400bps',
        'fNUR19200bps',
        'fNUR28800bps',
        'fNUR38400bps',
        'fNUR48000bps',
        'fNUR56000bps',
        'fNUR64000bps',
        'fNURautobauding'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _FreeFormatData #
##############################
def _FreeFormatData(contents):
    return _OctetString(contents)

##############################
# _FrequencyBandSupported #
##############################
def _FrequencyBandSupported(contents):
    band = ['P-GSM', 'E-GSM', 'GSM 1800']

    value = contents[0]
    nbands = 0
    val = '0x%02x: ' % value

    for x in range(3):
        if value % 2 == 1:
            if nbands > 0:
                val = val + ', '
            val = val + band[x]
            nbands = nbands + 1
        value = value >> 1

    return val

##############################
# _GenericDigitsSet #
##############################
def _GenericDigitsSet(contents):
    return _OctetString(contents)

##############################
# _GenericNumbersSet #
##############################
def _GenericNumbersSet(contents):
    return _OctetString(contents)

##############################
# _GlobalCallReference #
##############################
def _GlobalCallReference(contents):
    # review
    ptr = 0

    length = contents[ptr]
    ptr = ptr + 1
    if length > 0:
        netId = contents[ptr:ptr + length]
        val = 'Network ID=' + _OctetString(netId)
        ptr = ptr + length

    length = contents[ptr]
    ptr = ptr + 1
    if length > 0:
        nodeId = contents[ptr:ptr + length]
        val = val + ' Node ID=' + _OctetString(nodeId)
        ptr = ptr + length

    length = contents[ptr]
    ptr = ptr + 1
    if length > 0:
        callrefId = contents[ptr:ptr + length]
        val = val + ' Call Ref ID=' + _OctetString(callrefId)

    return val

##############################
# _GlobalTitle #
##############################
def _GlobalTitle(contents):
    (tt, npoe, nai) = contents[0:3]
    np = npoe >> 4
    if npoe & 0x0f == 1:
        oe = 'Odd'
    elif npoe & 0x0f == 2:
        oe = 'Even'

    digits = _TBCDString(contents[3:])

    if oe == 'Odd':
        digits = digits[:-1]

    # don't need to print out Odd/Even if the digits are printed to the correct length
    return 'TT=%d, NP=%d, NAI=%d, Digits=%s' % (tt, np, nai, digits)

##############################
# _GlobalTitleAndSubSystemNumber #
##############################
def _GlobalTitleAndSubSystemNumber(contents):
    ssn = contents[0]
    val = 'SSN=%d, ' % ssn + _GlobalTitle(contents[1:])
    return val

##############################
# _GSMCallReferenceNumber #
##############################
def _GSMCallReferenceNumber(contents):
    return _OctetString(contents)

##############################
# _IMEI #
##############################
def _IMEI(contents):
    # IMEI is encoded in the CDR *without* the checksum digit
    # so we need to calculate it ourself and append it
    imei = _TBCDString(contents[0:7])
    checksum = luhn(imei)
    imei = imei + '%d' % checksum
    return imei

##############################
# _IMEISV #
##############################
def _IMEISV(contents):
    # IMEI is encoded in the CDR *without* the checksum digit
    # so we need to calculate it ourself and append it
    imei = _TBCDString(contents[0:7])
    checksum = luhn(imei)
    imeisv = imei + '%d' % checksum + _TBCDString([contents[7]])
    return imeisv

##############################
# _IMSI #
##############################
def _IMSI(contents):
    return _TBCDString(contents)

##############################
# _INMarkingOfMS #
##############################
def _INMarkingOfMS(contents):
    label = [
        None,
        'originatingINService',
        'terminatingINService',
        'originatingINCategoryKeyService',
        'terminatingINCategoryKeyService',
        'originatingCAMELService',
        'terminatingCAMELService',
        'originatingExtendedCAMELServiceWithINCapabilityIndicator',
        'terminatingExtendedCAMELServiceWithINCapabilityIndicator',
        'originatingExtendedCAMELServiceWithOriginatingINCategoryKey',
        'terminatingExtendedCAMELServiceWithTerminatingINCategoryKey',
        'subscriberDialledCAMELService',
        'subscriberDialledCAMELServiceAndOriginatingCAMELService',
        'visitedTerminatingCAMELService'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _INServiceTrigger #
##############################
def _INServiceTrigger(contents):
    return _Integer(contents)

##############################
# _IntermediateRate #
##############################
def _IntermediateRate(contents):
    label = [
        None,
        None,
        'rate8KbitPerSecondUsed',
        'rate16KbitPerSecondUsed'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _InternalCauseAndLoc #
##############################
def _InternalCauseAndLoc(contents):
    location = contents[0]
    cause    = contents[1]
    return 'Location=%02x; Cause=%02x' %(location, cause)

##############################
# _IuCodec #
##############################
def _IuCodec(contents):
    label = [None] * 21
    label[1]  = 'uMTSAdaptiveMultiRate-Set7'
    label[2]  = 'uMTSAdaptiveMultiRate-AllModes'
    label[3]  = 'uMTSAdaptiveMultiRate2-Set7'
    label[4]  = 'uMTSAdaptiveMultiRate2-Set1'
    label[5]  = 'uMTSAdaptiveMultiRate2-AllModes'
    label[20] = 'uMTSAdaptiveMultiRateWideBand-Set0'
    return _EnumeratedType(label, contents[0])

##############################
# _LCSAccuracy #
##############################
def _LCSAccuracy(contents):
    return _OctetString(contents)

##############################
# _LCSClientType #
##############################
def _LCSClientType(contents):
    label = [
        'emergencyServices',
        'valueAddedServices',
        'plmnOperatorServices',
        'lawfulInterceptServices'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _LCSDeferredEventType #
##############################
def _LCSDeferredEventType(contents):
    label = [
        'deferred-MT-UEreachableEvent'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _LegID #
##############################
def _LegID(contents):
    return _Integer(contents)

##############################
# _LevelOfCAMELService #
##############################
def _LevelOfCAMELService(contents):
    # the encoding in the CDR is not consistent with the documentation
    return _OctetString(contents)

##############################
# _LocationCode #
##############################
def _LocationCode(contents):
    return _Integer(contents)

##############################
# _LocationEstimate #
##############################
def _LocationEstimate(contents):
    # review
    return _OctetString(contents)

##############################
# _LocationInformation #
##############################
def _LocationInformation(contents):
    dig1 = contents[0] & 0x0f
    dig2 = contents[0] >> 4
    dig3 = contents[1] & 0x0f
    mcc = '%x%x%x' %(dig1, dig2, dig3)

    dig1 = contents[2] & 0x0f
    dig2 = contents[2] >> 4
    dig3 = contents[1] >> 4
    mnc = '%x%x' %(dig1, dig2)
    if dig3 != 0x0f:
        mnc = mnc + '%x' % dig3

    lac = contents[3] * 256 + contents[4]
    sac = contents[5] * 256 + contents[6]

    return 'MCC=%s, MNC=%s, LAC=%d, SAC=%d' %(mcc, mnc, lac, sac)


##############################
# _LocationInformationExtension #
##############################
def _LocationInformationExtension(contents):
    octets = contents
    octets[0] = octets[0] & 0x0f
    return 'E-UTRAN Cell Id=' + _Integer(octets)

##############################
# _MessageReference #
##############################
def _MessageReference(contents):
    return _Integer(contents)

##############################
# _MessageTypeIndicator #
##############################
def _MessageTypeIndicator(contents):
    label = [
        'sMSdeliverSCtoMS',
        'sMSdeliveReportMStoSC',
        'sMSstatusReportSCtoMS',
        'sMScommandMStoSC',
        'sMSsubmitMStoSC',
        'sMSsubmitReportSCtoMS',
        'reservedMTIValue'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _MiscellaneousInformation #
##############################
def _MiscellaneousInformation(contents):
    return _Integer(contents)

##############################
# _MMEIdentity #
##############################
def _MMEIdentity(contents):
    return str(contents)

##############################
# _MMEName #
##############################
def _MMEName(contents):
    return str(contents)

##############################
# _MobileUserClass1 #
##############################
def _MobileUserClass1(contents):
    # only used for WCDMA Japan
    pass

##############################
# _MobileUserClass2 #
##############################
def _MobileUserClass2(contents):
    # only used for WCDMA Japan
    pass

##############################
# _NetworkCallReference #
##############################
def _NetworkCallReference(contents):
    val = 'Seq=' + _Integer(contents[0:3])
    val = val + ', SwitchID=' + _Integer(contents[3:])
    return val

##############################
# _NumberOfChannels #
##############################
def _NumberOfChannels(contents):
    nchannels = [contents[0] + 1]
    return _Integer(nchannels)

##############################
# _NumberOfMeterPulses #
##############################
def _NumberOfMeterPulses(contents):
    return _Integer(contents)

##############################
# _NumberOfOperations #
##############################
def _NumberOfOperations(contents):
    return _Integer(contents)

##############################
# _NumberOfShortMessage #
##############################
def _NumberOfShortMessage(contents):
    return _Integer(contents)

##############################
# _OperationIdentifier #
##############################
def _OperationIdentifier(contents):
    return _Integer(contents)

##############################
# _OptimalRoutingType #
##############################
def _OptimalRoutingType(contents):
    label = [
        'optimalRoutingAtLateCallForwarding',
        'hplmnOptimalRoutingAtLateCallForwarding'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _OriginatedCode #
##############################
def _OriginatedCode(contents):
    label = [
        'callOriginatingFromOwnSubscriberInSSN',
        'callOriginatingFromOwnSubscriberInGSN',
        'callOriginatingFromIncomingTrunk',
        'callOriginatingFromSUSblock',
        'callOriginatingFromOMSblock',
        'testCallTowardsIL-OL-BL',
        'testCallWithIndividualSelectionOfB-Subscriber',
        'testCallWithIndividualSelectionExceptB-Subscriber',
        'testCallWithSelectionInSpecifiedRoute',
        'operator'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _OriginatingLineInformation #
##############################
def _OriginatingLineInformation(contents):
    return _OctetString(contents)

##############################
# _OutputForSubscriber #
##############################
def _OutputForSubscriber(contents):
    label = [
        'callingParty',
        'calledParty',
        'callingAndCalledParty'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _OutputType #
##############################
def _OutputType(contents):
    label = [
        'noOutput',
        'iCIoutputForCallingSubscriber',
        'iCIOutputForCalledSubscriber',
        'iCIOutputForCallingAndCalledSubscribers',
        'tTOutputOnly',
        'tTAndICIForCallingSubscriber',
        'tTAndICIForCalledSubscriber',
        'tTAndICIForCallingAndCalledSubscribers'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _PartialOutputRecNum #
##############################
def _PartialOutputRecNum(contents):
    return _Integer(contents)

##############################
# _PChargingVector #
##############################
def _PChargingVector(contents):
    datalen = len(contents)
    ptr = 0
    val = ''
    while ptr < datalen:
        fieldlen = contents[ptr]
        ptr = ptr + 1
        if ptr > 1:
            val = val + ','
        val = val + str(contents[ptr:ptr + fieldlen])
        ptr = ptr + fieldlen

    return val

##############################
# _PChargingVectorRelated #
##############################
def _PChargingVectorRelated(contents):
    return _PChargingVector(contents)

##############################
# _PositioningDelivery #
##############################
def _PositioningDelivery(contents):
    # review
    return _OctetString(contents)

##############################
# _PointCodeAndSubSystemNumber #
##############################
def _PointCodeAndSubSystemNumber(contents):
    (spc1, spc2, spc3, ssn) = contents
    spc = spc2 * 256 + spc1
    return 'PC=%d, SSN=%d' %(spc, ssn)

##############################
# _PositionAccuracy #
##############################
def _PositionAccuracy(contents):
    # review
    return _OctetString(contents)

##############################
# _PresentationAndScreeningIndicator #
##############################
def _PresentationAndScreeningIndicator(contents):
    screen = [
        'Screening indicator not valid',
        'User provided, verified, and passed',
        None,
        'Network provided'
    ]

    present = [
        'Presentation allowed',
        'Presentation restricted',
        None,
        'Presentation restricted by network'
    ]

    value = contents[0]
    hi = value >> 4
    lo = value & 0x0f

    return '0x%02x: %s; %s' %(value, screen[hi], present[lo])

##############################
# _ProcedureCode #
##############################
def _ProcedureCode(contents):
    return _TBCDString(contents)

##############################
# _RadioChannelProperty #
##############################
def _RadioChannelProperty(contents):
    label = [
        'halfRateChannel',
        'fullRateChannel',
        'dualRateHalfRatePreferred',
        'dualRateFullRatePreferred',
        'twoFullRateChannels',
        'threeFullRateChannels',
        'fourFullRateChannels',
        'twoAssignedAirTimeSlots',
        'fourAssignedAirTimeSlots',
        'sixAssignedAirTimeSlots',
        'eightAssignedAirTimeSlots',
        'twelveAssignedAirTimeSlots',
        'sixteenAssignedAirtimeSlots',
        'twoDownlinkOneUplinkAssignedAirTimeSlots',
        'fourDownlinkOneUplinkAssignedAirTimeSlots',
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _RANAPCauseCode #
##############################
def _RANAPCauseCode(contents):
    return _Integer(contents)

##############################
# _RecordSequenceNumber #
##############################
def _RecordSequenceNumber(contents):
    return _Integer(contents)

##############################
# _RedirectionCounter #
##############################
def _RedirectionCounter(contents):
    return _Integer(contents)

##############################
# _RegionalServiceUsed #
##############################
def _RegionalServiceUsed(contents):
    label = [
        'localSubscription',
        'regionalSubcription',
        'subscriptionWithTariffAreas',
        'regionalSubcriptionAndSubscriptionWithTariffAreas'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _ResponseTimeCategory #
##############################
def _ResponseTimeCategory(contents):
    label = [
        'lowdelay',
        'delaytolerant',
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _RoamingPriorityLevel #
##############################
def _RoamingPriorityLevel(contents):
    # review
    return _OctetString(contents)

##############################
# _Route #
##############################
def _Route(contents):
    return (contents)

##############################
# _RTCDefaultServiceHandling #
##############################
def _RTCDefaultServiceHandling(contents):
    label = [
        'serviceAllowed',
        'serviceNotAllowed',
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _RTCFailureIndicator #
##############################
def _RTCFailureIndicator(contents):
    return _Integer(contents)

##############################
# _RTCNotInvokedReason #
##############################
def _RTCNotInvokedReason(contents):
    label = [
        'emergencyCall',
        'callToSpecialDestination',
        'callLegNotToBeCharged',
        'smsNotToBeCharged',
        'mcaSMSFreeOfCharge',
        'undeterminedRoamingPLMN'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _RTCSessionID #
##############################
def _RTCSessionID(contents):
    return _OctetString(contents)

##############################
# _SelectedCodec #
##############################
def _SelectedCodec(contents):
    label = [
        'gSMFullRate',
        'gSMHalfRate',
        'gSMEnhancedFullRate',
        'fullRateAdaptiveMultiRate',
        'halfRateAdaptiveMultiRate',
        'uMTSAdaptiveMultiRate',
        'uMTSAdaptiveMultiRate2',
        'tDMAEnhancedFullRate',
        'pDCEnhancedFullRate'
    ]
    # pad out to 16 elements and fill in index 15
    label = label + [None] * (16 - len(label))
    label[15] = 'inmarsatCoding'
    return _EnumeratedType(label, contents[0])

##############################
# _ServiceCode #
##############################
def _ServiceCode(contents):
    return _TBCDString(contents)

##############################
# _ServiceFeatureCode #
##############################
def _ServiceFeatureCode(contents):
    return _OctetString(contents)

##############################
# _ServiceKey #
##############################
def _ServiceKey(contents):
    return _Integer(contents[0:4])

##############################
# _ServiceSwitchingType #
##############################
def _ServiceSwitchingType(contents):
    label = [
        'speechToFax',
        'faxToSpeech',
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _Single #
##############################
def _Single(contents):
    label = [
        'aPartyToBeCharged',
        'bPartyToBeCharged',
        'cPartyToBeCharged',
        'otherPartyToBeCharged',
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _SMSResult #
##############################
def _SMSResult(contents):
    label = [
        'unsuccessfulMOSMSDeliverytoSMSCDuetoCAMELReason',
        'unsuccessfulMOSMSDeliverytoSMSCDuetoOtherReason',
        'unsuccessfulMTSMSDeliverytoMSDuetoCAMELReason',
        'unsuccessfulMTSMSDeliverytoMSDuetoOtherReason',
        'unsuccessfulMOSMSDeliverytoSMSCDuetoRTCFAReason',
        'unsuccessfulMTSMSDeliverytoMSDuetoRTCFAReason'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _SpeechCoderPreferenceList #
##############################
def _SpeechCoderPreferenceList(contents):
    label = [
        'fullRateVersion1',
        'fullRateVersion2',
        'fullRateVersion3',
        'halfRateVersion1',
        'halfRateVersion2',
        'halfRateVersion3',
        'fullRateVersion5'
    ]

    val = '{'
    for n in range(len(contents)):
        x = contents[n]
        if n > 0:
            val = val + ', '
        val = val + label[x]

    val = val + '}'
    return val

##############################
# _SpeechCoderVersion #
##############################
def _SpeechCoderVersion(contents):
    label = [
        'fullRateVersion1',
        'fullRateVersion2',
        'fullRateVersion3',
        'halfRateVersion1',
        'halfRateVersion2',
        'halfRateVersion3',
        'fullRateVersion5'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _SRVCCAlertingIndicator #
##############################
def _SRVCCAlertingIndicator(contents):
    label = [
        'OriginatingCallInAlertingState',
        'TerminatingCallInAlertingState',
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _SRVCCIndicator #
##############################
def _SRVCCIndicator(contents):
    label = [
        'e-UTRAN',
        'uTRAN (HSPA)',
        'gERAN',
        'uTRAN'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _SSCode #
##############################
def _SSCode(contents):
    # review
    return _OctetString(contents)

##############################
# _SSFChargingCase #
##############################
def _SSFChargingCase(contents):
    return _Integer(contents)

##############################
# _SSRequest #
##############################
def _SSRequest(contents):
    label = [
        'registration',
        'erasure',
        'activation',
        'deactivation',
        'interrogation',
        'invoke',
        'registerPassword',
        'processUSSD'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _SubscriberState #
##############################
def _SubscriberState(contents):
    label = [
        'detached',
        'attached',
        'implicitDetached',
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _SubscriptionType #
##############################
def _SubscriptionType(contents):
    return _Integer(contents)

##############################
# _SwitchIdentity #
##############################
def _SwitchIdentity(contents):
    return _Integer(contents)

##############################
# _TAC #
##############################
def _TAC(contents):
    (tsc, tos, toi) = contents[0:3]
    val = 'TSC=%d, TOS=%d, TOI=%d' %(tsc, tos, toi)
    if len(contents) == 4:
        top = contents[3]
        val = val + ', TOP=%d' % top

    return val

##############################
# _TargetRNCid #
##############################
def _TargetRNCid(contents):
    # review
    return _OctetString(contents)

##############################
# _TariffClass #
##############################
def _TariffClass(contents):
    return _Integer(contents)

##############################
# _TariffSwitchInd #
##############################
def _TariffSwitchInd(contents):
    label = [
        'noTariffSwitch',
        None,
        'tariffSwitchAfterStartOfCharging',
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _TBCDString #
##############################
# see Generic Types

##############################
# _TeleServiceCode #
##############################
def _TeleServiceCode(contents):
    tsc = contents[0]
    val = '0x%02x ' % tsc

    if tsc == TSC_TELEPHONY:
        val = val + '(Telephony)'
    elif tsc == TSC_EMERGENCY:
        val = val + '(Emergency)'
    elif tsc == TSC_MT_SMS:
        val = val + '(MT_SMS)'
    elif tsc == TSC_MO_SMS:
        val = val + '(MO_SMS)'
    elif tsc == TSC_ALT_FAX_SPEECH:
        val = val + '(Alt. Fax and Speech)'
    elif tsc == TSC_FAX_GROUP3:
        val = val + '(Fax Group 3)'
    elif tsc & 0xf0 == TSC_ALL_PLMN_SPECIFIC:
        lo = tsc & 0x0f
        if lo == 0:
            val = val + '(All PLMN specific TS)'
        else:
            val = val + '(PLMN specific TS - %X)' % lo
    else:
        val = val + '(Unknown)'

    return val

##############################
# _Time                      #
##############################
def _Time(contents):
    (hh, mm, ss) = contents[0:3]
    val = '%d:%02d:%02d' %(hh, mm, ss)

    if len(contents) == 4:
        val = val + '.%d' % contents[3]

    return val

##############################
# _Timezone #
##############################
def _Timezone(contents):
    tens = contents[0] & 0x07
    sign = (contents[0] >> 3) % 2
    units = contents[0] >> 4

    quarters = tens * 10 + units
    hh = quarters / 4
    mm = quarters % 4

    val = 'UTC'
    if sign == TZ_NEGATIVE:
        val = val + '-'
    else:
        val = val + '+'
    val = val + '%02d:%02d' %(hh, mm * 15)

    return val

##############################
# _TrafficActivityCode #
##############################
def _TrafficActivityCode(contents):
    (tos, toi, top, tsc, rop) = contents
    return 'TOS=%d, TOI=%d, TOP=%d, TSC=%d, ROP=%d' %(tos, toi, top, tsc, rop)

##############################
# _TrafficClass #
##############################
def _TrafficClass(contents):
    label = [
        'Conversational Class',
        'Streaming Class',
        'Interactive Class',
        'Background Class'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _TransferDelay #
##############################
def _TransferDelay(contents):
    return _Integer(contents)

##############################
# _TransitCarrierInfo #
##############################
def _TransitCarrierInfo(contents):
    # only used for WCDMA Japan
    pass

##############################
# _TransparencyIndicator #
##############################
def _TransparencyIndicator(contents):
    label = [
        'transparent',
        'nonTransparent'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _TriggerDetectionPoint #
##############################
def _TriggerDetectionPoint(contents):
    label = [
        None,
        'originatingCallAttemptAuthorized',
        'collectedInformation',
        'analyzedInformation',
        'originatingCallAttemptRouteSelectFailure',
        'originatingCallAttemptCalledPartyBusy',
        'originatingCallAttemptCalledPartyNotAnswer',
        'originatingCallAttemptCalledPartyAnswer',
        'originatingCallAttemptMid-CallEventDetected',
        'originatingCallAttemptCallDisconnecting',
        'originatingCallAttemptCallAbandon',
        'terminatingCallAttemptAuthorized',
        'terminatingCallAttemptCalledPartyBusy',
        'terminatingCallAttemptNoAnswer',
        'terminatingCallAttemptAnswer',
        'terminatingCallAttemptMid-CallEventDetected'
        'terminatingCallAttemptCallDisconnect',
        'terminatingCallAttemptCallAbandon',
    ]

    # pad out to 256 elements to insert elements with index >= 247
    label = label + [None] * (256 - len(label))
    label[247] = 'terminatingCallAttemptCallReAnswer'
    label[248] = 'terminatingCallAttemptCallSuspended'
    label[249] = 'terminatingCallAttemptCalledPartyNotReachable'
    label[250] = 'terminatingCallAttemptAlerting'
    label[251] = 'terminatingCallAttemptRouteSelectFailure'
    label[252] = 'originatingCallAttemptCalledPartyReAnswer'
    label[253] = 'originatingCallAttemptCallSuspended'
    label[254] = 'originatingCallAttemptCalledPartyNotReachable'
    label[255] = 'originatingCallAttemptAlerting'

    return _EnumeratedType(label, contents[0])

##############################
# _TypeOfCalledSubscriber #
##############################
def _TypeOfCalledSubscriber(contents):
    label = [
        'pSTNSubscriber',
        'iSDNSubscriber',
        'unknownSubscriber'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _TypeOfCallingSubscriber #
##############################
def _TypeOfCallingSubscriber(contents):
    return _Integer(contents)

##############################
# _TypeOfLocationRequest #
##############################
def _TypeOfLocationRequest(contents):
    label = [
        'mT-LocationRequestCurrentLocation',
        'mT-LocationRequestCurrentOrLastKnownLocation',
        'mO-LocationRequestLocEstimateToMS',
        'mO-LocationRequestLocEstimateToThirdParty',
        'mO-LocationRequestAssistData',
        'mO-LocationRequestDeciphKeys',
        'nI-LocationRequest',
        'mT-LocationRequestDeferred'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _TypeOfSignalling #
##############################
def _TypeOfSignalling(contents):
    label = [
        'iSUPIsNotAppliedAllTheWay',
        'iSUPIsAppliedAllTheWay',
        'unknownSignalling'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _UILayer1Protocol #
##############################
def _UILayer1Protocol(contents):
    label = [
        None,
        '{v110-X30',
        'g711mulaw',
        'g711Alaw',
        'g721-32000bps-I460',
        'h221-H242',
        'h223-H245',
        'nonITU-T',
        'v120',
        'x31',
        'vSELP-Speech'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _UnsuccessfulPositioningDataReason #
##############################
def _UnsuccessfulPositioningDataReason(contents):
    label = [
        'systemError',
        'userDeniedDueToPrivacyVerification'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _UserClass #
##############################
def _UserClass(contents):
    # only used for WCDMA Japan
    pass

##############################
# _UserRate #
##############################
def _UserRate(contents):
    label = [
        'uRIndNeg',
        'uR600bps',
        'uR1200bps',
        'uR2400bps',
        'uR3600bps',
        'uR4800bps',
        'uR7200bps',
        'uR8000bps',
        'uR9600bps',
        'uR14400bps',
        'uR16000bps',
        'uR19200bps',
        'uR32000bps',
        'uR38400bps',
        'uR48000bps',
        'uR56000bps',
        'uR64000bps',
        'uR38400bps1',
        'uR57600bps',
        'uR28800bps',
        None, # value=20 not used
        'uR134-5bps',
        'uR100bps',
        'uR75bps-1200bps',
        'uR1200bps-75bps',
        'uR50bps',
        'uR75bps',
        'uR110bps',
        'uR150bps',
        'uR200bps',
        'uR300bps',
        'uR12000bps'
    ]
    return _EnumeratedType(label, contents[0])

##############################
# _UserTerminalPosition #
##############################
def _UserTerminalPosition(contents):
    # review
    return _OctetString(contents)

##############################
# _UserToUserInformation #
##############################
def _UserToUserInformation(contents):
    # review
    return _OctetString(contents)

##############################
# _UserToUserService1Information #
##############################
def _UserToUserService1Information(contents):
    # review
    return _OctetString(contents)



##################################
# parameter to primitive mapping #
##################################
parameterMap = {
    'acceptableChannelCodings': _ChannelCodings,
    'acceptanceOfCallWaiting': None,
    'accountCode': _AccountCode,
    'aCMChargingIndicator': _ChargingIndicator,
    'ageOfLocationEstimate': _AgeOfLocationEstimate,
    'aIURRequested': _AirInterfaceUserRate,
    'aNMChargingIndicator': _ChargingIndicator,
    'aoCCurrencyAmountSent': _AoCCurrencyAmountSent,
    'bearerServiceCode': _BearerServiceCode,
    'bladeID': _BladeID,
    'bSSMAPCauseCode': _BSSMAPCauseCode,
    'buddyBladeIndicator': None,
    'callAttemptIndicator': None,
    'callAttemptState': _CallAttemptState,
    'calledDirectoryNumber': _AddressString,
    'calledPartyMNPInfo': _AddressString,
    'calledPartyNumber': _AddressString,
    'calledSubscriberIMEI': _IMEI,
    'calledSubscriberIMEISV': _IMEISV,
    'calledSubscriberIMSI': _IMSI,
    'callIdentificationNumber': _CallIDNumber,
    'callingPartyNumber': _AddressString,
    'callingPartyNumberSpecialArrangementInd': None,
    'callingSubscriberIMEI': _IMEI,
    'callingSubscriberIMEISV': _IMEISV,
    'callingSubscriberIMSI': _IMSI,
    'callPosition': _CallPosition,
    'cAMELCallingPartyNumber': _AddressString,
    'cAMELDestinationAddress': _AddressStringExtended,
    'cAMELInitiatedCallForwarding': None,
    'cAMELOriginatingAddress': _AddressStringExtended,
    'cAMELSMSCAddress': _AddressString,
    'carrierIdentificationCode': _CarrierIdentificationCode,
    'carrierInformation': _CarrierInformation,
    'carrierInformationBackward': _TransitCarrierInfo,
    'carrierInformationForward': _TransitCarrierInfo,
    'carrierSelectionSubstitutionInformation': _CarrierSelectionSubstitutionInformation,
    'causeCode': _CauseCode,
    'ccbsCallIndicator': None,
    'changeInitiatingParty': _ChangeInitiatingParty,
    'channelAllocationPriorityLevel': _ChannelAllocationPriorityLevel,
    'channelCodingUsed': _ChannelCodings,
    'chargeableDuration': _Time,
    'chargedCallingPartyNumber': _AddressString,
    'chargedParty': _ChargedParty,
    'chargeInformation': _ChargeInformation,
    'chargeNumber': _AddressString,
    'chargePartyDistributed': _Distributed,
    'chargePartySingle': _Single,
    'chargingCase': _ChargingCase,
    'chargingUnitsAddition': _ChargingUnitsAddition,
    'contractorNumber': _AddressString,
    'cRIIndicator': _CRIIndicator,
    'cRIToMS': _CRIToMS,
    'cUGIncomingAccessUsed': None,
    'cUGIndex': _CUGIndex,
    'cUGInterlockCode': _CUGInterlockCode,
    'cUGOutgoingAccessIndicator': None,
    'cUGOutgoingAccessUsed': None,
    'c7ChargingMessage': _C7ChargingMessage,
    'c7FirstCHTMessage': _C7CHTMessage,
    'c7SecondCHTMessage': _C7CHTMessage,
    'date': _Date,
    'dateForStartOfCharge': _Date,
    'decipheringKeys': _DecipheringKeys,
    'defaultCallHandling': _DefaultCallHandling,
    'defaultSMSHandling': _DefaultSMSHandling,
    'deliveryOfErroneousSDU1': _DeliveryOfErroneousSDU,
    'deliveryOfErroneousSDU2': _DeliveryOfErroneousSDU,
    'deliveryOfErroneousSDU3': _DeliveryOfErroneousSDU,
    'destinationAddress': _AddressStringExtended,
    'disconnectingParty': _DisconnectingParty,
    'disconnectionDate': _Date,
    'disconnectionDueToSystemRecovery': None,
    'disconnectionTime': _Time,
    'dTMFUsed': None,
    'emergencyServiceCategory': _EmergencyServiceCategory,
    'eMLPPPriorityLevel': _EMLPPPriorityLevel,
    'endToEndAccessDataMap': _EndToEndAccessDataMap,
    'entryPOICA': _ChargeAreaCode,
    'eosInfo': _EosInfo,
    'eventCRIToMS': _EventCRIToMS,
    'exchangeIdentity': _ExchangeIdentity,
    'exitPOICA': _ChargeAreaCode,
    'faultCode': _FaultCode,
    'firstAssignedSpeechCoderVersion': _SpeechCoderVersion,
    'firstCalledLocationInformation': _LocationInformation,
    'firstCalledLocationInformationExtension': _LocationInformationExtension,
    'firstCallingLocationInformation': _LocationInformation,
    'firstCallingLocationInformationExtension': _LocationInformationExtension,
    'firstRadioChannelUsed': _FirstRadioChannelUsed,
    'firstTargetLocationInformation': _LocationInformation,
    'flexibleCounter1': _Counter,
    'flexibleCounter2': _Counter,
    'flexibleCounter3': _Counter,
    'flexibleCounter4': _Counter,
    'flexibleCounter5': _Counter,
    'flexibleCounter6': _Counter,
    'flexibleCounter7': _Counter,
    'flexibleCounter8': _Counter,
    'fNURRequested': _FixedNetworkUserRate,
    'forloppDuringOutputIndicator': None,
    'forloppReleaseDuringCall': None,
    'freeFormatData': _FreeFormatData,
    'freeFormatDataAppendIndicator': None,
    'freeFormatDataAppendIndicator2': None,
    'frequencyBandSupported': _FrequencyBandSupported,
    'genericChargingDigits': _GenericDigitsSet,
    'genericChargingNumbers': _GenericNumbersSet,
    'globalCallReference': _GlobalCallReference,
    'gSMCallReferenceNumber': _GSMCallReferenceNumber,
    'gsmSCFAddress': _AddressString,
    'gsmSCFControlOfAoC': None,
    'gsmSCFInitiatedCallIndicator': None,
    'guaranteedBitRate': _BitRate,
    'horizontalAccuracy': _LCSAccuracy,
    'iCIOrdered': None,
    'incomingAssignedRoute': _Route,
    'incomingPChargingVector': _PChargingVector,
    'incomingRoute': _Route,
    'incompleteCallDataIndicator': None,
    'incompleteCompositeCDRIndicator': None,
    'iNMarkingOfMS': _INMarkingOfMS,
    'iNServiceTrigger': _INServiceTrigger,
    'interExchangeCarrierIndicator': None,
    'intermediateRate': _IntermediateRate,
    'internalCauseAndLoc': _InternalCauseAndLoc,
    'internationalCallIndicator': None,
    'interRegionHandoverIndicator': None,
    'interruptionTime': _Time,
    'invocationOfCallHold': None,
    'iuCodec': _IuCodec,
    'lastCalledLocationInformation': _LocationInformation,
    'lastCalledLocationInformationExtension': _LocationInformationExtension,
    'lastCallingLocationInformation': _LocationInformation,
    'lastPartialOutput': None,
    'lCSClientIdentity': _AddressString,
    'lCSClientType': _LCSClientType,
    'lCSDeferredEventType': _LCSDeferredEventType,
    'levelOfCAMELService': _LevelOfCAMELService,
    'locationCode': _LocationCode,
    'locationEstimate': _LocationEstimate,
    'maxBitRateDownlink': _BitRate,
    'maxBitRateUplink': _BitRate,
    'mCASMSIndicator': None,
    'messageReference': _MessageReference,
    'messageTypeIndicator': _MessageTypeIndicator,
    'miscellaneousInformation': _MiscellaneousInformation,
    'mLCAddress': _AddressString,
    'mMEIdentity': _MMEIdentity,
    'mMEName': _MMEName,
    'mobileStationRoamingNumber': _AddressString,
    'mobileStationRoamingNumberInfo': _AddressString,
    'mobileSubscriberNumberForHLRInterrogation': _AddressString,
    'mobileUserClass1': _MobileUserClass1,
    'mobileUserClass2': _MobileUserClass2,
    'mSCAddress': _AddressString,
    'mSCIdentification': _AddressString,
    'mSCNumber': _AddressString,
    'mTRFIndicator': None,
    'multimediaCall': None,
    'networkCallReference': _NetworkCallReference,
    'networkInitiatedUSSDOperations': _NumberOfOperations,
    'networkProvidedCallingPartyNumber': _AddressString,
    'numberOfChannelsRequested': _NumberOfChannels,
    'numberOfMeterPulses': _NumberOfMeterPulses,
    'numberOfShortMessages': _NumberOfShortMessage,
    'optimalRoutingInvocationFailed': None,
    'optimalRoutingType': _OptimalRoutingType,
    'originalCalledNumber': _AddressString,
    'originatedCode': _OriginatedCode,
    'originatingAccessISDN': None,
    'originatingAddress': _AddressStringExtended,
    'originatingCarrier': _CarrierInfo,
    'originatingChargeArea': _ChargeAreaCode,
    'originatingLineInformation': _OriginatingLineInformation,
    'originatingLocationNumber': _AddressString,
    'originForCharging': _ChargingOrigin,
    'outgoingAssignedRoute': _Route,
    'outgoingPChargingVector': _PChargingVector,
    'outgoingRoute': _Route,
    'outputForSubscriber': _OutputForSubscriber,
    'outputType': _OutputType,
    'partialOutputRecNum': _PartialOutputRecNum,
    'pChargingVectorRelated': _PChargingVectorRelated,
    'positionAccuracy': _PositionAccuracy,
    'positioningDelivery': _PositioningDelivery,
    'presentationAndScreeningIndicator': _PresentationAndScreeningIndicator,
    'radioChannelProperty': _RadioChannelProperty,
    'rANAPCauseCode': _RANAPCauseCode,
    'recordSequenceNumber': _RecordSequenceNumber,
    'redirectingDropBack': None,
    'redirectingDropBackNumber': _AddressString,
    'redirectingIMSI': _IMSI,
    'redirectingNumber': _AddressString,
    'redirectingSPN': _AddressString,
    'redirectionCounter': _RedirectionCounter,
    'regionalServiceUsed': _RegionalServiceUsed,
    'regionDependentChargingOrigin': _ChargingOrigin,
    'relatedCallNumber': _CallIDNumber,
    'reroutedToServiceCentreAddress': _AddressString,
    'reroutingIndicator': None,
    'residualBitErrorRatio1': _ErrorRatio,
    'residualBitErrorRatio2': _ErrorRatio,
    'residualBitErrorRatio3': _ErrorRatio,
    'responseTimeCategory': _ResponseTimeCategory,
    'restartDuringCall': None,
    'restartDuringOutputIndicator': None,
    'retrievalOfHeldCall': None,
    'rNCidOfFirstRNC': _TargetRNCid,
    'rNCidOfTargetRNC': _TargetRNCid,
    'roamingPriorityLevel': _RoamingPriorityLevel,
    'rTCDefaultServiceHandling': _RTCDefaultServiceHandling,
    'rTCFailureIndicator': _RTCFailureIndicator,
    'rTCIndicator': None,
    'rTCNotInvokedReason': _RTCNotInvokedReason,
    'rTCSessionID': _RTCSessionID,
    'sDUErrorRatio1': _ErrorRatio,
    'sDUErrorRatio2': _ErrorRatio,
    'sDUErrorRatio3': _ErrorRatio,
    'selectedCodec': _SelectedCodec,
    'servedSubscriberNumber': _AddressString,
    'serviceCentreAddress': _AddressString,
    'serviceFeatureCode': _ServiceFeatureCode,
    'serviceSwitchingType': _ServiceSwitchingType,
    'sMSReferenceNumber': _GSMCallReferenceNumber,
    'sMSResult': _SMSResult,
    'speechCoderPreferenceList': _SpeechCoderPreferenceList,
    'sRVCCAdditionalSessionIndicator': None,
    'sRVCCAlertingIndicator': _SRVCCAlertingIndicator,
    'sRVCCCallHoldIndicator': None,
    'sRVCCConferenceIndicator': None,
    'sRVCCIndicator': _SRVCCIndicator,
    'sRVCCOriginatingPreAlertingIndicator': None,
    'sSCode': _SSCode,
    'sSFLegID': _LegID,
    'sSFChargingCase': _SSFChargingCase,
    'sSInvocationNotification': None,
    'sSRequest': _SSRequest,
    'subscriberState': _SubscriberState,
    'subscriptionType': _SubscriptionType,
    'switchIdentity': _SwitchIdentity,
    'tAC': _TAC,
    'targetIMEI': _IMEI,
    'targetIMEISV': _IMEISV,
    'targetIMSI': _IMSI,
    'targetLocationInformation': _LocationInformation,
    'targetMSISDN': _AddressString,
    'tariffClass': _TariffClass,
    'tariffSwitchInd': _TariffSwitchInd,
    'tDSCounter': _Counter,
    'teleServiceCode': _TeleServiceCode,
    'terminatingAccessISDN': None,
    'terminatingCarrier': _CarrierInfo,
    'terminatingChargeArea': _ChargeAreaCode,
    'terminatingLocationNumber': _AddressString,
    'terminatingMobileUserClass1': _MobileUserClass1,
    'terminatingMobileUserClass2': _MobileUserClass2,
    'terminatingUserClass': _UserClass,
    'timeForEvent': _Time,
    'timeForStartOfCharge': _Time,
    'timeForStopOfCharge': _Time,
    'timeForTCSeizureCalled': _Time,
    'timeForTCSeizureCalling': _Time,
    'timeFromRegisterSeizureToStartOfCharging': _Time,
    'trafficActivityCode': _TrafficActivityCode,
    'trafficClass': _TrafficClass,
    'trafficIsolationIndicator': None,
    'transferDelay': _TransferDelay,
    'translatedNumber': _AddressString,
    'transparencyIndicator': _TransparencyIndicator,
    'typeOfCalledSubscriber': _TypeOfCalledSubscriber,
    'typeOfCallingSubscriber': _TypeOfCallingSubscriber,
    'typeOfLocationRequest': _TypeOfLocationRequest,
    'typeOfSignalling': _TypeOfSignalling,
    'uETimeZone': _Timezone,
    'unsuccessfulPositioningDataReason': _UnsuccessfulPositioningDataReason,
    'userClass': _UserClass,
    'userProvidedCallingPartyNumber': _AddressString,
    'userTerminalPosition': _UserTerminalPosition,
    'userToUserInformation': _UserToUserInformation,
    'userToUserService1Information': _UserToUserService1Information,
    'uSSDApplicationIdentifier': _ApplicationIdentifier,
    'uSSDOperationIdentifier': _OperationIdentifier,
    'uSSDProcedureCode': _ProcedureCode,
    'uSSDServiceCode': _ServiceCode,
    'verticalAccuracy': _LCSAccuracy,
    'verticalCoordinateRequest': None,
    'wPSCallIndicator': None,
    # these parameters are inside constructors
    'serviceKey': _ServiceKey,
    'userRate': _UserRate,
    'asyncSyncIndicator': _AsyncSyncIndicator,
    'uILayer1Protocol': _UILayer1Protocol,
    'triggerDetectionPoint': _TriggerDetectionPoint,
    'co-located': None,
    'pointCodeAndSubSystemNumber': _PointCodeAndSubSystemNumber,
    'globalTitle': _GlobalTitle,
    'globalTitleAndSubSystemNumber': _GlobalTitleAndSubSystemNumber,
    # default display method when for unknown tags
    'default': _Raw,
}



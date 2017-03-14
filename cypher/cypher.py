#!/usr/bin/python

import os
import datetime
import time

#
# support functions
#
def normalise(address, country_code=None):
    if country_code is None:
        country_code = '61'

    pos = address.rfind('=') + 1
    digits = address[pos:]

    # no modification required if already international number
    if address.find('TON=1,') == 0:
        return digits

    if address.find('TON=2,') == 0:
        if digits.find('0011') == 0:
            return digits[4:]

        if digits.find('0') == 0:
            return country_code + digits[1:]

    # everything else
    return digits


############################################################
#   base class definition                                  #
############################################################
class CallDetailRecord:
    # class variables go here

    def __init__(self):
        self.name = ''
        self.field = {}

    def set(self, key=None, value=None):
        if key is not None and key in self.field:
            self.field[key] = value


############################################################
#   call modules                                           #
############################################################
class callForwarding(CallDetailRecord):
    def __init__(self):
        self.name = 'callForwarding'

        # dictionary for the cdr fields
        self.field = {
            'callPosition': None,
            'chargeableDuration': None,
            'dateForStartOfCharge': None,
            'exchangeIdentity': None,
            'interruptionTime': None,
            'recordSequenceNumber': None,
            'tariffClass': None,
            'tariffSwitchInd': None,
            'timeForStartOfCharge': None,
            'timeForStopOfCharge': None,
            'outputType': None,
            'switchIdentity': None,
            'bladeID': None,
            'mSCIdentification': None,
            'redirectingIMSI': None,
            'mobileStationRoamingNumber': None,
            'calledPartyNumber': None,
            'networkCallReference': None,
            'callingPartyNumber': None,
            'incomingRoute': None,
            'originalCalledNumber': None,
            'originatedCode': None,
            'presentationAndScreeningIndicator': None,
            'redirectingNumber': None,
            'redirectionCounter': None,
            'callIdentificationNumber': None,
            'typeOfCallingSubscriber': None,
            'tAC': None,
            'subscriptionType': None,
            'originForCharging': None,
            'chargedParty': None,
            'timeFromRegisterSeizureToStartOfCharging': None,
            'internalCauseAndLoc': None,
            'translatedNumber': None,
            'outgoingRoute': None,
            'eosInfo': None,
            'disconnectingParty': None,
        }

    def cypher(self):
        # a:Subscriber {msisdn: callingPartyNumber}
        # b:Subscriber {msisdn: redirectingNumber}
        # c:Subscriber {msisdn: calledPartyNumber}
        amsisdn = normalise(self.field['callingPartyNumber'])
        bmsisdn = normalise(self.field['redirectingNumber'])
        cmsisdn = normalise(self.field['calledPartyNumber'])
        callId = int(self.field['callIdentificationNumber'])
        command = 'merge (a:Subscriber {msisdn: "%s"}) ' % amsisdn
        command = command + 'merge (b:Subscriber {msisdn: "%s"}) ' % bmsisdn
        command = command + 'merge (c:Subscriber {msisdn: "%s"}) ' % cmsisdn
        z = '(z:CallForward {callId: %d})' % callId
        command = command + 'create (a)-[:CALLING]->%s-[:REDIRECTING]->(b) ' % z
        command = command + 'create (z)-[:CALLED]->(c) '
        return command


class mSOriginatingSMSinMSC(CallDetailRecord):
    def __init__(self):
        self.name = 'mSOriginatingSMSinMSC'
        # set timezone to Australia/Brisbane
        os.environ['TZ'] = 'Australia/Brisbane'

        # dictionary for the cdr fields
        self.field = {
            'dateForStartOfCharge': None,
            'exchangeIdentity': None,
            'recordSequenceNumber': None,
            'timeForStartOfCharge': None,
            'outputType': None,
            'switchIdentity': None,
            'bladeID': None,
            'callIdentificationNumber': None,
            'chargedParty': None,
            'callingSubscriberIMSI': None,
            'firstCallingLocationInformation': None,
            'firstCallingLocationInformationExtension': None,
            'teleServiceCode': None,
            'tAC': None,
            'typeOfCallingSubscriber': None,
            'callingSubscriberIMEI': None,
            'callingSubscriberIMEISV': None,
            'originForCharging': None,
            'callingPartyNumber': None,
            'mSCIdentification': None,
            'serviceCentreAddress': None,
            'messageReference': None,
            'messageTypeIndicator': None,
            'destinationAddress': None,
            'mMEName': None,
            'uETimeZone': None,
        }

    def cypher(self):
        # a:Subscriber {msisdn: callingPartyNumber}
        # b:Subscriber {msisdn: destinationAddress}
        # s:Sms {callId: callIdentificationNumber}
        amsisdn = normalise(self.field['callingPartyNumber'])
        bmsisdn = normalise(self.field['destinationAddress'])
        callId = int(self.field['callIdentificationNumber'])

        # dateForStartOfCharge and timeForStartOfCharge
        tsCharge = self.field['dateForStartOfCharge'] + ' ' + self.field['timeForStartOfCharge']
        dt = datetime.datetime.strptime(tsCharge, '%d/%m/%y %H:%M:%S')
        callTime = [dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second, 0, 0, 0]
        ts = int(time.mktime(callTime))

        # firstCallingLocationInformation
        ptr = self.field['firstCallingLocationInformation'].find('LAC')
        lacsac = self.field['firstCallingLocationInformation'][ptr:]
        cell = lacsac.lower().replace('=', ':')

        # callingSubscriberIMEI
        tac = int(self.field['callingSubscriberIMEI'][0:8])

        command = 'merge (a:Subscriber {msisdn: "%s"}) ' % amsisdn
        command = command + 'merge (b:Subscriber {msisdn: "%s"}) ' % bmsisdn
        s = '(s:Sms {type: "mo", callId: %d, ts: %d})' %(callId, ts)
        command = command + 'create (a)-[:SENT_SMS]->%s<-[:RECEIVED_SMS]-(b) ' % s
        command = command + 'merge (c:Cell {%s}) ' % cell
        command = command + 'create (s)-[:AT]->(c) '
        command = command + 'merge (p:Phone {tac: %d}) ' % tac
        command = command + 'merge (a)-[:USES]->(p) '

        return command


class mSTerminatingSMSinMSC(CallDetailRecord):
    def __init__(self):
        self.name = 'mSTerminatingSMSinMSC'

        # dictionary for the cdr fields
        self.field = {
            'dateForStartOfCharge': None,
            'exchangeIdentity': None,
            'recordSequenceNumber': None,
            'timeForStartOfCharge': None,
            'outputType': None,
            'switchIdentity': None,
            'bladeID': None,
            'callIdentificationNumber': None,
            'chargedParty': None,
            'calledSubscriberIMEI': None,
            'calledSubscriberIMEISV': None,
            'calledSubscriberIMSI': None,
            'firstCalledLocationInformation': None,
            'firstCalledLocationInformationExtension': None,
            'lastCalledLocationInformation': None,
            'lastCalledLocationInformationExtension': None,
            'uETimeZone': None,
            'numberOfShortMessages': None,
            'calledPartyNumber': None,
            'teleServiceCode': None,
            'mSCIdentification': None,
            'serviceCentreAddress': None,
            'tAC': None,
            'originForCharging': None,
            'messageTypeIndicator': None,
            'originatingAddress': None,
        }

    def cypher(self):
        # a:Subscriber {msisdn: originatingAddress}
        # b:Subscriber {msisdn: calledPartyNumber}
        # s:Sms {callId: callIdentificationNumber}
        amsisdn = normalise(self.field['originatingAddress'])
        bmsisdn = normalise(self.field['calledPartyNumber'])
        callId = int(self.field['callIdentificationNumber'])

        # dateForStartOfCharge and timeForStartOfCharge
        tsCharge = self.field['dateForStartOfCharge'] + ' ' + self.field['timeForStartOfCharge']
        dt = datetime.datetime.strptime(tsCharge, '%d/%m/%y %H:%M:%S')
        callTime = [dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second, 0, 0, 0]
        ts = int(time.mktime(callTime))

        # firstCalledLocationInformation
        ptr = self.field['firstCalledLocationInformation'].find('LAC')
        lacsac = self.field['firstCalledLocationInformation'][ptr:]
        cell = lacsac.lower().replace('=', ':')

        # calledSubscriberIMEI
        tac = int(self.field['calledSubscriberIMEI'][0:8])

        command = 'merge (a:Subscriber {msisdn: "%s"}) ' % amsisdn
        command = command + 'merge (b:Subscriber {msisdn: "%s"}) ' % bmsisdn
        s = '(:Sms {type: "mt", callId: %d})' % callId
        command = command + 'create (a)-[:SENT_SMS]->%s<-[:RECEIVED_SMS]-(b)' % s
        command = command + 'merge (c:Cell {%s}) ' % cell
        command = command + 'create (s)-[:AT]->(c) '
        command = command + 'merge (p:Phone {tac: %d}) ' % tac
        command = command + 'merge (b)-[:USES]->(p) '
        return command



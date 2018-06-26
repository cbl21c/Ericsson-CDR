#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "components.h"

#define MAX_PRIMITIVES 300

#define NAME_MAX_LEN 48

#define HI_BITS 0xf0
#define LO_BITS 0x0f

#define BIT8 0x80
#define BIT7 0x40
#define BIT6 0x20
#define BIT5 0x10
#define BIT4 0x08
#define BIT3 0x04
#define BIT2 0x02
#define BIT1 0x01

#define ODD  1
#define EVEN 2

byte output[MAX_LINE_LEN];
byte digits[MAX_LINE_LEN];

asn1Object primitive[MAX_PRIMITIVES];
asn1Object *camelTDPData[2];
asn1Object *multimediaInformation[3];
asn1Object *triggerData[6];

char *primitiveName[MAX_PRIMITIVES] = {
    "acceptableChannelCodings",
    "acceptanceOfCallWaiting",
    "accountCode",
    "aCMChargingIndicator",
    "ageOfLocationEstimate",
    "aIURRequested",
    "aNMChargingIndicator",
    "aoCCurrencyAmountSent",
    "bearerServiceCode",
    "bladeID",
    "bSSMAPCauseCode",
    "buddyBladeIndicator",
    "callAttemptIndicator",
    "callAttemptState",
    "calledDirectoryNumber",
    "calledPartyMNPInfo",
    "calledPartyNumber",
    "calledSubscriberIMEI",
    "calledSubscriberIMEISV",
    "calledSubscriberIMSI",
    "callIdentificationNumber",
    "callingPartyNumber",
    "callingPartyNumberSpecialArrangementInd",
    "callingSubscriberIMEI",
    "callingSubscriberIMEISV",
    "callingSubscriberIMSI",
    "callPosition",
    "cAMELCallingPartyNumber",
    "cAMELDestinationAddress",
    "cAMELInitiatedCallForwarding",
    "cAMELOriginatingAddress",
    "cAMELSMSCAddress",
    "carrierIdentificationCode",
    "carrierInformation",
    "carrierInformationBackward",
    "carrierInformationForward",
    "carrierSelectionSubstitutionInformation",
    "causeCode",
    "ccbsCallIndicator",
    "changeInitiatingParty",
    "channelAllocationPriorityLevel",
    "channelCodingUsed",
    "chargeableDuration",
    "chargedCallingPartyNumber",
    "chargedParty",
    "chargeInformation",
    "chargeNumber",
    "chargePartyDistributed",
    "chargePartySingle",
    "chargingCase",
    "chargingUnitsAddition",
    "contractorNumber",
    "cRIIndicator",
    "cRIToMS",
    "cUGIncomingAccessUsed",
    "cUGIndex",
    "cUGInterlockCode",
    "cUGOutgoingAccessIndicator",
    "cUGOutgoingAccessUsed",
    "c7ChargingMessage",
    "c7FirstCHTMessage",
    "c7SecondCHTMessage",
    "date",
    "dateForStartOfCharge",
    "decipheringKeys",
    "defaultCallHandling",
    "defaultCallHandling2",
    "defaultSMSHandling",
    "deliveryOfErroneousSDU1",
    "deliveryOfErroneousSDU2",
    "deliveryOfErroneousSDU3",
    "destinationAddress",
    "disconnectingParty",
    "disconnectionDate",
    "disconnectionDueToSystemRecovery",
    "disconnectionTime",
    "dTMFUsed",
    "emergencyServiceCategory",
    "eMLPPPriorityLevel",
    "endToEndAccessDataMap",
    "entryPOICA",
    "eosInfo",
    "eventCRIToMS",
    "exchangeIdentity",
    "exitPOICA",
    "faultCode",
    "firstAssignedSpeechCoderVersion",
    "firstCalledLocationInformation",
    "firstCalledLocationInformationExtension",
    "firstCallingLocationInformation",
    "firstCallingLocationInformationExtension",
    "firstRadioChannelUsed",
    "firstTargetLocationInformation",
    "flexibleCounter1",
    "flexibleCounter2",
    "flexibleCounter3",
    "flexibleCounter4",
    "flexibleCounter5",
    "flexibleCounter6",
    "flexibleCounter7",
    "flexibleCounter8",
    "fNURRequested",
    "forloppDuringOutputIndicator",
    "forloppReleaseDuringCall",
    "freeFormatData",
    "freeFormatData2",
    "freeFormatDataAppendIndicator",
    "freeFormatDataAppendIndicator2",
    "frequencyBandSupported",
    "genericChargingDigits",
    "genericChargingNumbers",
    "globalCallReference",
    "gSMCallReferenceNumber",
    "gsmSCFAddress",
    "gsmSCFControlOfAoC",
    "gsmSCFInitiatedCallIndicator",
    "guaranteedBitRate",
    "horizontalAccuracy",
    "iCIOrdered",
    "incomingAssignedRoute",
    "incomingPChargingVector",
    "incomingRoute",
    "incompleteCallDataIndicator",
    "incompleteCompositeCDRIndicator",
    "iNMarkingOfMS",
    "iNServiceTrigger",
    "interExchangeCarrierIndicator",
    "intermediateRate",
    "internalCauseAndLoc",
    "internationalCallIndicator",
    "interRegionHandoverIndicator",
    "interruptionTime",
    "invocationOfCallHold",
    "iuCodec",
    "lastCalledLocationInformation",
    "lastCalledLocationInformationExtension",
    "lastCallingLocationInformation",
    "lastPartialOutput",
    "lCSClientIdentity",
    "lCSClientType",
    "lCSDeferredEventType",
    "levelOfCAMELService",
    "locationCode",
    "locationEstimate",
    "maxBitRateDownlink",
    "maxBitRateUplink",
    "mCASMSIndicator",
    "messageReference",
    "messageTypeIndicator",
    "miscellaneousInformation",
    "mLCAddress",
    "mMEIdentity",
    "mMEName",
    "mobileStationRoamingNumber",
    "mobileStationRoamingNumberInfo",
    "mobileSubscriberNumberForHLRInterrogation",
    "mobileUserClass1",
    "mobileUserClass2",
    "mSCAddress",
    "mSCIdentification",
    "mSCNumber",
    "mTRFIndicator",
    "multimediaCall",
    "networkCallReference",
    "networkInitiatedUSSDOperations",
    "networkProvidedCallingPartyNumber",
    "numberOfChannelsRequested",
    "numberOfMeterPulses",
    "numberOfShortMessages",
    "optimalRoutingInvocationFailed",
    "optimalRoutingType",
    "originalCalledNumber",
    "originatedCode",
    "originatingAccessISDN",
    "originatingAddress",
    "originatingCarrier",
    "originatingChargeArea",
    "originatingLineInformation",
    "originatingLocationNumber",
    "originForCharging",
    "outgoingAssignedRoute",
    "outgoingPChargingVector",
    "outgoingRoute",
    "outputForSubscriber",
    "outputType",
    "partialOutputRecNum",
    "pChargingVectorRelated",
    "positionAccuracy",
    "positioningDelivery",
    "presentationAndScreeningIndicator",
    "radioChannelProperty",
    "rANAPCauseCode",
    "recordSequenceNumber",
    "redirectingDropBack",
    "redirectingDropBackNumber",
    "redirectingIMSI",
    "redirectingNumber",
    "redirectingSPN",
    "redirectionCounter",
    "regionalServiceUsed",
    "regionDependentChargingOrigin",
    "relatedCallNumber",
    "reroutedToServiceCentreAddress",
    "reroutingIndicator",
    "residualBitErrorRatio1",
    "residualBitErrorRatio2",
    "residualBitErrorRatio3",
    "responseTimeCategory",
    "restartDuringCall",
    "restartDuringOutputIndicator",
    "retrievalOfHeldCall",
    "rNCidOfFirstRNC",
    "rNCidOfTargetRNC",
    "roamingPriorityLevel",
    "rTCDefaultServiceHandling",
    "rTCFailureIndicator",
    "rTCIndicator",
    "rTCNotInvokedReason",
    "rTCSessionID",
    "sDUErrorRatio1",
    "sDUErrorRatio2",
    "sDUErrorRatio3",
    "selectedCodec",
    "servedSubscriberNumber",
    "serviceCentreAddress",
    "serviceFeatureCode",
    "serviceSwitchingType",
    "sMSReferenceNumber",
    "sMSResult",
    "speechCoderPreferenceList",
    "sRVCCAdditionalSessionIndicator",
    "sRVCCAlertingIndicator",
    "sRVCCCallHoldIndicator",
    "sRVCCConferenceIndicator",
    "sRVCCIndicator",
    "sRVCCOriginatingPreAlertingIndicator",
    "sSCode",
    "sSFLegID",
    "sSFChargingCase",
    "sSInvocationNotification",
    "sSRequest",
    "subscriberState",
    "subscriptionType",
    "switchIdentity",
    "tAC",
    "targetIMEI",
    "targetIMEISV",
    "targetIMSI",
    "targetLocationInformation",
    "targetMSISDN",
    "tariffClass",
    "tariffSwitchInd",
    "tDSCounter",
    "teleServiceCode",
    "terminatingAccessISDN",
    "terminatingCarrier",
    "terminatingChargeArea",
    "terminatingLocationNumber",
    "terminatingMobileUserClass1",
    "terminatingMobileUserClass2",
    "terminatingUserClass",
    "timeForEvent",
    "timeForStartOfCharge",
    "timeForStopOfCharge",
    "timeForTCSeizureCalled",
    "timeForTCSeizureCalling",
    "timeFromRegisterSeizureToStartOfCharging",
    "trafficActivityCode",
    "trafficClass",
    "trafficIsolationIndicator",
    "transferDelay",
    "translatedNumber",
    "transparencyIndicator",
    "typeOfCalledSubscriber",
    "typeOfCallingSubscriber",
    "typeOfLocationRequest",
    "typeOfSignalling",
    "uETimeZone",
    "unsuccessfulPositioningDataReason",
    "userClass",
    "userProvidedCallingPartyNumber",
    "userTerminalPosition",
    "userToUserInformation",
    "userToUserService1Information",
    "uSSDApplicationIdentifier",
    "uSSDOperationIdentifier",
    "uSSDProcedureCode",
    "uSSDServiceCode",
    "verticalAccuracy",
    "verticalCoordinateRequest",
    "wPSCallIndicator",
    /* these parameters are inside constructors */
    "serviceKey",
    "userRate",
    "asyncSyncIndicator",
    "uILayer1Protocol",
    "triggerDetectionPoint",
    "co-located",
    "pointCodeAndSubSystemNumber",
    "globalTitle",
    "globalTitleAndSubSystemNumber"
};


/*
 * enumerated types
 */
char *airInterfaceUserRateLabel[] = {
    "(unknown)",
    "aIUR9600bps",
    "aIUR14400bps",
    "aIUR19200bps",
    "(unknown)",
    "aIUR28800bps",
    "aIUR38400bps",
    "aIUR43200bps",
    "aIUR57600bps",
    "aIUR38400bps1",
    "aIUR38400bps2",
    "aIUR38400bps3",
    "aIUR38400bps4"
};

char *asyncSyncIndicatorLabel[] = {
    "syncData",
    "asyncData"
};

char *callPositionLabel[] = {
    "valueUsedForAllCallsToDetermineIfOutputToTakePlace",
    "callHasReachedCongestionOrBusyState",
    "callHasOnlyReachedThroughConnection",
    "b-AnswerHasBeenReceived"
};

char *chargedPartyLabel[] = {
    "chargingOfCallingSubscriber",
    "chargingOfCalledSubscriber",
    "noCharge"
};

char *defaultCallHandlingLabel[] = {
    "continueCall",
    "releaseCall"
};

char *deliveryOfErroneousSDULabel[] = {
    "yes",
    "no",
    "noErrorDetectionConsideration"
};

char *disconnectingPartyLabel[] = {
    "callingPartyRelease",
    "calledPartyRelease",
    "networkRelease"
};

char *iNMarkingOfMSLabel[] = {
    "unknown",
    "originatingINService",
    "terminatingINService",
    "originatingINCategoryKeyService",
    "terminatingINCategoryKeyService",
    "originatingCAMELService",
    "terminatingCAMELService",
    "originatingExtendedCAMELServiceWithINCapabilityIndicator",
    "terminatingExtendedCAMELServiceWithINCapabilityIndicator",
    "originatingExtendedCAMELServiceWithOriginatingINCategoryKey",
    "terminatingExtendedCAMELServiceWithTerminatingINCategoryKey",
    "subscriberDialledCAMELService",
    "subscriberDialledCAMELServiceAndOriginatingCAMELService",
    "visitedTerminatingCAMELService"
};

char *originatedCodeLabel[] = {
    "callOriginatingFromOwnSubscriberInSSN",
    "callOriginatingFromOwnSubscriberInGSN",
    "callOriginatingFromIncomingTrunk",
    "callOriginatingFromSUSblock",
    "callOriginatingFromOMSblock",
    "testCallTowardsIL-OL-BL",
    "testCallWithIndividualSelectionOfB-Subscriber",
    "testCallWithIndividualSelectionExceptB-Subscriber",
    "testCallWithSelectionInSpecifiedRoute",
    "operator"
};

char *outputForSubscriberLabel[] = {
    "callingParty",
    "calledParty",
    "callingAndCalledParty"
};

char *outputTypeLabel[] = {
    "noOutput",
    "iCIoutputForCallingSubscriber",
    "iCIOutputForCalledSubscriber",
    "iCIOutputForCallingAndCalledSubscribers",
    "tTOutputOnly",
    "tTAndICIForCallingSubscriber",
    "tTAndICIForCalledSubscriber",
    "tTAndICIForCallingAndCalledSubscribers"
};

char *rTCDefaultServiceHandlingLabel[] = {
    "serviceAllowed",
    "serviceNotAllowed"
};

char *rTCNotInvokedReasonLabel[] = {
    "emergencyCall",
    "callToSpecialDestination",
    "callLegNotToBeCharged",
    "smsNotToBeCharged",
    "mcaSMSFreeOfCharge",
    "undeterminedRoamingPLMN"
};

char *speechCoderVersionLabel[] = {
    "fullRateVersion1",
    "fullRateVersion2",
    "fullRateVersion3",
    "halfRateVersion1",
    "halfRateVersion2",
    "halfRateVersion3",
    "fullRateVersion5"
};

char *tariffSwitchIndLabel[] = {
    "noTariffSwitch",
    "unknown",
    "tariffSwitchAfterStartOfCharging"
};

char *typeOfCalledSubscriber[] = {
    "pSTNSubscriber",
    "iSDNSubscriber",
    "unknownSubscriber"
};

char *uILayer1ProtocolLabel[] = {
    "(unknown)"
    "v110-X30",
    "g711mulaw",
    "g711Alaw",
    "g721-32000bps-I460",
    "h221-H242",
    "h223-H245",
    "nonITU-T",
    "v120",
    "x31",
    "vSELP-Speech"
};

char *userRateLabel[] = {
    "uRIndNeg",
    "uR600bps",
    "uR1200bps",
    "uR2400bps",
    "uR3600bps",
    "uR4800bps",
    "uR7200bps",
    "uR8000bps",
    "uR9600bps",
    "uR14400bps",
    "uR16000bps",
    "uR19200bps",
    "uR32000bps",
    "uR38400bps",
    "uR48000bps",
    "uR56000bps",
    "uR64000bps",
    "uR38400bps1",
    "uR57600bps",
    "uR28800bps",
    "uR134-5bps",
    "uR100bps",
    "uR75bps-1200bps",
    "uR1200bps-75bps",
    "uR50bps",
    "uR75bps",
    "uR110bps",
    "uR150bps",
    "uR200bps",
    "uR300bps",
    "uR12000bps"
};



/* ######################################################################## */
/* # Generic and Common Types                                               */
/* ######################################################################## */

char GSMCHAR[128];
void *gsmchar_initialise(void)
{
    int n;

    /* most of these will align with ascii */
    for (n = 32; n < 128; n++)
        GSMCHAR[n] = n;

    /* these are the exceptions */
    GSMCHAR[0x24] = '\xa4';
    GSMCHAR[0x40] = '\xa1';
    GSMCHAR[0x5b] = '\xc4';
    GSMCHAR[0x5c] = '\xd6';
    GSMCHAR[0x5d] = '\xd1';
    GSMCHAR[0x5e] = '\xdc';
    GSMCHAR[0x5f] = '\xa7';
    GSMCHAR[0x60] = '\xbf';
    GSMCHAR[0x7b] = '\xe4';
    GSMCHAR[0x7c] = '\xf6';
    GSMCHAR[0x7d] = '\xf1';
    GSMCHAR[0x7e] = '\xfc';
    GSMCHAR[0x7f] = '\xe0';

    /* these are the remaining chars - mask LF and CR */
    GSMCHAR[0x00] = '@';
    GSMCHAR[0x01] = '\xa3';
    GSMCHAR[0x02] = '$';
    GSMCHAR[0x03] = '\xa5';
    GSMCHAR[0x04] = '\xe8';
    GSMCHAR[0x05] = '\xe9';
    GSMCHAR[0x06] = '\xf9';
    GSMCHAR[0x07] = '\xec';
    GSMCHAR[0x08] = '\xf2';
    GSMCHAR[0x09] = '\xc7';
    GSMCHAR[0x0a] = 0;
    GSMCHAR[0x0b] = '\xd8';
    GSMCHAR[0x0c] = '\xf8';
    GSMCHAR[0x0d] = 0;
    GSMCHAR[0x0e] = '\xc5';
    GSMCHAR[0x0f] = '\xe5';
    GSMCHAR[0x10] = 0;
    GSMCHAR[0x11] = '_';
    GSMCHAR[0x12] = 0;
    GSMCHAR[0x13] = 0;
    GSMCHAR[0x14] = 0;
    GSMCHAR[0x15] = 0;
    GSMCHAR[0x16] = 0;
    GSMCHAR[0x17] = 0;
    GSMCHAR[0x18] = 0;
    GSMCHAR[0x19] = 0;
    GSMCHAR[0x1a] = 0;
    GSMCHAR[0x1b] = 0;
    GSMCHAR[0x1c] = '\xc6';
    GSMCHAR[0x1d] = '\xe6';
    GSMCHAR[0x1e] = '\xdf';
    GSMCHAR[0x1f] = '\xc9';
}

/* s needs to be unsigned so that we can add bit0 value */
char* gsmchar_decode(int len, byte *s)
{
    int  n, nbits, remain, out, aptr;
    // char addr[MAX_LINE_LEN];

    aptr = 0;
    nbits = 0;
    remain = 0;
    memset(digits, 0, MAX_LINE_LEN);

    for (n = 0; n < len; n++)
    {
        out = ((s[n] << nbits) + remain) & 0x7f;
        if (GSMCHAR[out])
            digits[aptr++] = GSMCHAR[out];
        nbits = (nbits + 1) % 7;
        remain = s[n] >> (8 - nbits);

        /* if we reach a multiple of 7, we should output two bytes */
        if (nbits == 0)
        {
            out = s[n] >> 1;
            if (GSMCHAR[out])
                digits[aptr++] = GSMCHAR[out];
        }
    }

    /* if the last char is '@', it's probably there only because 7 bits remain */
    if (out == 0)
        digits[aptr - 1] = 0;

    return digits;
}


/* ############################## */
/* # _Enumerated                # */
/* ############################## */
char* _Enumerated(int index, int max, char **label)
{
    memset(output, 0, MAX_LINE_LEN);
    if (index >= max)
        sprintf(output, "%d (unknown)", index, label[index]);
    else
        sprintf(output, "%d (%s)", index, label[index]);

    return output;
}

/* ############################## */
/* # _Integer                   # */
/* ############################## */
char* _Integer(int len, byte *contents)
{
    int value, n;

    memset(output, 0, MAX_LINE_LEN);
    value = 0;
    for (n = 0; n < len; n++)
        value = value * 256 + contents[n];

    memset(output, 0, MAX_LINE_LEN);
    sprintf(output, "%d", value);
    return output;
}

/* ############################## */
/* # _Null                      # */
/* ############################## */
char* _Null(int len, byte *contents)
{
    return NULL;
}

/* ############################## */
/* # _OctetString               # */
/* ############################## */
char* _OctetString(int len, byte *contents)
{
    int n;

    memset(output, 0, MAX_LINE_LEN);
    strcpy(output, "0x");
    for (n = 0; n < len; n++)
        sprintf(output + (n + 1) * 2, "%02x", contents[n]);

    return output;
}

/* ############################## */
/* # _String                    # */
/* ############################## */
char* _String(int len, byte *contents)
{
    // printf("_String()\n");
    memset(output, 0, MAX_LINE_LEN);
    /* len + 1 because of null terminating byte */
    snprintf(output, len + 1, "%s", contents);
    return output;
}

/* ############################## */
/* # _TBCDString                # */
/* ############################## */
char* _TBCDString(int len, byte *contents)
{
    int  n, dig1, dig2;

    memset(output, 0, MAX_LINE_LEN);
    for (n = 0; n < len; n++)
    {
        dig1 = contents[n] & LO_BITS;
        dig2 = contents[n] >> 4;


        if (dig1 != 0x0f)
            sprintf(output + n * 2, "%x", dig1);
        if (dig2 != 0x0f)
            sprintf(output + n * 2 + 1, "%x", dig2);
    }

    return output;
}


/* ######################################################################## */
/* # Call Data Parameter Data Types (Section 5.2)                           */
/* ######################################################################## */

/* ############################## */
/* # _AddressString #              */
/* ############################## */
char* _AddressString(int len, byte *contents)
{
    int  ton, npi;

    ton = contents[0] >> 4;
    npi = (contents[0] & LO_BITS);
    if (ton == 14)
    {
        gsmchar_decode(len - 1, contents + 1);
        sprintf(output, "TON=%d NPI=%d Addr=%s", ton, npi, digits);
    }
    else
    {
        strcpy(digits, _TBCDString(len - 1, contents + 1));
        sprintf(output, "TON=%d NPI=%d Digits=%s", ton, npi, digits);
    }

    return output;
}

/* ############################## */
/* # _AirInterfaceUserRate #              */
/* ############################## */
char* _AirInterfaceUserRate(int len, byte *contents)
{
    return _Enumerated(contents[0], 13, airInterfaceUserRateLabel);
}

/* ############################## */
/* # _AsyncSyncIndicator #              */
/* ############################## */
char* _AsyncSyncIndicator(int len, byte *contents)
{
    return _Enumerated(contents[0], 2, asyncSyncIndicatorLabel);
}

/* ############################## */
/* # _CallPosition #              */
/* ############################## */
char* _CallPosition(int len, byte *contents)
{
    return _Enumerated(contents[0], 4, callPositionLabel);
}

/* ############################## */
/* # _ChannelCodings #              */
/* ############################## */
char* _ChannelCodings(int len, byte *contents)
{
    memset(output, 0, MAX_LINE_LEN);
    if (contents[0] & BIT4)
        sprintf(output, "14.4 ");
    if (contents[0] & BIT2)
        sprintf(output + strlen(output), "9.6 ");
    if (contents[0] & BIT1)
        sprintf(output + strlen(output), "4.8 ");

    sprintf(output + strlen(output), "kbps");
}

/* ############################## */
/* # _ChargedParty #              */
/* ############################## */
char* _ChargedParty(int len, byte *contents)
{
    return _Enumerated(contents[0], 3, chargedPartyLabel);
}

/* ############################## */
/* # _Date #                      */
/* ############################## */
char* _Date(int len, byte *contents)
{
    int dd, mm, yy, cc;

    if (len == 3)
    {
        yy = contents[0];
        mm = contents[1];
        dd = contents[2];
    }
    else if (len == 4)
    {
        cc = contents[0];
        yy = contents[1] + cc * 100;
        mm = contents[2];
        dd = contents[3];
    }

    sprintf(output, "%02d/%02d/%02d", dd, mm, yy);
    return output;
}

/* ############################## */
/* # _DefaultCallHandling #              */
/* ############################## */
char* _DefaultCallHandling(int len, byte *contents)
{
    return _Enumerated(contents[0], 2, defaultCallHandlingLabel);
}

/* ############################## */
/* # _DeliveryOfErroneousSDU #              */
/* ############################## */
char* _DeliveryOfErroneousSDU(int len, byte *contents)
{
    return _Enumerated(contents[0], 3, deliveryOfErroneousSDULabel);
}

/* ############################## */
/* # _DisconnectingParty #        */
/* ############################## */
char* _DisconnectingParty(int len, byte *contents)
{
    return _Enumerated(contents[0], 3, disconnectingPartyLabel);
}

/* ############################## */
/* # _GlobalTitleAndSubSystemNumber #        */
/* ############################## */
char* _GlobalTitleAndSubSystemNumber(int len, byte *contents)
{
    int ssn, tt, np, oe, nai, dlen;

    ssn = contents[0];
    tt  = contents[1];
    np  = contents[2] >> 4;
    oe  = contents[2] & LO_BITS;
    nai = contents[3];

    strcpy(digits, _TBCDString(len - 4, contents + 4));
    dlen = strlen(digits);
    if (oe == ODD)
        digits[dlen - 1] = 0;

    sprintf(output, "SSN=%d TT=%d NP=%d OE=%d NAI=%d Addr=%s", ssn, tt, np, oe, nai, digits);

    return output;
}

/* ############################## */
/* # _INMarkingOfMS #             */
/* ############################## */
char* _INMarkingOfMS(int len, byte *contents)
{
    return _Enumerated(contents[0], 14, iNMarkingOfMSLabel);
}

/* ############################## */
/* # _InternalCauseAndLoc #       */
/* ############################## */
char* _InternalCauseAndLoc(int len, byte *contents)
{
    sprintf(output, "Location=%02x Cause=%02x", contents[0], contents[1]);
    return output;
}

/* ############################## */
/* # _LocationInformation #       */
/* ############################## */
char* _LocationInformation(int len, byte *contents)
{
    int mcc, mnc, lac, sac;

    mcc = (contents[0] & LO_BITS) * 100 + (contents[0] >> 4) * 10 + (contents[1] & LO_BITS);
    mnc = (contents[2] & LO_BITS) * 10 +  (contents[2] >> 4);
    if (contents[1] & LO_BITS != 0x0f)
        mnc = mnc * 10 + (contents[1] & LO_BITS);

    lac = contents[3] * 256 + contents[4];
    sac = contents[5] * 256 + contents[6];

    sprintf(output, "%03d-%02d-%d-%d", mcc, mnc, lac, sac);
    return output;
}

/* ############################## */
/* # _LocationInformationExtension #       */
/* ############################## */
char* _LocationInformationExtension(int len, byte *contents)
{
    int eci;

    eci = (contents[0] & LO_BITS) * 256 + contents[1];
    sprintf(output, "%d", eci);
    return output;
}

/* ############################## */
/* # _NetworkCallReference #      */
/* ############################## */
char* _NetworkCallReference(int len, byte *contents)
{
    char seq[MAX_LINE_LEN], switchid[MAX_LINE_LEN];

    strcpy(seq, _Integer(3, contents));
    strcpy(switchid, _Integer(2, contents + 3));
    sprintf(output, "Seq=%d SwitchID=%d", seq, switchid);
    return output;
}

/* ############################## */
/* # _OriginatedCode #       */
/* ############################## */
char* _OriginatedCode(int len, byte *contents)
{
    // printf("_OriginatedCode()\n");
    return _Enumerated(contents[0], 10, originatedCodeLabel);
}

/* ############################## */
/* # _OutputForSubscriber #       */
/* ############################## */
char* _OutputForSubscriber(int len, byte *contents)
{
    return _Enumerated(contents[0], 3, outputForSubscriberLabel);
}

/* ############################## */
/* # _OutputType #       */
/* ############################## */
char* _OutputType(int len, byte *contents)
{
    return _Enumerated(contents[0], 8, outputTypeLabel);
}

/* ############################## */
/* # _PChargingVector #       */
/* ############################## */
char* _PChargingVector(int len, byte *contents)
{
    unsigned int ptr, fieldlen;

    /* copy entire contents... */
    memcpy(output, contents + 1, len - 1);
    /* ensure that the string is properly terminated */
    output[len] = 0;

    /* go through and insert commas */
    ptr = contents[0] + 1;
    while (ptr < len)
    {
        fieldlen = contents[ptr];
        output[ptr - 1] = ',';
        ptr += fieldlen + 1;
    }

    return output;
}

/* ############################## */
/* # _RTCDefaultServiceHandling # */
/* ############################## */
char* _RTCDefaultServiceHandling(int len, byte *contents)
{
    return _Enumerated(contents[0], 2, rTCDefaultServiceHandlingLabel);
}

/* ############################## */
/* # _RTCNotInvokedReason # */
/* ############################## */
char* _RTCNotInvokedReason(int len, byte *contents)
{
    return _Enumerated(contents[0], 6, rTCNotInvokedReasonLabel);
}

/* ############################## */
/* # _SpeechCoderVersion # */
/* ############################## */
char* _SpeechCoderVersion(int len, byte *contents)
{
    return _Enumerated(contents[0], 7, speechCoderVersionLabel);
}

/* ############################## */
/* # _TAC #                       */
/* ############################## */
char* _TAC(int len, byte *contents)
{
    sprintf(output, "TSC=%d TOS=%d TOI=%d", contents[0], contents[1], contents[2]);
    return output;
}

/* ############################## */
/* # _TariffSwitchInd #                       */
/* ############################## */
char* _TariffSwitchInd(int len, byte *contents)
{
    return _Enumerated(contents[0], 3, tariffSwitchIndLabel);
}

/* ############################## */
/* # _Time #                      */
/* ############################## */
char* _Time(int len, byte *contents)
{
    int hh, mm, ss, ms;

    hh = contents[0];
    mm = contents[1];
    ss = contents[2];

    if (len == 4)
    {
        ms = contents[3];
        sprintf(output, "%02d:%02d:%02d.%d", hh, mm, ss, ms);
    }
    else
        sprintf(output, "%02d:%02d:%02d", hh, mm, ss);

    return output;
}

/* ############################## */
/* # _Timezone #                      */
/* ############################## */
char* _Timezone(int len, byte *contents)
{
    char sign;
    int units, tens, quarters, hours, minutes;

    units = contents[0] >> 4;
    sign  = (contents[0] & 0x08 ? '-' : '+');
    tens  = (contents[0] & 0x07);
    quarters = tens * 10 + units;
    hours = quarters / 4;
    minutes = (quarters % 4) * 15;

    sprintf(output, "UTC%c%02d:%02d", sign, hours, minutes);
    return output;
}
int hh, mm, ss, ms;
/* ############################## */
/* # _UILayer1Protocol #                       */
/* ############################## */
char* _UILayer1Protocol(int len, byte *contents)
{
    return _Enumerated(contents[0], 11, uILayer1ProtocolLabel);
}

/* ############################## */
/* # _UserRate #                       */
/* ############################## */
char* _UserRate(int len, byte *contents)
{
    return _Enumerated(contents[0], 32, userRateLabel);
}




/* ######################################################################## */
/* # Initialisation functions                                               */
/* ######################################################################## */

void initialiseCDRObjects(void)
{
    int n;
    /* zero the output string */
    memset(output, 0, MAX_LINE_LEN);
    /* and initialise the gsm charset */
    gsmchar_initialise();


    /* ######################################################################## */
    /* # Primitives                                                             */
    /* ######################################################################## */

    for (n = 0; n < MAX_PRIMITIVES; n++)
    {
        primitive[n].name       = primitiveName[n];
        primitive[n].type       = PRIMITIVE;
        primitive[n].ref.decode = &_OctetString;
    }

    /* point to decoder functions */
    primitive[ACCEPTABLECHANNELCODINGS].ref.decode                 = &_ChannelCodings;
    primitive[ACCEPTANCEOFCALLWAITING].ref.decode                  = NULL;
    primitive[ACCOUNTCODE].ref.decode                              = &_TBCDString;
    primitive[ACMCHARGINGINDICATOR].ref.decode                     = NULL; /* only used in WCDMA Japan */
    primitive[AIURREQUESTED].ref.decode                            = &_AirInterfaceUserRate;
    primitive[ANMCHARGINGINDICATOR].ref.decode                     = NULL; /* only used in WCDMA Japan */
    primitive[ASYNCSYNCINDICATOR].ref.decode                       = &_AsyncSyncIndicator;
    primitive[BEARERSERVICECODE].ref.decode                        = &_OctetString;
    primitive[BLADEID].ref.decode                                  = &_Integer;
    primitive[BSSMAPCAUSECODE].ref.decode                          = &_OctetString;
    primitive[BUDDYBLADEINDICATOR].ref.decode                      = NULL;
    primitive[C7CHARGINGMESSAGE].ref.decode                        = &_OctetString; /* to do */
    primitive[C7FIRSTCHTMESSAGE].ref.decode                        = &_OctetString; /* to do */
    primitive[C7SECONDCHTMESSAGE].ref.decode                       = &_OctetString; /* to do */
    primitive[CALLATTEMPTINDICATOR].ref.decode                     = NULL;
    primitive[CALLEDDIRECTORYNUMBER].ref.decode                    = &_TBCDString;
    primitive[CALLEDPARTYMNPINFO].ref.decode                       = &_AddressString;
    primitive[CALLEDPARTYNUMBER].ref.decode                        = &_AddressString;
    primitive[CALLEDSUBSCRIBERIMEI].ref.decode                     = &_TBCDString;
    primitive[CALLEDSUBSCRIBERIMEISV].ref.decode                   = &_TBCDString;
    primitive[CALLEDSUBSCRIBERIMSI].ref.decode                     = &_TBCDString;
    primitive[CALLIDENTIFICATIONNUMBER].ref.decode                 = &_Integer;
    primitive[CALLINGPARTYNUMBER].ref.decode                       = &_AddressString;
    primitive[CALLINGPARTYNUMBERSPECIALARRANGEMENTIND].ref.decode  = NULL;
    primitive[CALLINGSUBSCRIBERIMEI].ref.decode                    = &_TBCDString;
    primitive[CALLINGSUBSCRIBERIMEISV].ref.decode                  = &_TBCDString;
    primitive[CALLINGSUBSCRIBERIMSI].ref.decode                    = &_TBCDString;
    primitive[CALLPOSITION].ref.decode                             = &_CallPosition;
    primitive[CAMELINITIATEDCALLFORWARDING].ref.decode             = NULL;
    primitive[CARRIERIDENTIFICATIONCODE].ref.decode                = &_TBCDString;
    primitive[CARRIERINFORMATION].ref.decode                       = &_TBCDString; /* to do */
    primitive[CARRIERINFORMATIONBACKWARD].ref.decode               = NULL; /* only used in WCDMA Japan */
    primitive[CARRIERINFORMATIONFORWARD].ref.decode                = NULL; /* only used in WCDMA Japan */
    primitive[CARRIERSELECTIONSUBSTITUTIONINFORMATION].ref.decode  = &_Integer;
    primitive[CCBSCALLINDICATOR].ref.decode                        = NULL;
    primitive[CHANNELALLOCATIONPRIORITYLEVEL].ref.decode           = &_OctetString;
    primitive[CHANNELCODINGUSED].ref.decode                        = &_ChannelCodings;
    primitive[CHARGEABLEDURATION].ref.decode                       = &_Time;
    primitive[CHARGEDPARTY].ref.decode                             = &_ChargedParty;
    primitive[CHARGEINFORMATION].ref.decode                        = NULL; /* only used in WCDMA Japan */
    primitive[CHARGENUMBER].ref.decode                             = &_AddressString;
    primitive[CHARGINGCASE].ref.decode                             = &_Integer;
    primitive[CONTRACTORNUMBER].ref.decode                         = &_TBCDString;
    primitive[CUGINCOMINGACCESSUSED].ref.decode                    = NULL;
    primitive[CUGINDEX].ref.decode                                 = &_Integer;
    primitive[CUGINTERLOCKCODE].ref.decode                         = &_OctetString;
    primitive[CUGOUTGOINGACCESSINDICATOR].ref.decode               = NULL;
    primitive[CUGOUTGOINGACCESSUSED].ref.decode                    = NULL;
    primitive[DATEFORSTARTOFCHARGE].ref.decode                     = &_Date;
    primitive[DEFAULTCALLHANDLING].ref.decode                      = &_DefaultCallHandling;
    primitive[DELIVERYOFERRONEOUSSDU1].ref.decode                  = &_DeliveryOfErroneousSDU;
    primitive[DELIVERYOFERRONEOUSSDU2].ref.decode                  = &_DeliveryOfErroneousSDU;
    primitive[DELIVERYOFERRONEOUSSDU3].ref.decode                  = &_DeliveryOfErroneousSDU;
    primitive[DESTINATIONADDRESS].ref.decode                       = &_AddressString;
    primitive[DISCONNECTINGPARTY].ref.decode                       = &_DisconnectingParty;
    primitive[DISCONNECTIONDATE].ref.decode                        = &_Date;
    primitive[DISCONNECTIONDUETOSYSTEMRECOVERY].ref.decode         = NULL;
    primitive[DISCONNECTIONTIME].ref.decode                        = &_Time;
    primitive[DTMFUSED].ref.decode                                 = NULL;
    primitive[EMERGENCYSERVICECATEGORY].ref.decode                 = &_OctetString;
    primitive[EMLPPPRIORITYLEVEL].ref.decode                       = &_OctetString;
    primitive[ENTRYPOICA].ref.decode                               = NULL; /* only used in WCDMA Japan */
    primitive[EOSINFO].ref.decode                                  = &_Integer;
    primitive[EXCHANGEIDENTITY].ref.decode                         = &_String;
    primitive[EXITPOICA].ref.decode                                = NULL; /* only used in WCDMA Japan */
    primitive[FAULTCODE].ref.decode                                = &_Integer;
    primitive[FIRSTASSIGNEDSPEECHCODERVERSION].ref.decode          = &_SpeechCoderVersion;
    primitive[FIRSTCALLEDLOCATIONINFORMATION].ref.decode           = &_LocationInformation;
    primitive[FIRSTCALLEDLOCATIONINFORMATIONEXTENSION].ref.decode  = &_LocationInformationExtension;
    primitive[FIRSTCALLINGLOCATIONINFORMATION].ref.decode          = &_LocationInformation;
    primitive[FIRSTCALLINGLOCATIONINFORMATIONEXTENSION].ref.decode = &_LocationInformationExtension;
    primitive[FIRSTTARGETLOCATIONINFORMATION].ref.decode           = &_LocationInformation;
    primitive[FORLOPPDURINGOUTPUTINDICATOR].ref.decode             = NULL;
    primitive[FORLOPPRELEASEDURINGCALL].ref.decode                 = NULL;
    primitive[FREEFORMATDATAAPPENDINDICATOR].ref.decode            = NULL;
    primitive[FREEFORMATDATAAPPENDINDICATOR2].ref.decode           = NULL;
    primitive[GLOBALCALLREFERENCE].ref.decode                      = &_OctetString; /* to do */
    primitive[GLOBALTITLEANDSUBSYSTEMNUMBER].ref.decode            = &_GlobalTitleAndSubSystemNumber;
    primitive[GSMCALLREFERENCENUMBER].ref.decode                   = &_OctetString;
    primitive[GSMSCFADDRESS].ref.decode                            = &_AddressString;
    primitive[GSMSCFCONTROLOFAOC].ref.decode                       = NULL;
    primitive[GSMSCFINITIATEDCALLINDICATOR].ref.decode             = NULL;
    primitive[ICIORDERED].ref.decode                               = NULL;
    primitive[INCOMINGASSIGNEDROUTE].ref.decode                    = &_String;
    primitive[INCOMINGPCHARGINGVECTOR].ref.decode                  = &_PChargingVector;
    primitive[INCOMINGROUTE].ref.decode                            = &_String;
    primitive[INCOMPLETECALLDATAINDICATOR].ref.decode              = NULL;
    primitive[INCOMPLETECOMPOSITECDRINDICATOR].ref.decode          = NULL;
    primitive[INMARKINGOFMS].ref.decode                            = &_INMarkingOfMS;
    primitive[INSERVICETRIGGER].ref.decode                         = &_Integer;
    primitive[INTEREXCHANGECARRIERINDICATOR].ref.decode            = NULL;
    primitive[INTERNALCAUSEANDLOC].ref.decode                      = &_InternalCauseAndLoc;
    primitive[INTERNATIONALCALLINDICATOR].ref.decode               = NULL;
    primitive[INTERREGIONHANDOVERINDICATOR].ref.decode             = NULL;
    primitive[INTERRUPTIONTIME].ref.decode                         = &_Time;
    primitive[INVOCATIONOFCALLHOLD].ref.decode                     = NULL;
    primitive[LASTCALLEDLOCATIONINFORMATION].ref.decode            = &_LocationInformation;
    primitive[LASTCALLEDLOCATIONINFORMATIONEXTENSION].ref.decode   = &_LocationInformationExtension;
    primitive[LASTCALLINGLOCATIONINFORMATION].ref.decode           = &_LocationInformation;
    primitive[LASTPARTIALOUTPUT].ref.decode                        = NULL;
    primitive[MCASMSINDICATOR].ref.decode                          = NULL;
    primitive[MESSAGEREFERENCE].ref.decode                         = &_Integer; /* to do: enumerated */
    primitive[MESSAGETYPEINDICATOR].ref.decode                     = &_Integer;
    primitive[MISCELLANEOUSINFORMATION].ref.decode                 = &_Integer;
    primitive[MMENAME].ref.decode                                  = &_String;
    primitive[MOBILESTATIONROAMINGNUMBER].ref.decode               = &_AddressString;
    primitive[MOBILESTATIONROAMINGNUMBERINFO].ref.decode           = &_AddressString;
    primitive[MOBILESUBSCRIBERNUMBERFORHLRINTERROGATION].ref.decode = &_TBCDString;
    primitive[MOBILEUSERCLASS1].ref.decode                         = NULL; /* only used in WCDMA Japan */
    primitive[MOBILEUSERCLASS2].ref.decode                         = NULL; /* only used in WCDMA Japan */
    primitive[MSCADDRESS].ref.decode                               = &_AddressString;
    primitive[MSCIDENTIFICATION].ref.decode                        = &_AddressString;
    primitive[MTRFINDICATOR].ref.decode                            = NULL;
    primitive[MULTIMEDIACALL].ref.decode                           = NULL;
    primitive[NETWORKCALLREFERENCE].ref.decode                     = &_NetworkCallReference;
    primitive[NUMBEROFMETERPULSES].ref.decode                      = &_Integer;
    primitive[NUMBEROFSHORTMESSAGES].ref.decode                    = &_Integer;
    primitive[OPTIMALROUTINGINVOCATIONFAILED].ref.decode           = NULL;
    primitive[ORIGINALCALLEDNUMBER].ref.decode                     = &_AddressString;
    primitive[ORIGINATEDCODE].ref.decode                           = &_OriginatedCode;
    primitive[ORIGINATINGACCESSISDN].ref.decode                    = NULL;
    primitive[ORIGINATINGADDRESS].ref.decode                       = &_AddressString;
    primitive[ORIGINATINGCARRIER].ref.decode                       = &_OctetString; /* to do */
    primitive[ORIGINATINGCHARGEAREA].ref.decode                    = NULL; /* only used in WCDMA Japan */
    primitive[ORIGINATINGLINEINFORMATION].ref.decode               = &_OctetString;
    primitive[ORIGINATINGLOCATIONNUMBER].ref.decode                = &_AddressString;
    primitive[ORIGINFORCHARGING].ref.decode                        = &_Integer;
    primitive[OUTGOINGASSIGNEDROUTE].ref.decode                    = &_String;
    primitive[OUTGOINGPCHARGINGVECTOR].ref.decode                  = &_PChargingVector;
    primitive[OUTGOINGROUTE].ref.decode                            = &_String;
    primitive[OUTPUTFORSUBSCRIBER].ref.decode                      = &_OutputForSubscriber;
    primitive[OUTPUTTYPE].ref.decode                               = &_OutputType;
    primitive[PARTIALOUTPUTRECNUM].ref.decode                      = &_Integer;
    primitive[RECORDSEQUENCENUMBER].ref.decode                     = &_Integer;
    primitive[REDIRECTINGDROPBACK].ref.decode                      = NULL;
    primitive[REDIRECTINGDROPBACKNUMBER].ref.decode                = &_TBCDString;
    primitive[REDIRECTINGNUMBER].ref.decode                        = &_AddressString;
    primitive[REDIRECTIONCOUNTER].ref.decode                       = &_Integer;
    primitive[RELATEDCALLNUMBER].ref.decode                        = &_Integer;
    primitive[REROUTINGINDICATOR].ref.decode                       = NULL;
    primitive[RESTARTDURINGCALL].ref.decode                        = NULL;
    primitive[RESTARTDURINGOUTPUTINDICATOR].ref.decode             = NULL;
    primitive[RETRIEVALOFHELDCALL].ref.decode                      = NULL;
    primitive[RTCDEFAULTSERVICEHANDLING].ref.decode                = &_RTCDefaultServiceHandling;
    primitive[RTCFAILUREINDICATOR].ref.decode                      = &_Integer;
    primitive[RTCINDICATOR].ref.decode                             = NULL;
    primitive[RTCNOTINVOKEDREASON].ref.decode                      = &_RTCNotInvokedReason;
    primitive[RTCSESSIONID].ref.decode                             = &_OctetString;
    primitive[SERVICECENTREADDRESS].ref.decode                     = &_AddressString;
    primitive[SERVICEKEY].ref.decode                               = &_Integer;
    primitive[SRVCCADDITIONALSESSIONINDICATOR].ref.decode          = NULL;
    primitive[SRVCCCALLHOLDINDICATOR].ref.decode                   = NULL;
    primitive[SRVCCCONFERENCEINDICATOR].ref.decode                 = NULL;
    primitive[SRVCCORIGINATINGPREALERTINGINDICATOR].ref.decode     = NULL;
    primitive[SSFCHARGINGCASE].ref.decode                          = &_Integer;
    primitive[SSFLEGID].ref.decode                                 = &_Integer;
    primitive[SSINVOCATIONNOTIFICATION].ref.decode                 = NULL;
    primitive[SUBSCRIPTIONTYPE].ref.decode                         = &_Integer;
    primitive[SWITCHIDENTITY].ref.decode                           = &_Integer;
    primitive[TAC].ref.decode                                      = &_TAC;
    primitive[TARIFFCLASS].ref.decode                              = &_Integer;
    primitive[TARIFFSWITCHIND].ref.decode                          = &_TariffSwitchInd;
    primitive[TARGETLOCATIONINFORMATION].ref.decode                = &_LocationInformation;
    primitive[TDSCOUNTER].ref.decode                               = &_Integer;
    primitive[TERMINATINGACCESSISDN].ref.decode                    = NULL;
    primitive[TERMINATINGCARRIER].ref.decode                       = &_OctetString; /* to do */
    primitive[TERMINATINGCHARGEAREA].ref.decode                    = NULL; /* only used in WCDMA Japan */
    primitive[TERMINATINGLOCATIONNUMBER].ref.decode                = &_AddressString;
    primitive[TERMINATINGMOBILEUSERCLASS1].ref.decode              = NULL; /* only used in WCDMA Japan */
    primitive[TERMINATINGMOBILEUSERCLASS2].ref.decode              = NULL; /* only used in WCDMA Japan */
    primitive[TERMINATINGUSERCLASS].ref.decode                     = NULL; /* only used in WCDMA Japan */
    primitive[TIMEFOREVENT].ref.decode                             = &_Time;
    primitive[TIMEFORSTARTOFCHARGE].ref.decode                     = &_Time;
    primitive[TIMEFORSTOPOFCHARGE].ref.decode                      = &_Time;
    primitive[TIMEFORTCSEIZURECALLED].ref.decode                   = &_Time;
    primitive[TIMEFORTCSEIZURECALLING].ref.decode                  = &_Time;
    primitive[TIMEFROMREGISTERSEIZURETOSTARTOFCHARGING].ref.decode = &_Time;
    primitive[TRAFFICCLASS].ref.decode                             = &_Integer; /* to do: enumerated */
    primitive[TRAFFICISOLATIONINDICATOR].ref.decode                = NULL;
    primitive[TRANSFERDELAY].ref.decode                            = &_Integer;
    primitive[TRANSLATEDNUMBER].ref.decode                         = &_AddressString;
    primitive[TRIGGERDETECTIONPOINT].ref.decode                    = &_Integer; /* to do: enumerated */
    primitive[TYPEOFCALLINGSUBSCRIBER].ref.decode                  = &_Integer;
    primitive[UILAYER1PROTOCOL].ref.decode                         = &_UILayer1Protocol;
    primitive[UETIMEZONE].ref.decode                               = &_Timezone;
    primitive[USERCLASS].ref.decode                                = NULL; /* only used in WCDMA Japan */
    primitive[USERRATE].ref.decode                                 = &_UserRate;
    primitive[WPSCALLINDICATOR].ref.decode                         = NULL;


    /* these CDR components are constructors */
    camelTDPData[0] = primitive + SERVICEKEY;
    camelTDPData[1] = primitive + GSMSCFADDRESS;

    multimediaInformation[0] = primitive + USERRATE;
    multimediaInformation[1] = primitive + ASYNCSYNCINDICATOR;
    multimediaInformation[2] = primitive + UILAYER1PROTOCOL;

    triggerData[0] = primitive + TRIGGERDETECTIONPOINT;
    triggerData[1] = primitive + SERVICEKEY;
    triggerData[2] = primitive + CO_LOCATED;
    triggerData[3] = primitive + POINTCODEANDSUBSYSTEMNUMBER;
    triggerData[4] = primitive + GLOBALTITLE;
    triggerData[5] = primitive + GLOBALTITLEANDSUBSYSTEMNUMBER;

}


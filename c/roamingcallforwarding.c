#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roamingcallforwarding.h"
#include "components.h"

extern asn1Object primitive[];
extern asn1Object *multimediaInformation[];

asn1Object *roamingcallforwarding[ROAMINGCALLFORWARDING_MAX_FIELDS];


void initialiseRoamingCallForwarding(void)
{
    int n;

    roamingcallforwarding[  0] = primitive + TAC;
    roamingcallforwarding[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    roamingcallforwarding[  2] = primitive + RECORDSEQUENCENUMBER;
    roamingcallforwarding[  3] = primitive + TYPEOFCALLINGSUBSCRIBER;
    roamingcallforwarding[  4] = primitive + CALLINGPARTYNUMBER;
    roamingcallforwarding[  5] = primitive + CALLEDPARTYNUMBER;
    roamingcallforwarding[  6] = primitive + CALLEDSUBSCRIBERIMSI;
    roamingcallforwarding[  7] = primitive + MOBILESTATIONROAMINGNUMBER;
    roamingcallforwarding[  8] = primitive + DISCONNECTINGPARTY;
    roamingcallforwarding[  9] = primitive + DATEFORSTARTOFCHARGE;
    roamingcallforwarding[ 10] = primitive + TIMEFORSTARTOFCHARGE;
    roamingcallforwarding[ 11] = primitive + TIMEFORSTOPOFCHARGE;
    roamingcallforwarding[ 12] = primitive + CHARGEABLEDURATION;
    roamingcallforwarding[ 13] = primitive + INTERRUPTIONTIME;
    roamingcallforwarding[ 14] = primitive + TIMEFROMREGISTERSEIZURETOSTARTOFCHARGING;
    roamingcallforwarding[ 15] = primitive + CHARGEDPARTY;
    roamingcallforwarding[ 16] = primitive + ORIGINFORCHARGING;
    roamingcallforwarding[ 17] = primitive + TARIFFCLASS;
    roamingcallforwarding[ 18] = primitive + TARIFFSWITCHIND;
    roamingcallforwarding[ 19] = primitive + EXCHANGEIDENTITY;
    roamingcallforwarding[ 20] = primitive + MSCIDENTIFICATION;
    roamingcallforwarding[ 21] = primitive + OUTGOINGROUTE;
    roamingcallforwarding[ 22] = primitive + INCOMINGROUTE;
    roamingcallforwarding[ 23] = primitive + MISCELLANEOUSINFORMATION;
    roamingcallforwarding[ 24] = primitive + SUBSCRIPTIONTYPE;
    roamingcallforwarding[ 25] = primitive + CALLPOSITION;
    roamingcallforwarding[ 26] = primitive + EOSINFO;
    roamingcallforwarding[ 27] = primitive + INTERNALCAUSEANDLOC;
    roamingcallforwarding[ 28] = primitive + ORIGINALCALLEDNUMBER;
    roamingcallforwarding[ 29] = primitive + REDIRECTINGNUMBER;
    roamingcallforwarding[ 30] = primitive + REDIRECTIONCOUNTER;
    roamingcallforwarding[ 31] = primitive + RESTARTDURINGCALL;
    roamingcallforwarding[ 32] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    roamingcallforwarding[ 33] = primitive + NUMBEROFMETERPULSES;
    roamingcallforwarding[ 34] = primitive + C7CHARGINGMESSAGE;
    roamingcallforwarding[ 35] = primitive + C7FIRSTCHTMESSAGE;
    roamingcallforwarding[ 36] = primitive + C7SECONDCHTMESSAGE;
    roamingcallforwarding[ 37] = primitive + ICIORDERED;
    roamingcallforwarding[ 38] = primitive + OUTPUTFORSUBSCRIBER;
    roamingcallforwarding[ 39] = primitive + LASTPARTIALOUTPUT;
    roamingcallforwarding[ 40] = primitive + PARTIALOUTPUTRECNUM;
    roamingcallforwarding[ 41] = primitive + RELATEDCALLNUMBER;
    roamingcallforwarding[ 42] = primitive + CUGINTERLOCKCODE;
    roamingcallforwarding[ 43] = primitive + CUGOUTGOINGACCESSINDICATOR;
    roamingcallforwarding[ 44] = primitive + PRESENTATIONANDSCREENINGINDICATOR;
    roamingcallforwarding[ 45] = primitive + FAULTCODE;
    roamingcallforwarding[ 46] = primitive + INCOMPLETECALLDATAINDICATOR;

    /* component[47] is a constructor */
    roamingcallforwarding[47] = (asn1Object*) malloc(sizeof(asn1Object));
    roamingcallforwarding[47]->name = (char*) malloc(MAX_FIELD_LEN);
    sprintf(roamingcallforwarding[47]->name, "multimediaInformation");
    roamingcallforwarding[47]->type = CONSTRUCTOR;
    roamingcallforwarding[47]->ref.next = multimediaInformation;

    roamingcallforwarding[ 48] = primitive + SWITCHIDENTITY;
    roamingcallforwarding[ 49] = primitive + NETWORKCALLREFERENCE;
    roamingcallforwarding[ 50] = primitive + DISCONNECTIONDUETOSYSTEMRECOVERY;
    roamingcallforwarding[ 51] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    roamingcallforwarding[ 52] = primitive + FORLOPPRELEASEDURINGCALL;
    roamingcallforwarding[ 53] = primitive + GSMCALLREFERENCENUMBER;
    roamingcallforwarding[ 54] = primitive + MSCADDRESS;
    roamingcallforwarding[ 55] = primitive + CARRIERINFORMATIONBACKWARD;
    roamingcallforwarding[ 56] = primitive + ORIGINATINGACCESSISDN;
    roamingcallforwarding[ 57] = primitive + ORIGINATINGCARRIER;
    roamingcallforwarding[ 58] = primitive + ORIGINATINGCHARGEAREA;
    roamingcallforwarding[ 59] = primitive + TERMINATINGACCESSISDN;
    roamingcallforwarding[ 60] = primitive + TERMINATINGCARRIER;
    roamingcallforwarding[ 61] = primitive + TERMINATINGCHARGEAREA;
    roamingcallforwarding[ 62] = primitive + CONTRACTORNUMBER;
    roamingcallforwarding[ 63] = primitive + CARRIERIDENTIFICATIONCODE;
    roamingcallforwarding[ 64] = primitive + CARRIERINFORMATION;
    roamingcallforwarding[ 65] = primitive + CARRIERSELECTIONSUBSTITUTIONINFORMATION;
    roamingcallforwarding[ 66] = primitive + CHARGENUMBER;
    roamingcallforwarding[ 67] = primitive + INTEREXCHANGECARRIERINDICATOR;
    roamingcallforwarding[ 68] = primitive + ORIGINATINGLINEINFORMATION;
    roamingcallforwarding[ 69] = primitive + USERTOUSERINFORMATION;
    roamingcallforwarding[ 70] = primitive + GLOBALCALLREFERENCE;
    roamingcallforwarding[ 71] = primitive + RTCINDICATOR;
    roamingcallforwarding[ 72] = primitive + RTCSESSIONID;
    roamingcallforwarding[ 73] = primitive + RTCDEFAULTSERVICEHANDLING;
    roamingcallforwarding[ 74] = primitive + RTCFAILUREINDICATOR;
    roamingcallforwarding[ 75] = primitive + RTCNOTINVOKEDREASON;
    roamingcallforwarding[ 76] = primitive + MOBILESUBSCRIBERNUMBERFORHLRINTERROGATION;
    roamingcallforwarding[ 77] = primitive + OUTGOINGPCHARGINGVECTOR;
    roamingcallforwarding[ 78] = primitive + BLADEID;
    roamingcallforwarding[ 79] = primitive + TRAFFICISOLATIONINDICATOR;
    roamingcallforwarding[ 80] = primitive + MTRFINDICATOR;
    roamingcallforwarding[ 81] = primitive + BUDDYBLADEINDICATOR;

    /* pad out the array where tags are not defined */
    for (n = 82; n < 102; n++)
        roamingcallforwarding[n] = NULL;

    roamingcallforwarding[102] = primitive + OUTPUTTYPE;

    /* pad out the array where tags are not defined */
    for (n = 103; n < 121; n++)
        roamingcallforwarding[n] = NULL;

    roamingcallforwarding[121] = primitive + REROUTINGINDICATOR;
}


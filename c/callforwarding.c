#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callforwarding.h"
#include "components.h"

extern asn1Object primitive[];
extern asn1Object *camelTDPData[];
extern asn1Object *multimediaInformation[];

asn1Object *callforwarding[CALLFORWARDING_MAX_FIELDS];


void initialiseCallForwarding(void)
{
    int n;

    callforwarding[  0] = primitive + TAC;
    callforwarding[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    callforwarding[  2] = primitive + RECORDSEQUENCENUMBER;
    callforwarding[  3] = primitive + TYPEOFCALLINGSUBSCRIBER;
    callforwarding[  4] = primitive + CALLINGPARTYNUMBER;
    callforwarding[  5] = primitive + CALLEDPARTYNUMBER;
    callforwarding[  6] = primitive + ORIGINALCALLEDNUMBER;
    callforwarding[  7] = primitive + REDIRECTINGNUMBER;
    callforwarding[  8] = primitive + REDIRECTIONCOUNTER;
    callforwarding[  9] = primitive + REDIRECTINGSPN;
    callforwarding[ 10] = primitive + REDIRECTINGIMSI;
    callforwarding[ 11] = primitive + MOBILESTATIONROAMINGNUMBER;
    callforwarding[ 12] = primitive + DISCONNECTINGPARTY;
    callforwarding[ 13] = primitive + DATEFORSTARTOFCHARGE;
    callforwarding[ 14] = primitive + TIMEFORSTARTOFCHARGE;
    callforwarding[ 15] = primitive + TIMEFORSTOPOFCHARGE;
    callforwarding[ 16] = primitive + CHARGEABLEDURATION;
    callforwarding[ 17] = primitive + INTERRUPTIONTIME;
    callforwarding[ 18] = primitive + TIMEFROMREGISTERSEIZURETOSTARTOFCHARGING;
    callforwarding[ 19] = primitive + CHARGEDPARTY;
    callforwarding[ 20] = primitive + ORIGINFORCHARGING;
    callforwarding[ 21] = primitive + TARIFFCLASS;
    callforwarding[ 22] = primitive + TARIFFSWITCHIND;
    callforwarding[ 23] = primitive + EXCHANGEIDENTITY;
    callforwarding[ 24] = primitive + MSCIDENTIFICATION;
    callforwarding[ 25] = primitive + OUTGOINGROUTE;
    callforwarding[ 26] = primitive + INCOMINGROUTE;
    callforwarding[ 27] = primitive + MISCELLANEOUSINFORMATION;
    callforwarding[ 28] = primitive + ORIGINATINGLOCATIONNUMBER;
    callforwarding[ 29] = primitive + CALLPOSITION;
    callforwarding[ 30] = primitive + EOSINFO;
    callforwarding[ 31] = primitive + INTERNALCAUSEANDLOC;
    callforwarding[ 32] = primitive + RESTARTDURINGCALL;
    callforwarding[ 33] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    callforwarding[ 34] = primitive + NUMBEROFMETERPULSES;
    callforwarding[ 35] = primitive + C7CHARGINGMESSAGE;
    callforwarding[ 36] = primitive + C7FIRSTCHTMESSAGE;
    callforwarding[ 37] = primitive + C7SECONDCHTMESSAGE;
    callforwarding[ 38] = primitive + ICIORDERED;
    callforwarding[ 39] = primitive + OUTPUTFORSUBSCRIBER;
    callforwarding[ 40] = primitive + INMARKINGOFMS;
    callforwarding[ 41] = primitive + LASTPARTIALOUTPUT;
    callforwarding[ 42] = primitive + PARTIALOUTPUTRECNUM;
    callforwarding[ 43] = primitive + RELATEDCALLNUMBER;
    callforwarding[ 44] = primitive + CUGINTERLOCKCODE;
    callforwarding[ 45] = primitive + CUGINDEX;
    callforwarding[ 46] = primitive + CUGOUTGOINGACCESSUSED;
    callforwarding[ 47] = primitive + CUGOUTGOINGACCESSINDICATOR;
    callforwarding[ 48] = primitive + REGIONALSERVICEUSED;
    callforwarding[ 49] = primitive + REGIONDEPENDENTCHARGINGORIGIN;
    callforwarding[ 50] = primitive + PRESENTATIONANDSCREENINGINDICATOR;
    callforwarding[ 51] = primitive + FAULTCODE;
    callforwarding[ 52] = primitive + SUBSCRIPTIONTYPE;
    callforwarding[ 53] = primitive + INCOMPLETECALLDATAINDICATOR;
    callforwarding[ 54] = primitive + INCOMPLETECOMPOSITECDRINDICATOR;
    callforwarding[ 55] = primitive + ORIGINATEDCODE;
    callforwarding[ 56] = primitive + SWITCHIDENTITY;
    callforwarding[ 57] = primitive + NETWORKCALLREFERENCE;
    callforwarding[ 58] = primitive + DISCONNECTIONDUETOSYSTEMRECOVERY;
    callforwarding[ 59] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    callforwarding[ 60] = primitive + FORLOPPRELEASEDURINGCALL;
    callforwarding[ 61] = primitive + TRANSLATEDNUMBER;
    callforwarding[ 62] = primitive + CAMELINITIATEDCALLFORWARDING;

    /* components[63 to 72] are constructors */
    /* name = 'bCSMTDPData1..10' */
    for (n = 63; n < 73; n++)
    {
        callforwarding[n] = (asn1Object*) malloc(sizeof(asn1Object));
        callforwarding[n]->name = (char*) malloc(MAX_FIELD_LEN);
        memset(callforwarding[n]->name, 0, MAX_FIELD_LEN);
        sprintf(callforwarding[n]->name, "bCSMTDPData%d", n - 62);
        callforwarding[n]->type = CONSTRUCTOR;
        callforwarding[n]->ref.next = camelTDPData;
    }

    callforwarding[ 73] = primitive + GSMCALLREFERENCENUMBER;
    callforwarding[ 74] = primitive + MSCADDRESS;
    callforwarding[ 75] = primitive + ACMCHARGINGINDICATOR;
    callforwarding[ 76] = primitive + ANMCHARGINGINDICATOR;
    callforwarding[ 77] = primitive + CARRIERINFORMATIONBACKWARD;
    callforwarding[ 78] = primitive + CHARGEINFORMATION;
    callforwarding[ 79] = primitive + DISCONNECTIONDATE;
    callforwarding[ 80] = primitive + DISCONNECTIONTIME;
    callforwarding[ 81] = primitive + EXITPOICA;
    callforwarding[ 82] = primitive + ORIGINATINGCARRIER;
    callforwarding[ 83] = primitive + ORIGINATINGCHARGEAREA;
    callforwarding[ 84] = primitive + TERMINATINGACCESSISDN;
    callforwarding[ 85] = primitive + TERMINATINGCARRIER;
    callforwarding[ 86] = primitive + TERMINATINGCHARGEAREA;
    callforwarding[ 87] = primitive + TERMINATINGMOBILEUSERCLASS1;
    callforwarding[ 88] = primitive + TERMINATINGMOBILEUSERCLASS2;
    callforwarding[ 89] = primitive + TERMINATINGUSERCLASS;
    callforwarding[ 90] = primitive + ORIGINATINGACCESSISDN;
    callforwarding[ 91] = primitive + CONTRACTORNUMBER;
    callforwarding[ 92] = primitive + CALLEDPARTYMNPINFO;
    callforwarding[ 93] = primitive + CARRIERIDENTIFICATIONCODE;
    callforwarding[ 94] = primitive + CARRIERINFORMATION;
    callforwarding[ 95] = primitive + CARRIERSELECTIONSUBSTITUTIONINFORMATION;
    callforwarding[ 96] = primitive + CHARGENUMBER;
    callforwarding[ 97] = primitive + INTEREXCHANGECARRIERINDICATOR;
    callforwarding[ 98] = primitive + ORIGINATINGLINEINFORMATION;
    callforwarding[ 99] = primitive + OPTIMALROUTINGTYPE;
    callforwarding[100] = primitive + OPTIMALROUTINGINVOCATIONFAILED;
    callforwarding[101] = primitive + USERTOUSERINFORMATION;
    callforwarding[102] = primitive + OUTPUTTYPE;

    /* component[103] is a constructor */
    callforwarding[103] = (asn1Object*) malloc(sizeof(asn1Object));
    callforwarding[103]->name = (char*) malloc(MAX_FIELD_LEN);
    sprintf(callforwarding[103]->name, "multimediaInformation");
    callforwarding[103]->type = CONSTRUCTOR;
    callforwarding[103]->ref.next = multimediaInformation;

    callforwarding[104] = primitive + GLOBALCALLREFERENCE;
    callforwarding[105] = primitive + RTCINDICATOR;
    callforwarding[106] = primitive + RTCSESSIONID;
    callforwarding[107] = primitive + RTCDEFAULTSERVICEHANDLING;
    callforwarding[108] = primitive + RTCFAILUREINDICATOR;
    callforwarding[109] = primitive + RTCNOTINVOKEDREASON;
    callforwarding[110] = primitive + CALLEDDIRECTORYNUMBER;
    callforwarding[111] = primitive + OUTGOINGPCHARGINGVECTOR;
    callforwarding[112] = primitive + BLADEID;
    callforwarding[113] = primitive + BUDDYBLADEINDICATOR;
    callforwarding[114] = primitive + TRAFFICISOLATIONINDICATOR;

    /* pad out the array where tags are not defined */
    for (n = 115; n < 121; n++)
        callforwarding[n] = NULL;

    callforwarding[121] = primitive + REROUTINGINDICATOR;
}


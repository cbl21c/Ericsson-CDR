#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transit.h"
#include "components.h"

extern asn1Object primitive[];
extern asn1Object *camelTDPData[];
extern asn1Object *multimediaInformation[];

asn1Object *transit[TRANSIT_MAX_FIELDS];


void initialiseTransit(void)
{
    int n;

    transit[  0] = primitive + TAC;
    transit[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    transit[  2] = primitive + RECORDSEQUENCENUMBER;
    transit[  3] = primitive + TYPEOFCALLINGSUBSCRIBER;
    transit[  4] = primitive + CALLINGPARTYNUMBER;
    transit[  5] = primitive + CALLEDPARTYNUMBER;
    transit[  6] = primitive + CALLEDSUBSCRIBERIMSI;
    transit[  7] = primitive + DISCONNECTINGPARTY;
    transit[  8] = primitive + DATEFORSTARTOFCHARGE;
    transit[  9] = primitive + TIMEFORSTARTOFCHARGE;
    transit[ 10] = primitive + TIMEFORSTOPOFCHARGE;
    transit[ 11] = primitive + CHARGEABLEDURATION;
    transit[ 12] = primitive + INTERRUPTIONTIME;
    transit[ 13] = primitive + TIMEFROMREGISTERSEIZURETOSTARTOFCHARGING;
    transit[ 14] = primitive + CHARGEDPARTY;
    transit[ 15] = primitive + ORIGINFORCHARGING;
    transit[ 16] = primitive + TARIFFCLASS;
    transit[ 17] = primitive + TARIFFSWITCHIND;
    transit[ 18] = primitive + NUMBEROFMETERPULSES;
    transit[ 19] = primitive + EXCHANGEIDENTITY;
    transit[ 20] = primitive + MSCIDENTIFICATION;
    transit[ 21] = primitive + OUTGOINGROUTE;
    transit[ 22] = primitive + INCOMINGROUTE;
    transit[ 23] = primitive + MISCELLANEOUSINFORMATION;
    transit[ 24] = primitive + ORIGINATEDCODE;
    transit[ 25] = primitive + INMARKINGOFMS;
    transit[ 26] = primitive + CALLPOSITION;
    transit[ 27] = primitive + EOSINFO;
    transit[ 28] = primitive + INTERNALCAUSEANDLOC;
    transit[ 29] = primitive + ORIGINALCALLEDNUMBER;
    transit[ 30] = primitive + REDIRECTINGNUMBER;
    transit[ 31] = primitive + REDIRECTIONCOUNTER;
    transit[ 32] = primitive + REDIRECTINGDROPBACKNUMBER;
    transit[ 33] = primitive + REDIRECTINGDROPBACK;
    transit[ 34] = primitive + RESTARTDURINGCALL;
    transit[ 35] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    transit[ 36] = primitive + ICIORDERED;
    transit[ 37] = primitive + OUTPUTFORSUBSCRIBER;
    transit[ 38] = primitive + LASTPARTIALOUTPUT;
    transit[ 39] = primitive + PARTIALOUTPUTRECNUM;
    transit[ 40] = primitive + RELATEDCALLNUMBER;
    transit[ 41] = primitive + FAULTCODE;
    transit[ 42] = primitive + SUBSCRIPTIONTYPE;
    transit[ 43] = primitive + INCOMPLETECALLDATAINDICATOR;
    transit[ 44] = primitive + INCOMPLETECOMPOSITECDRINDICATOR;
    transit[ 45] = primitive + SWITCHIDENTITY;
    transit[ 46] = primitive + NETWORKCALLREFERENCE;
    transit[ 47] = primitive + DISCONNECTIONDUETOSYSTEMRECOVERY;
    transit[ 48] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    transit[ 49] = primitive + FORLOPPRELEASEDURINGCALL;
    transit[ 50] = primitive + TRANSLATEDNUMBER;

    /* components[51 to 60] are constructors */
    /* name = 'bCSMTDPData1..10' */
    for (n = 51; n < 61; n++)
    {
        transit[n] = (asn1Object*) malloc(sizeof(asn1Object));
        transit[n]->name = (char*) malloc(MAX_FIELD_LEN);
        memset(transit[n]->name, 0, MAX_FIELD_LEN);
        sprintf(transit[n]->name, "bCSMTDPData%d", n - 50);
        transit[n]->type = CONSTRUCTOR;
        transit[n]->ref.next = camelTDPData;
    }

    transit[ 61] = primitive + GSMCALLREFERENCENUMBER;
    transit[ 62] = primitive + C7CHARGINGMESSAGE;
    transit[ 63] = primitive + C7FIRSTCHTMESSAGE;
    transit[ 64] = primitive + C7SECONDCHTMESSAGE;
    transit[ 65] = primitive + ACMCHARGINGINDICATOR;
    transit[ 66] = primitive + ANMCHARGINGINDICATOR;
    transit[ 67] = primitive + MSCADDRESS;
    transit[ 68] = primitive + CARRIERINFORMATIONBACKWARD;
    transit[ 69] = primitive + CARRIERINFORMATIONFORWARD;
    transit[ 70] = primitive + CHARGEINFORMATION;
    transit[ 71] = primitive + DISCONNECTIONDATE;
    transit[ 72] = primitive + DISCONNECTIONTIME;
    transit[ 73] = primitive + ENTRYPOICA;
    transit[ 74] = primitive + EXITPOICA;
    transit[ 75] = primitive + INTERNATIONALCALLINDICATOR;
    transit[ 76] = primitive + MOBILEUSERCLASS1;
    transit[ 77] = primitive + MOBILEUSERCLASS2;
    transit[ 78] = primitive + ORIGINATINGACCESSISDN;
    transit[ 79] = primitive + ORIGINATINGCARRIER;
    transit[ 80] = primitive + ORIGINATINGCHARGEAREA;
    transit[ 81] = primitive + TDSCOUNTER;
    transit[ 82] = primitive + TERMINATINGACCESSISDN;
    transit[ 83] = primitive + TERMINATINGCARRIER;
    transit[ 84] = primitive + TERMINATINGCHARGEAREA;
    transit[ 85] = primitive + TERMINATINGMOBILEUSERCLASS1;
    transit[ 86] = primitive + TERMINATINGMOBILEUSERCLASS2;
    transit[ 87] = primitive + CONTRACTORNUMBER;
    transit[ 88] = primitive + TERMINATINGUSERCLASS;
    transit[ 89] = primitive + USERCLASS;
    transit[ 90] = primitive + CALLEDPARTYMNPINFO;
    transit[ 91] = primitive + CHARGENUMBER;
    transit[ 92] = primitive + ORIGINATINGLINEINFORMATION;

    /* component[93] is a constructor */
    transit[93] = (asn1Object*) malloc(sizeof(asn1Object));
    transit[93]->name = (char*) malloc(MAX_FIELD_LEN);
    sprintf(transit[93]->name, "multimediaInformation");
    transit[93]->type = CONSTRUCTOR;
    transit[93]->ref.next = multimediaInformation;

    transit[ 94] = primitive + GLOBALCALLREFERENCE;
    transit[ 95] = primitive + RTCINDICATOR;
    transit[ 96] = primitive + RTCSESSIONID;
    transit[ 97] = primitive + RTCDEFAULTSERVICEHANDLING;
    transit[ 98] = primitive + RTCFAILUREINDICATOR;
    transit[ 99] = primitive + RTCNOTINVOKEDREASON;
    transit[100] = primitive + CALLEDDIRECTORYNUMBER;
    transit[101] = primitive + INCOMINGPCHARGINGVECTOR;
    transit[102] = primitive + OUTPUTTYPE;
    transit[103] = primitive + OUTGOINGPCHARGINGVECTOR;
    transit[104] = primitive + BLADEID;
    transit[105] = primitive + BUDDYBLADEINDICATOR;
    transit[106] = primitive + TRAFFICISOLATIONINDICATOR;
    transit[107] = primitive + CARRIERIDENTIFICATIONCODE;
    transit[108] = primitive + CARRIERINFORMATION;
    transit[109] = primitive + CARRIERSELECTIONSUBSTITUTIONINFORMATION;
    transit[110] = primitive + INTEREXCHANGECARRIERINDICATOR;
    transit[111] = primitive + MOBILESTATIONROAMINGNUMBERINFO; /* market correction */

    /* pad out the array where tags are not defined */
    for (n = 112; n < 121; n++)
        transit[n] = NULL;

    transit[121] = primitive + REROUTINGINDICATOR;
}


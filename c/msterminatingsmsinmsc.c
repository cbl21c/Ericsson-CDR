#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msterminatingsmsinmsc.h"
#include "components.h"

extern asn1Object primitive[];
extern asn1Object *camelTDPData[];

asn1Object *msterminatingsmsinmsc[MSTERMINATINGSMSINMSC_MAX_FIELDS];


void initialiseMSTerminatingSMSinMSC(void)
{
    int n;

    msterminatingsmsinmsc[  0] = primitive + TAC;
    msterminatingsmsinmsc[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    msterminatingsmsinmsc[  2] = primitive + RECORDSEQUENCENUMBER;
    msterminatingsmsinmsc[  3] = primitive + CALLEDPARTYNUMBER;
    msterminatingsmsinmsc[  4] = primitive + CALLEDSUBSCRIBERIMSI;
    msterminatingsmsinmsc[  5] = primitive + CALLEDSUBSCRIBERIMEI;
    msterminatingsmsinmsc[  6] = primitive + DATEFORSTARTOFCHARGE;
    msterminatingsmsinmsc[  7] = primitive + TIMEFORSTARTOFCHARGE;
    msterminatingsmsinmsc[  8] = primitive + ORIGINFORCHARGING;
    msterminatingsmsinmsc[  9] = primitive + CHARGEDPARTY;
    msterminatingsmsinmsc[ 10] = primitive + EXCHANGEIDENTITY;
    msterminatingsmsinmsc[ 11] = primitive + MSCIDENTIFICATION;
    msterminatingsmsinmsc[ 12] = primitive + OUTGOINGROUTE;
    msterminatingsmsinmsc[ 13] = primitive + FIRSTCALLEDLOCATIONINFORMATION;
    msterminatingsmsinmsc[ 14] = primitive + TELESERVICECODE;
    msterminatingsmsinmsc[ 15] = primitive + SERVICECENTREADDRESS;
    /* no tags for 16 and 17 */
    msterminatingsmsinmsc[ 16] = NULL;
    msterminatingsmsinmsc[ 17] = NULL;
    msterminatingsmsinmsc[ 18] = primitive + ICIORDERED;
    msterminatingsmsinmsc[ 19] = primitive + OUTPUTFORSUBSCRIBER;
    msterminatingsmsinmsc[ 20] = primitive + MISCELLANEOUSINFORMATION;
    msterminatingsmsinmsc[ 21] = primitive + REGIONALSERVICEUSED;
    msterminatingsmsinmsc[ 22] = primitive + REGIONDEPENDENTCHARGINGORIGIN;
    msterminatingsmsinmsc[ 23] = primitive + CHANNELALLOCATIONPRIORITYLEVEL;
    msterminatingsmsinmsc[ 24] = primitive + INCOMPLETECALLDATAINDICATOR;
    msterminatingsmsinmsc[ 25] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    msterminatingsmsinmsc[ 26] = primitive + FREQUENCYBANDSUPPORTED;
    msterminatingsmsinmsc[ 27] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    msterminatingsmsinmsc[ 28] = primitive + NUMBEROFSHORTMESSAGES;
    msterminatingsmsinmsc[ 29] = primitive + LASTCALLEDLOCATIONINFORMATION;
    msterminatingsmsinmsc[ 30] = primitive + POSITIONACCURACY;
    msterminatingsmsinmsc[ 31] = primitive + USERTERMINALPOSITION;
    msterminatingsmsinmsc[ 32] = primitive + SWITCHIDENTITY;
    msterminatingsmsinmsc[ 33] = primitive + ORIGINATINGADDRESS;
    msterminatingsmsinmsc[ 34] = primitive + MESSAGETYPEINDICATOR;
    msterminatingsmsinmsc[ 35] = primitive + RNCIDOFFIRSTRNC;

    /* component[36] is a constructor */
    msterminatingsmsinmsc[36] = (asn1Object*) malloc(sizeof(asn1Object));
    msterminatingsmsinmsc[36]->name = (char*) malloc(MAX_FIELD_LEN);
    memset(msterminatingsmsinmsc[36]->name, 0, MAX_FIELD_LEN);
    sprintf(msterminatingsmsinmsc[36]->name, "bCSMTDPData1");
    msterminatingsmsinmsc[36]->type = CONSTRUCTOR;
    msterminatingsmsinmsc[36]->ref.next = camelTDPData;

    msterminatingsmsinmsc[ 37] = primitive + DEFAULTSMSHANDLING;
    msterminatingsmsinmsc[ 38] = primitive + FREEFORMATDATA;
    msterminatingsmsinmsc[ 39] = primitive + SMSRESULT;
    msterminatingsmsinmsc[ 40] = primitive + SMSREFERENCENUMBER;
    msterminatingsmsinmsc[ 41] = primitive + MSCADDRESS;
    msterminatingsmsinmsc[ 42] = primitive + CAMELORIGINATINGADDRESS;
    msterminatingsmsinmsc[ 43] = primitive + CALLEDSUBSCRIBERIMEISV;
    msterminatingsmsinmsc[ 44] = primitive + RTCINDICATOR;
    msterminatingsmsinmsc[ 45] = primitive + RTCSESSIONID;
    msterminatingsmsinmsc[ 46] = primitive + RTCDEFAULTSERVICEHANDLING;
    msterminatingsmsinmsc[ 47] = primitive + RTCFAILUREINDICATOR;
    msterminatingsmsinmsc[ 48] = primitive + RTCNOTINVOKEDREASON;
    msterminatingsmsinmsc[ 49] = primitive + BLADEID;
    msterminatingsmsinmsc[ 50] = primitive + BUDDYBLADEINDICATOR;
    msterminatingsmsinmsc[ 51] = primitive + TRAFFICISOLATIONINDICATOR;
    msterminatingsmsinmsc[ 52] = primitive + FIRSTCALLEDLOCATIONINFORMATIONEXTENSION;
    msterminatingsmsinmsc[ 53] = primitive + MMENAME;
    msterminatingsmsinmsc[ 54] = primitive + UETIMEZONE;
    msterminatingsmsinmsc[ 55] = primitive + LASTCALLEDLOCATIONINFORMATIONEXTENSION;

    /* pad out the array where tags are not defined */
    for (n = 56; n < 102; n++)
        msterminatingsmsinmsc[n] = NULL;

    msterminatingsmsinmsc[102] = primitive + OUTPUTTYPE;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msoriginatingsmsinmsc.h"
#include "components.h"

extern asn1Object primitive[];
extern asn1Object *camelTDPData[];

asn1Object *msoriginatingsmsinmsc[MSORIGINATINGSMSINMSC_MAX_FIELDS];


void initialiseMSOriginatingSMSinMSC(void)
{
    int n;

    msoriginatingsmsinmsc[  0] = primitive + TAC;
    msoriginatingsmsinmsc[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    msoriginatingsmsinmsc[  2] = primitive + RECORDSEQUENCENUMBER;
    msoriginatingsmsinmsc[  3] = primitive + TYPEOFCALLINGSUBSCRIBER;
    msoriginatingsmsinmsc[  4] = primitive + CALLINGPARTYNUMBER;
    msoriginatingsmsinmsc[  5] = primitive + CALLINGSUBSCRIBERIMSI;
    msoriginatingsmsinmsc[  6] = primitive + CALLINGSUBSCRIBERIMEI;
    msoriginatingsmsinmsc[  7] = primitive + DATEFORSTARTOFCHARGE;
    msoriginatingsmsinmsc[  8] = primitive + TIMEFORSTARTOFCHARGE;
    msoriginatingsmsinmsc[  9] = primitive + CHARGEDPARTY;
    msoriginatingsmsinmsc[ 10] = primitive + ORIGINFORCHARGING;
    msoriginatingsmsinmsc[ 11] = primitive + EXCHANGEIDENTITY;
    msoriginatingsmsinmsc[ 12] = primitive + MSCIDENTIFICATION;
    msoriginatingsmsinmsc[ 13] = primitive + INCOMINGROUTE;
    msoriginatingsmsinmsc[ 14] = primitive + FIRSTCALLINGLOCATIONINFORMATION;
    msoriginatingsmsinmsc[ 15] = primitive + TELESERVICECODE;
    msoriginatingsmsinmsc[ 16] = primitive + SERVICECENTREADDRESS;
    msoriginatingsmsinmsc[ 17] = primitive + CALLINGSUBSCRIBERIMEISV;
    msoriginatingsmsinmsc[ 19] = primitive + ICIORDERED;
    msoriginatingsmsinmsc[ 20] = primitive + OUTPUTFORSUBSCRIBER;
    msoriginatingsmsinmsc[ 21] = primitive + MISCELLANEOUSINFORMATION;
    msoriginatingsmsinmsc[ 22] = primitive + REGIONALSERVICEUSED;
    msoriginatingsmsinmsc[ 23] = primitive + REGIONDEPENDENTCHARGINGORIGIN;
    msoriginatingsmsinmsc[ 24] = primitive + CHANNELALLOCATIONPRIORITYLEVEL;
    msoriginatingsmsinmsc[ 25] = primitive + FREQUENCYBANDSUPPORTED;
    msoriginatingsmsinmsc[ 26] = primitive + INCOMPLETECALLDATAINDICATOR;
    msoriginatingsmsinmsc[ 27] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    msoriginatingsmsinmsc[ 28] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    msoriginatingsmsinmsc[ 29] = primitive + POSITIONACCURACY;
    msoriginatingsmsinmsc[ 30] = primitive + USERTERMINALPOSITION;
    msoriginatingsmsinmsc[ 31] = primitive + SWITCHIDENTITY;
    msoriginatingsmsinmsc[ 32] = primitive + DESTINATIONADDRESS;
    msoriginatingsmsinmsc[ 33] = primitive + MESSAGEREFERENCE;
    msoriginatingsmsinmsc[ 34] = primitive + MESSAGETYPEINDICATOR;
    msoriginatingsmsinmsc[ 35] = primitive + RNCIDOFFIRSTRNC;

    /* component[36] is a constructor */
    msoriginatingsmsinmsc[36] = (asn1Object*) malloc(sizeof(asn1Object));
    msoriginatingsmsinmsc[36]->name = (char*) malloc(MAX_FIELD_LEN);
    memset(msoriginatingsmsinmsc[36]->name, 0, MAX_FIELD_LEN);
    sprintf(msoriginatingsmsinmsc[36]->name, "bCSMTDPData1");
    msoriginatingsmsinmsc[36]->type = CONSTRUCTOR;
    msoriginatingsmsinmsc[36]->ref.next = camelTDPData;

    msoriginatingsmsinmsc[ 37] = primitive + CAMELCALLINGPARTYNUMBER;
    msoriginatingsmsinmsc[ 38] = primitive + CAMELDESTINATIONADDRESS;
    msoriginatingsmsinmsc[ 39] = primitive + CAMELSMSCADDRESS;
    msoriginatingsmsinmsc[ 40] = primitive + DEFAULTSMSHANDLING;
    msoriginatingsmsinmsc[ 41] = primitive + FREEFORMATDATA;
    msoriginatingsmsinmsc[ 42] = primitive + SMSRESULT;
    msoriginatingsmsinmsc[ 43] = primitive + SMSREFERENCENUMBER;
    msoriginatingsmsinmsc[ 44] = primitive + MSCADDRESS;
    msoriginatingsmsinmsc[ 45] = primitive + RTCINDICATOR;
    msoriginatingsmsinmsc[ 46] = primitive + RTCSESSIONID;
    msoriginatingsmsinmsc[ 47] = primitive + RTCDEFAULTSERVICEHANDLING;
    msoriginatingsmsinmsc[ 48] = primitive + RTCFAILUREINDICATOR;
    msoriginatingsmsinmsc[ 49] = primitive + RTCNOTINVOKEDREASON;
    msoriginatingsmsinmsc[ 50] = primitive + MCASMSINDICATOR;
    msoriginatingsmsinmsc[ 51] = primitive + REROUTEDTOSERVICECENTREADDRESS;
    msoriginatingsmsinmsc[ 52] = primitive + BLADEID;
    msoriginatingsmsinmsc[ 53] = primitive + BUDDYBLADEINDICATOR;
    msoriginatingsmsinmsc[ 54] = primitive + TRAFFICISOLATIONINDICATOR;
    msoriginatingsmsinmsc[ 55] = primitive + FIRSTCALLINGLOCATIONINFORMATIONEXTENSION;
    msoriginatingsmsinmsc[ 56] = primitive + MMENAME;
    msoriginatingsmsinmsc[ 57] = primitive + UETIMEZONE;

    /* pad out the array where tags are not defined */
    for (n = 58; n < 102; n++)
        msoriginatingsmsinmsc[n] = NULL;

    msoriginatingsmsinmsc[102] = primitive + OUTPUTTYPE;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transitinoutgoingcall.h"
#include "components.h"

extern asn1Object primitive[];

asn1Object *transitinoutgoingcall[TRANSITINOUTGOINGCALL_MAX_FIELDS];


void initialiseTransitINOutgoingCall(void)
{
    int n;

    transitinoutgoingcall[  0] = primitive + TAC;
    transitinoutgoingcall[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    transitinoutgoingcall[  2] = primitive + RECORDSEQUENCENUMBER;
    transitinoutgoingcall[  3] = primitive + OUTGOINGROUTE;
    transitinoutgoingcall[  4] = primitive + SUBSCRIPTIONTYPE;
    transitinoutgoingcall[  5] = primitive + INCOMPLETECALLDATAINDICATOR;
    transitinoutgoingcall[  6] = primitive + INCOMPLETECOMPOSITECDRINDICATOR;
    transitinoutgoingcall[  7] = primitive + LASTPARTIALOUTPUT;
    transitinoutgoingcall[  8] = primitive + PARTIALOUTPUTRECNUM;
    transitinoutgoingcall[  9] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    transitinoutgoingcall[ 10] = primitive + EXCHANGEIDENTITY;
    transitinoutgoingcall[ 11] = primitive + RESTARTDURINGCALL;
    transitinoutgoingcall[ 12] = primitive + NETWORKCALLREFERENCE;
    transitinoutgoingcall[ 13] = primitive + ICIORDERED;
    transitinoutgoingcall[ 14] = primitive + OUTPUTFORSUBSCRIBER;
    transitinoutgoingcall[ 15] = primitive + SWITCHIDENTITY;
    transitinoutgoingcall[ 16] = primitive + DISCONNECTIONDUETOSYSTEMRECOVERY;
    transitinoutgoingcall[ 17] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    transitinoutgoingcall[ 18] = primitive + TARIFFCLASS;
    transitinoutgoingcall[ 19] = primitive + FORLOPPRELEASEDURINGCALL;
    transitinoutgoingcall[ 20] = primitive + C7CHARGINGMESSAGE;
    transitinoutgoingcall[ 21] = primitive + C7FIRSTCHTMESSAGE;
    transitinoutgoingcall[ 22] = primitive + C7SECONDCHTMESSAGE;
    transitinoutgoingcall[ 23] = primitive + CONTRACTORNUMBER;
    transitinoutgoingcall[ 24] = primitive + CALLEDPARTYMNPINFO;
    transitinoutgoingcall[ 25] = primitive + GLOBALCALLREFERENCE;
    transitinoutgoingcall[ 26] = primitive + OUTGOINGPCHARGINGVECTOR;
    transitinoutgoingcall[ 27] = primitive + BLADEID;
    transitinoutgoingcall[ 28] = primitive + TRAFFICISOLATIONINDICATOR;

    /* pad out the array where tags are not defined */
    for (n = 29; n < TRANSITINOUTGOINGCALL_MAX_FIELDS; n++)
        transitinoutgoingcall[n] = NULL;

    transitinoutgoingcall[102] = primitive + OUTPUTTYPE;
}


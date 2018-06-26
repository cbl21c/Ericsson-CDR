#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msterminatingsmsinsmsgmsc.h"
#include "components.h"

extern asn1Object primitive[];
extern asn1Object *camelTDPData[];

asn1Object *msterminatingsmsinsmsgmsc[MSTERMINATINGSMSINSMSGMSC_MAX_FIELDS];


void initialiseMSTerminatingSMSinSMSGMSC(void)
{
    int n;

    msterminatingsmsinsmsgmsc[  0] = primitive + TAC;
    msterminatingsmsinsmsgmsc[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    msterminatingsmsinsmsgmsc[  2] = primitive + RECORDSEQUENCENUMBER;
    msterminatingsmsinsmsgmsc[  3] = primitive + CALLEDPARTYNUMBER;
    msterminatingsmsinsmsgmsc[  4] = primitive + CALLEDSUBSCRIBERIMSI;
    msterminatingsmsinsmsgmsc[  5] = primitive + MOBILESTATIONROAMINGNUMBER;
    msterminatingsmsinsmsgmsc[  6] = primitive + DATEFORSTARTOFCHARGE;
    msterminatingsmsinsmsgmsc[  7] = primitive + TIMEFORSTARTOFCHARGE;
    msterminatingsmsinsmsgmsc[  8] = primitive + CHARGEDPARTY;
    msterminatingsmsinsmsgmsc[  9] = primitive + EXCHANGEIDENTITY;
    msterminatingsmsinsmsgmsc[ 10] = primitive + MSCIDENTIFICATION;
    msterminatingsmsinsmsgmsc[ 11] = primitive + TELESERVICECODE;
    msterminatingsmsinsmsgmsc[ 12] = primitive + SERVICECENTREADDRESS;
    msterminatingsmsinsmsgmsc[ 13] = primitive + MSCNUMBER;
    msterminatingsmsinsmsgmsc[ 14] = primitive + MISCELLANEOUSINFORMATION;
    msterminatingsmsinsmsgmsc[ 15] = primitive + INCOMPLETECALLDATAINDICATOR;
    msterminatingsmsinsmsgmsc[ 16] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    msterminatingsmsinsmsgmsc[ 17] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    msterminatingsmsinsmsgmsc[ 18] = primitive + NUMBEROFSHORTMESSAGES;
    msterminatingsmsinsmsgmsc[ 19] = primitive + SWITCHIDENTITY;
    msterminatingsmsinsmsgmsc[ 20] = primitive + BLADEID;

    /* pad out the array where tags are not defined */
    for (n = 21; n < 102; n++)
        msterminatingsmsinsmsgmsc[n] = NULL;

    msterminatingsmsinsmsgmsc[102] = primitive + OUTPUTTYPE;
}


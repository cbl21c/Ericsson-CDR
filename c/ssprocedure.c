#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssprocedure.h"
#include "components.h"

extern asn1Object primitive[];

asn1Object *ssprocedure[SSPROCEDURE_MAX_FIELDS];


void initialiseSSProcedure(void)
{
    int n;

    ssprocedure[  0] = primitive + TAC;
    ssprocedure[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    ssprocedure[  2] = primitive + RECORDSEQUENCENUMBER;
    ssprocedure[  3] = primitive + TYPEOFCALLINGSUBSCRIBER;
    ssprocedure[  4] = primitive + CALLINGPARTYNUMBER;
    ssprocedure[  5] = primitive + CALLINGSUBSCRIBERIMSI;
    ssprocedure[  6] = primitive + CALLINGSUBSCRIBERIMEI;
    ssprocedure[  7] = primitive + DATEFORSTARTOFCHARGE;
    ssprocedure[  8] = primitive + TIMEFORSTARTOFCHARGE;
    ssprocedure[  9] = primitive + ORIGINFORCHARGING;
    ssprocedure[ 10] = primitive + EXCHANGEIDENTITY;
    ssprocedure[ 11] = primitive + MSCIDENTIFICATION;
    ssprocedure[ 12] = primitive + FIRSTCALLINGLOCATIONINFORMATION;
    ssprocedure[ 13] = primitive + CALLINGSUBSCRIBERIMEISV;
    /* no tag for 14 */
    ssprocedure[ 14] = NULL;
    ssprocedure[ 15] = primitive + ICIORDERED;
    ssprocedure[ 16] = primitive + OUTPUTFORSUBSCRIBER;
    ssprocedure[ 17] = primitive + SSCODE;
    ssprocedure[ 18] = primitive + SSREQUEST;
    ssprocedure[ 19] = primitive + MISCELLANEOUSINFORMATION;
    ssprocedure[ 20] = primitive + REGIONALSERVICEUSED;
    ssprocedure[ 21] = primitive + REGIONDEPENDENTCHARGINGORIGIN;
    ssprocedure[ 22] = primitive + RELATEDCALLNUMBER;
    ssprocedure[ 23] = primitive + USSDAPPLICATIONIDENTIFIER;
    ssprocedure[ 24] = primitive + USSDSERVICECODE;
    ssprocedure[ 25] = primitive + USSDPROCEDURECODE;
    ssprocedure[ 26] = primitive + NETWORKINITIATEDUSSDOPERATIONS;
    ssprocedure[ 27] = primitive + USSDOPERATIONIDENTIFIER;
    ssprocedure[ 28] = primitive + INCOMPLETECALLDATAINDICATOR;
    ssprocedure[ 29] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    ssprocedure[ 30] = primitive + FREQUENCYBANDSUPPORTED;
    ssprocedure[ 31] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    ssprocedure[ 32] = primitive + SWITCHIDENTITY;
    ssprocedure[ 33] = primitive + NETWORKCALLREFERENCE;
    ssprocedure[ 34] = primitive + POSITIONACCURACY;
    ssprocedure[ 35] = primitive + USERTERMINALPOSITION;
    ssprocedure[ 36] = primitive + RNCIDOFFIRSTRNC;
    ssprocedure[ 37] = primitive + GLOBALCALLREFERENCE;
    ssprocedure[ 38] = primitive + BLADEID;
    ssprocedure[ 39] = primitive + BUDDYBLADEINDICATOR;
    ssprocedure[ 40] = primitive + MMENAME;

    /* pad out the array where tags are not defined */
    for (n = 41; n < SSPROCEDURE_MAX_FIELDS; n++)
        ssprocedure[n] = NULL;

    ssprocedure[102] = primitive + OUTPUTTYPE;
}


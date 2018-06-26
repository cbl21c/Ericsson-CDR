#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msoriginatingsmsinsmsiwmsc.h"
#include "components.h"

extern asn1Object primitive[];

asn1Object *msoriginatingsmsinsmsiwmsc[MSORIGINATINGSMSINSMSIWMSC_MAX_FIELDS];


void initialiseMSOriginatingSMSinSMSIWMSC(void)
{
    int n;

    msoriginatingsmsinsmsiwmsc[  0] = primitive + TAC;
    msoriginatingsmsinsmsiwmsc[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    msoriginatingsmsinsmsiwmsc[  2] = primitive + RECORDSEQUENCENUMBER;
    msoriginatingsmsinsmsiwmsc[  3] = primitive + CALLINGPARTYNUMBER;
    msoriginatingsmsinsmsiwmsc[  4] = primitive + DATEFORSTARTOFCHARGE;
    msoriginatingsmsinsmsiwmsc[  5] = primitive + TIMEFORSTARTOFCHARGE;
    msoriginatingsmsinsmsiwmsc[  6] = primitive + CHARGEDPARTY;
    msoriginatingsmsinsmsiwmsc[  7] = primitive + EXCHANGEIDENTITY;
    msoriginatingsmsinsmsiwmsc[  8] = primitive + MSCIDENTIFICATION;
    msoriginatingsmsinsmsiwmsc[  9] = primitive + TELESERVICECODE;
    msoriginatingsmsinsmsiwmsc[ 10] = primitive + SERVICECENTREADDRESS;
    msoriginatingsmsinsmsiwmsc[ 11] = primitive + MISCELLANEOUSINFORMATION;
    msoriginatingsmsinsmsiwmsc[ 12] = primitive + INCOMPLETECALLDATAINDICATOR;
    msoriginatingsmsinsmsiwmsc[ 13] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    msoriginatingsmsinsmsiwmsc[ 14] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    msoriginatingsmsinsmsiwmsc[ 15] = primitive + SWITCHIDENTITY;
    msoriginatingsmsinsmsiwmsc[ 16] = primitive + BLADEID;

    /* pad out the array where tags are not defined */
    for (n = 17; n < 102; n++)
        msoriginatingsmsinsmsiwmsc[n] = NULL;

    msoriginatingsmsinsmsiwmsc[102] = primitive + OUTPUTTYPE;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inincomingcall.h"
#include "components.h"

extern asn1Object primitive[];
extern asn1Object *triggerData[];

asn1Object *inincomingcall[ININCOMINGCALL_MAX_FIELDS];


void initialiseINIncomingCall(void)
{
    int n;

    inincomingcall[  0] = primitive + CALLIDENTIFICATIONNUMBER;
    inincomingcall[  1] = primitive + SWITCHIDENTITY;
    inincomingcall[  2] = primitive + NETWORKCALLREFERENCE;
    inincomingcall[  3] = primitive + INSERVICETRIGGER;
    inincomingcall[  4] = primitive + SSFCHARGINGCASE;

    /* components[5 to 12] are constructors */
    /* name = 'triggerData1..7' */
    for (n = 5; n < 13; n++)
    {
        inincomingcall[n] = (asn1Object*) malloc(sizeof(asn1Object));
        inincomingcall[n]->name = (char*) malloc(MAX_FIELD_LEN);
        memset(inincomingcall[n]->name, 0, MAX_FIELD_LEN);
        sprintf(inincomingcall[n]->name, "triggerData%d", n - 5);
        inincomingcall[n]->type = CONSTRUCTOR;
        inincomingcall[n]->ref.next = triggerData;
    }

    inincomingcall[ 13] = primitive + RECORDSEQUENCENUMBER;
    inincomingcall[ 14] = primitive + DISCONNECTIONDUETOSYSTEMRECOVERY;
    inincomingcall[ 15] = primitive + INCOMPLETECALLDATAINDICATOR;
    inincomingcall[ 16] = primitive + INCOMPLETECOMPOSITECDRINDICATOR;
    inincomingcall[ 17] = primitive + LASTPARTIALOUTPUT;
    inincomingcall[ 18] = primitive + PARTIALOUTPUTRECNUM;
    inincomingcall[ 19] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    inincomingcall[ 20] = primitive + RESTARTDURINGCALL;
    inincomingcall[ 21] = primitive + EXCHANGEIDENTITY;
    inincomingcall[ 22] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    inincomingcall[ 23] = primitive + FORLOPPRELEASEDURINGCALL;
    inincomingcall[ 24] = primitive + GSMCALLREFERENCENUMBER;
    inincomingcall[ 25] = primitive + MSCADDRESS;
    inincomingcall[ 26] = primitive + DEFAULTCALLHANDLING;
    inincomingcall[ 27] = primitive + DEFAULTCALLHANDLING2;
    inincomingcall[ 28] = primitive + LEVELOFCAMELSERVICE;
    inincomingcall[ 29] = primitive + GLOBALCALLREFERENCE;
    inincomingcall[ 30] = primitive + BLADEID;
    inincomingcall[ 31] = primitive + TRAFFICISOLATIONINDICATOR;

    /* pad out the array where tags are not defined */
    for (n = 32; n < ININCOMINGCALL_MAX_FIELDS; n++)
        inincomingcall[n] = NULL;

    inincomingcall[102] = primitive + OUTPUTTYPE;
}


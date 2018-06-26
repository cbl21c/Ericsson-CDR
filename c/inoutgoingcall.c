#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inoutgoingcall.h"
#include "components.h"

extern asn1Object primitive[];
extern asn1Object *triggerData[];

asn1Object *inoutgoingcall[INOUTGOINGCALL_MAX_FIELDS];


void initialiseINOutgoingCall(void)
{
    int n;

    inoutgoingcall[  0] = primitive + CALLIDENTIFICATIONNUMBER;
    inoutgoingcall[  1] = primitive + SWITCHIDENTITY;
    inoutgoingcall[  2] = primitive + NETWORKCALLREFERENCE;
    inoutgoingcall[  3] = primitive + INSERVICETRIGGER;
    inoutgoingcall[  4] = primitive + SSFCHARGINGCASE;

    /* components[5 to 12] are constructors */
    /* name = 'triggerData1..7' */
    for (n = 5; n < 13; n++)
    {
        inoutgoingcall[n] = (asn1Object*) malloc(sizeof(asn1Object));
        inoutgoingcall[n]->name = (char*) malloc(MAX_FIELD_LEN);
        memset(inoutgoingcall[n]->name, 0, MAX_FIELD_LEN);
        sprintf(inoutgoingcall[n]->name, "triggerData%d", n - 5);
        inoutgoingcall[n]->type = CONSTRUCTOR;
        inoutgoingcall[n]->ref.next = triggerData;
    }

    inoutgoingcall[ 13] = primitive + RECORDSEQUENCENUMBER;
    inoutgoingcall[ 14] = primitive + DISCONNECTIONDUETOSYSTEMRECOVERY;
    inoutgoingcall[ 15] = primitive + INCOMPLETECALLDATAINDICATOR;
    inoutgoingcall[ 16] = primitive + INCOMPLETECOMPOSITECDRINDICATOR;
    inoutgoingcall[ 17] = primitive + LASTPARTIALOUTPUT;
    inoutgoingcall[ 18] = primitive + PARTIALOUTPUTRECNUM;
    inoutgoingcall[ 19] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    inoutgoingcall[ 20] = primitive + RESTARTDURINGCALL;
    inoutgoingcall[ 21] = primitive + EXCHANGEIDENTITY;
    inoutgoingcall[ 22] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    inoutgoingcall[ 23] = primitive + FORLOPPRELEASEDURINGCALL;
    inoutgoingcall[ 24] = primitive + GSMCALLREFERENCENUMBER;
    inoutgoingcall[ 25] = primitive + MSCADDRESS;
    inoutgoingcall[ 26] = primitive + DEFAULTCALLHANDLING;
    inoutgoingcall[ 27] = primitive + DEFAULTCALLHANDLING2;
    inoutgoingcall[ 28] = primitive + LEVELOFCAMELSERVICE;
    inoutgoingcall[ 29] = primitive + GSMSCFINITIATEDCALLINDICATOR;
    inoutgoingcall[ 30] = primitive + GLOBALCALLREFERENCE;
    inoutgoingcall[ 31] = primitive + BLADEID;
    inoutgoingcall[ 32] = primitive + TRAFFICISOLATIONINDICATOR;

    /* pad out the array where tags are not defined */
    for (n = 32; n < INOUTGOINGCALL_MAX_FIELDS; n++)
        inoutgoingcall[n] = NULL;

    inoutgoingcall[102] = primitive + OUTPUTTYPE;
}


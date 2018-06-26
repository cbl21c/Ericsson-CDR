#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inservicedataeventmodule.h"
#include "components.h"

extern asn1Object primitive[];

asn1Object *inservicedataeventmodule[INSERVICEDATAEVENTMODULE_MAX_FIELDS];


void initialiseINServiceDataEventModule(void)
{
    inservicedataeventmodule[  0] = primitive + CHARGEPARTYDISTRIBUTED;
    inservicedataeventmodule[  1] = primitive + CHARGEPARTYSINGLE;
    inservicedataeventmodule[  2] = primitive + CHARGINGUNITSADDITION;
    inservicedataeventmodule[  3] = primitive + GENERICCHARGINGDIGITS;
    inservicedataeventmodule[  4] = primitive + GENERICCHARGINGNUMBERS;
    inservicedataeventmodule[  5] = primitive + SERVICEFEATURECODE;
    inservicedataeventmodule[  6] = primitive + TIMEFOREVENT;
    inservicedataeventmodule[  7] = primitive + INCOMPLETECALLDATAINDICATOR;
    inservicedataeventmodule[  8] = primitive + FREEFORMATDATA;
    inservicedataeventmodule[  9] = primitive + SSFLEGID;
    inservicedataeventmodule[ 10] = primitive + FREEFORMATDATA2;
    inservicedataeventmodule[ 11] = primitive + FREEFORMATDATAAPPENDINDICATOR;
    inservicedataeventmodule[ 12] = primitive + FREEFORMATDATAAPPENDINDICATOR2;
}


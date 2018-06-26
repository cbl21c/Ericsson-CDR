#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssieventmodule.h"
#include "components.h"

extern asn1Object primitive[];

asn1Object *ssieventmodule[SSIEVENTMODULE_MAX_FIELDS];


void initialiseSSIEventModule(void)
{
    ssieventmodule[  0] = primitive + TAC;
    ssieventmodule[  1] = primitive + SSCODE;
    ssieventmodule[  2] = primitive + SSREQUEST;
    ssieventmodule[  3] = primitive + TIMEFOREVENT;
    ssieventmodule[  4] = primitive + FIRSTCALLINGLOCATIONINFORMATION;
    ssieventmodule[  5] = primitive + CRIINDICATOR;
    ssieventmodule[  6] = primitive + EVENTCRITOMS;
    ssieventmodule[  7] = primitive + INCOMPLETECALLDATAINDICATOR;
    ssieventmodule[  9] = primitive + NETWORKCALLREFERENCE;
    ssieventmodule[ 10] = primitive + SSINVOCATIONNOTIFICATION;
    ssieventmodule[ 11] = primitive + GLOBALCALLREFERENCE;
}


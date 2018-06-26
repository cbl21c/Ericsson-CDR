#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serviceswitcheventmodule.h"
#include "components.h"

extern asn1Object primitive[];

asn1Object *serviceswitcheventmodule[SERVICESWITCHEVENTMODULE_MAX_FIELDS];


void initialiseServiceSwitchEventModule(void)
{
    serviceswitcheventmodule[  0] = primitive + TAC;
    serviceswitcheventmodule[  1] = primitive + TIMEFOREVENT;
    serviceswitcheventmodule[  2] = primitive + SERVICESWITCHINGTYPE;
    serviceswitcheventmodule[  3] = primitive + INCOMPLETECALLDATAINDICATOR;
}


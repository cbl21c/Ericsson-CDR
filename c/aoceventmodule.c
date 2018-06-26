#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoceventmodule.h"
#include "components.h"

extern asn1Object primitive[];

asn1Object *aoceventmodule[AOCEVENTMODULE_MAX_FIELDS];


void initialiseAoCEventModule(void)
{
    aoceventmodule[  0] = primitive + TAC;
    aoceventmodule[  1] = primitive + CRITOMS;
    aoceventmodule[  2] = primitive + CRIINDICATOR;
    aoceventmodule[  3] = primitive + SSCODE;
    aoceventmodule[  4] = primitive + TIMEFOREVENT;
    aoceventmodule[  5] = primitive + INCOMPLETECALLDATAINDICATOR;
    aoceventmodule[  6] = primitive + GSMSCFCONTROLOFAOC;
}


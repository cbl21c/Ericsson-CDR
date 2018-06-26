#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "components.h"
#include "cme20mss16a.h"
#include "transit.h"
#include "msoriginating.h"
#include "roamingcallforwarding.h"
#include "callforwarding.h"
#include "msterminating.h"
#include "msoriginatingsmsinmsc.h"
#include "msoriginatingsmsinsmsiwmsc.h"
#include "msterminatingsmsinmsc.h"
#include "msterminatingsmsinsmsgmsc.h"
#include "ssprocedure.h"
#include "aoceventmodule.h"
#include "ssieventmodule.h"
#include "serviceswitcheventmodule.h"
#include "transitinoutgoingcall.h"
#include "inincomingcall.h"
#include "inoutgoingcall.h"
#include "inservicedataeventmodule.h"
// #include "isdnoriginating.h"
// #include "isdncallforwarding.h"
// #include "isdnssprocedure.h"
// #include "chargeratechangeeventmodule.h"
// #include "scfchargingoutput.h"
// #include "isdnssinvocationeventmodule.h"
// #include "locationservices.h"
// #include "handovereventmodule.h"

#define ROOT_MAX_FIELDS 2
#define COMPOSITECALLDATARECORD_MAX_FIELDS 1
#define UMTSGSMPLMNCALLDATARECORD_MAX_FIELDS 25
#define EVENTMODULE_MAX_FIELDS 26

asn1Object *root[ROOT_MAX_FIELDS];
asn1Object *compositecalldatarecord[COMPOSITECALLDATARECORD_MAX_FIELDS];
asn1Object *umtsgsmplmncalldatarecord[UMTSGSMPLMNCALLDATARECORD_MAX_FIELDS];
asn1Object *eventmodule[EVENTMODULE_MAX_FIELDS];


void initialiseCme20Mss16a(void)
{
    int n;

    /* initialisation of components and cdr types */
    initialiseCDRObjects();

    initialiseTransit();
    initialiseMSOriginating();
    initialiseRoamingCallForwarding();
    initialiseCallForwarding();
    initialiseMSTerminating();
    initialiseMSOriginatingSMSinMSC();
    initialiseMSOriginatingSMSinSMSIWMSC();
    initialiseMSTerminatingSMSinMSC();
    initialiseMSTerminatingSMSinSMSGMSC();
    initialiseSSProcedure();
    initialiseAoCEventModule();
    initialiseSSIEventModule();
    initialiseServiceSwitchEventModule();
    initialiseTransitINOutgoingCall();
    initialiseINIncomingCall();
    initialiseINOutgoingCall();
    initialiseINServiceDataEventModule();
    // initialiseISDNOriginating();
    // initialiseISDNCallForwarding();
    // initialiseISDNSSProcedure();
    // initialiseChargeRateChangeEventModule();
    // initialiseSCFChargingOutput();
    // initialiseISDNSSInvocationEventModule();
    // initialiseLocationServices();
    // initialiseHandOverEventModule();



    /* initialise eventmodule object */
    for (n = 0; n < EVENTMODULE_MAX_FIELDS; n++)
    {
        eventmodule[n] = (asn1Object*) malloc(sizeof(asn1Object));
        eventmodule[n]->name = (char*) malloc(MAX_FIELD_LEN);
        memset(eventmodule[n]->name, 0, MAX_FIELD_LEN);
        eventmodule[n]->type = CONSTRUCTOR;
        eventmodule[n]->ref.next = NULL;
    }

    strcpy(eventmodule[10]->name, "aoCEventModule");
    eventmodule[10]->ref.next = aoceventmodule;

    strcpy(eventmodule[11]->name, "sSIEventModule");
    eventmodule[11]->ref.next = ssieventmodule;

    strcpy(eventmodule[12]->name, "serviceSwitchEventModule");
    eventmodule[12]->ref.next = serviceswitcheventmodule;

    strcpy(eventmodule[16]->name, "iNServiceDataEventModule");
    eventmodule[16]->ref.next = inservicedataeventmodule;


    /* initialise umtsgsmplmncalldatarecord object */
    for (n = 0; n < UMTSGSMPLMNCALLDATARECORD_MAX_FIELDS; n++)
    {
        umtsgsmplmncalldatarecord[n] = (asn1Object*) malloc(sizeof(asn1Object));
        umtsgsmplmncalldatarecord[n]->name = (char*) malloc(MAX_FIELD_LEN);
        memset(umtsgsmplmncalldatarecord[n]->name, 0, MAX_FIELD_LEN);
        umtsgsmplmncalldatarecord[n]->type = CONSTRUCTOR;
        umtsgsmplmncalldatarecord[n]->ref.next = NULL;
    }

    n = 0;
    strcpy(umtsgsmplmncalldatarecord[n]->name, "transit");
    umtsgsmplmncalldatarecord[n++]->ref.next = transit;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "mSOriginating");
    umtsgsmplmncalldatarecord[n++]->ref.next = msoriginating;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "roamingCallForwarding");
    umtsgsmplmncalldatarecord[n++]->ref.next = roamingcallforwarding;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "callForwarding");
    umtsgsmplmncalldatarecord[n++]->ref.next = callforwarding;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "mSTerminating");
    umtsgsmplmncalldatarecord[n++]->ref.next = msterminating;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "mSOriginatingSMSinMSC");
    umtsgsmplmncalldatarecord[n++]->ref.next = msoriginatingsmsinmsc;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "mSOriginatingSMSinSMS-IWMSC");
    umtsgsmplmncalldatarecord[n++]->ref.next = msoriginatingsmsinsmsiwmsc;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "mSTerminatingSMSinMSC");
    umtsgsmplmncalldatarecord[n++]->ref.next = msterminatingsmsinmsc;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "mSTerminatingSMSinSMS-GMSC");
    umtsgsmplmncalldatarecord[n++]->ref.next = msterminatingsmsinsmsgmsc;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "sSProcedure");
    umtsgsmplmncalldatarecord[n++]->ref.next = ssprocedure;

    n = 13;
    strcpy(umtsgsmplmncalldatarecord[n]->name, "transitINOutgoingCall");
    umtsgsmplmncalldatarecord[n++]->ref.next = transitinoutgoingcall;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "iNIncomingCall");
    umtsgsmplmncalldatarecord[n++]->ref.next = inincomingcall;

    strcpy(umtsgsmplmncalldatarecord[n]->name, "iNOutgoingCall");
    umtsgsmplmncalldatarecord[n++]->ref.next = inoutgoingcall;

    /* SEQUENCE of EventModule */
    strcpy(umtsgsmplmncalldatarecord[n]->name, "eventModule");
    umtsgsmplmncalldatarecord[n++]->ref.next = eventmodule;

    /* no tag at 22 */


    /* initialise compositecalldatarecord object - only one */
    compositecalldatarecord[0] = (asn1Object*) malloc(sizeof(asn1Object));
    compositecalldatarecord[0]->name = (char*) malloc(MAX_FIELD_LEN);
    strcpy(compositecalldatarecord[0]->name, "uMTSGSMPLMNCallDataRecord");
    compositecalldatarecord[0]->type = CONSTRUCTOR;
    compositecalldatarecord[0]->ref.next = umtsgsmplmncalldatarecord;


    /* initialise root object */
    for (n = 0; n < ROOT_MAX_FIELDS; n++)
    {
        root[n] = (asn1Object*) malloc(sizeof(asn1Object));
        root[n]->name = (char*) malloc(MAX_FIELD_LEN);
        memset(root[n]->name, 0, MAX_FIELD_LEN);
        root[n]->type = CONSTRUCTOR;
        root[n]->ref.next = NULL;
    }

    n = 0;
    strcpy(root[n]->name, "uMTSGSMPLMNCallDataRecord");
    root[n++]->ref.next = umtsgsmplmncalldatarecord;

    strcpy(root[n]->name, "compositeCallDataRecord");
    root[n++]->ref.next = compositecalldatarecord;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msoriginating.h"
#include "components.h"

extern asn1Object primitive[];
extern asn1Object *camelTDPData[];
extern asn1Object *multimediaInformation[];

asn1Object *msoriginating[MSORIGINATING_MAX_FIELDS];


void initialiseMSOriginating(void)
{
    int n;

    msoriginating[  0] = primitive + TAC;
    msoriginating[  1] = primitive + CALLIDENTIFICATIONNUMBER;
    msoriginating[  2] = primitive + RECORDSEQUENCENUMBER;
    msoriginating[  3] = primitive + TYPEOFCALLINGSUBSCRIBER;
    msoriginating[  4] = primitive + CALLINGPARTYNUMBER;
    msoriginating[  5] = primitive + CALLINGSUBSCRIBERIMSI;
    msoriginating[  6] = primitive + CALLINGSUBSCRIBERIMEI;
    msoriginating[  7] = primitive + CALLEDPARTYNUMBER;
    msoriginating[  8] = primitive + DISCONNECTINGPARTY;
    msoriginating[  9] = primitive + DATEFORSTARTOFCHARGE;
    msoriginating[ 10] = primitive + TIMEFORSTARTOFCHARGE;
    msoriginating[ 11] = primitive + TIMEFORSTOPOFCHARGE;
    msoriginating[ 12] = primitive + CHARGEABLEDURATION;
    msoriginating[ 13] = primitive + INTERRUPTIONTIME;
    msoriginating[ 14] = primitive + TIMEFROMREGISTERSEIZURETOSTARTOFCHARGING;
    msoriginating[ 15] = primitive + CHARGEDPARTY;
    msoriginating[ 16] = primitive + ORIGINFORCHARGING;
    msoriginating[ 17] = primitive + CHARGINGCASE;
    msoriginating[ 18] = primitive + TARIFFCLASS;
    msoriginating[ 19] = primitive + TARIFFSWITCHIND;
    msoriginating[ 20] = primitive + EXCHANGEIDENTITY;
    msoriginating[ 21] = primitive + MSCIDENTIFICATION;
    msoriginating[ 22] = primitive + OUTGOINGROUTE;
    msoriginating[ 23] = primitive + INCOMINGROUTE;
    msoriginating[ 24] = primitive + MISCELLANEOUSINFORMATION;
    msoriginating[ 25] = primitive + ORIGINATINGLOCATIONNUMBER;
    msoriginating[ 26] = primitive + TIMEFORTCSEIZURECALLING;
    msoriginating[ 27] = primitive + FIRSTCALLINGLOCATIONINFORMATION;
    msoriginating[ 28] = primitive + LASTCALLINGLOCATIONINFORMATION;
    msoriginating[ 29] = primitive + TELESERVICECODE;
    msoriginating[ 30] = primitive + BEARERSERVICECODE;
    msoriginating[ 31] = primitive + TRANSPARENCYINDICATOR;
    msoriginating[ 32] = primitive + FIRSTRADIOCHANNELUSED;
    msoriginating[ 33] = primitive + CALLPOSITION;
    msoriginating[ 34] = primitive + EOSINFO;
    msoriginating[ 35] = primitive + INTERNALCAUSEANDLOC;
    msoriginating[ 36] = primitive + RESTARTDURINGCALL;
    msoriginating[ 37] = primitive + RESTARTDURINGOUTPUTINDICATOR;
    msoriginating[ 38] = primitive + NUMBEROFMETERPULSES;
    msoriginating[ 39] = primitive + C7CHARGINGMESSAGE;
    msoriginating[ 40] = primitive + C7FIRSTCHTMESSAGE;
    msoriginating[ 41] = primitive + C7SECONDCHTMESSAGE;
    msoriginating[ 42] = primitive + CALLEDPARTYMNPINFO;
    msoriginating[ 43] = primitive + CARRIERIDENTIFICATIONCODE;
    msoriginating[ 44] = primitive + DTMFUSED;
    msoriginating[ 45] = primitive + ICIORDERED;
    msoriginating[ 46] = primitive + OUTPUTFORSUBSCRIBER;
    msoriginating[ 47] = primitive + INMARKINGOFMS;
    msoriginating[ 48] = primitive + LASTPARTIALOUTPUT;
    msoriginating[ 49] = primitive + PARTIALOUTPUTRECNUM;
    msoriginating[ 50] = primitive + CUGINTERLOCKCODE;
    msoriginating[ 51] = primitive + CUGINDEX;
    msoriginating[ 52] = primitive + CUGOUTGOINGACCESSUSED;
    msoriginating[ 53] = primitive + CUGOUTGOINGACCESSINDICATOR;
    msoriginating[ 54] = primitive + REGIONALSERVICEUSED;
    msoriginating[ 55] = primitive + REGIONDEPENDENTCHARGINGORIGIN;
    msoriginating[ 56] = primitive + SSCODE;
    msoriginating[ 57] = primitive + CHANNELALLOCATIONPRIORITYLEVEL;
    msoriginating[ 58] = primitive + RADIOCHANNELPROPERTY;
    msoriginating[ 59] = primitive + FAULTCODE;
    msoriginating[ 60] = primitive + INTERMEDIATERATE;
    msoriginating[ 61] = primitive + FIRSTASSIGNEDSPEECHCODERVERSION;
    msoriginating[ 62] = primitive + SPEECHCODERPREFERENCELIST;
    msoriginating[ 63] = primitive + SUBSCRIPTIONTYPE;
    msoriginating[ 64] = primitive + INCOMPLETECALLDATAINDICATOR;
    msoriginating[ 65] = primitive + INCOMPLETECOMPOSITECDRINDICATOR;
    msoriginating[ 66] = primitive + ORIGINATEDCODE;
    msoriginating[ 67] = primitive + SWITCHIDENTITY;
    msoriginating[ 68] = primitive + NETWORKCALLREFERENCE;
    msoriginating[ 69] = primitive + FREQUENCYBANDSUPPORTED;
    msoriginating[ 70] = primitive + DISCONNECTIONDUETOSYSTEMRECOVERY;
    msoriginating[ 71] = primitive + FORLOPPDURINGOUTPUTINDICATOR;
    msoriginating[ 72] = primitive + FORLOPPRELEASEDURINGCALL;
    msoriginating[ 73] = primitive + ACCOUNTCODE;
    msoriginating[ 74] = primitive + TRANSLATEDNUMBER;

    /* components[75 to 84] are constructors */
    /* name = 'bCSMTDPData1..10' */
    for (n = 75; n < 85; n++)
    {
        msoriginating[n] = (asn1Object*) malloc(sizeof(asn1Object));
        msoriginating[n]->name = (char*) malloc(MAX_FIELD_LEN);
        memset(msoriginating[n]->name, 0, MAX_FIELD_LEN);
        sprintf(msoriginating[n]->name, "bCSMTDPData%d", n - 74);
        msoriginating[n]->type = CONSTRUCTOR;
        msoriginating[n]->ref.next = camelTDPData;
    }

    msoriginating[ 85] = primitive + GSMCALLREFERENCENUMBER;
    msoriginating[ 86] = primitive + MSCADDRESS;
    msoriginating[ 87] = primitive + EMLPPPRIORITYLEVEL;
    msoriginating[ 88] = primitive + POSITIONACCURACY;
    msoriginating[ 89] = primitive + USERTERMINALPOSITION;
    msoriginating[ 90] = primitive + ACCEPTABLECHANNELCODINGS;
    msoriginating[ 91] = primitive + INCOMINGASSIGNEDROUTE;
    msoriginating[ 92] = primitive + CHANNELCODINGUSED;
    msoriginating[ 93] = primitive + RANAPCAUSECODE;
    msoriginating[ 94] = primitive + GSMSCFADDRESS;
    msoriginating[ 95] = primitive + FNURREQUESTED;
    msoriginating[ 96] = primitive + AIURREQUESTED;
    msoriginating[ 97] = primitive + NUMBEROFCHANNELSREQUESTED;
    msoriginating[ 98] = primitive + BSSMAPCAUSECODE;
    msoriginating[ 99] = primitive + MULTIMEDIACALL;
    msoriginating[100] = primitive + GUARANTEEDBITRATE;
    msoriginating[101] = primitive + TRAFFICCLASS;
    msoriginating[102] = primitive + OUTPUTTYPE;
    msoriginating[103] = primitive + RNCIDOFFIRSTRNC;
    msoriginating[104] = primitive + MAXBITRATEDOWNLINK;
    msoriginating[105] = primitive + MAXBITRATEUPLINK;
    msoriginating[106] = primitive + TRANSFERDELAY;
    msoriginating[107] = primitive + DELIVERYOFERRONEOUSSDU1;
    msoriginating[108] = primitive + DELIVERYOFERRONEOUSSDU2;
    msoriginating[109] = primitive + DELIVERYOFERRONEOUSSDU3;
    msoriginating[110] = primitive + RESIDUALBITERRORRATIO1;
    msoriginating[111] = primitive + RESIDUALBITERRORRATIO2;
    msoriginating[112] = primitive + RESIDUALBITERRORRATIO3;
    msoriginating[113] = primitive + SDUERRORRATIO1;
    msoriginating[114] = primitive + SDUERRORRATIO2;
    msoriginating[115] = primitive + SDUERRORRATIO3;
    msoriginating[116] = primitive + ACMCHARGINGINDICATOR;
    msoriginating[117] = primitive + ANMCHARGINGINDICATOR;
    msoriginating[118] = primitive + CARRIERINFORMATIONBACKWARD;
    msoriginating[119] = primitive + CHARGEINFORMATION;
    msoriginating[120] = primitive + DISCONNECTIONDATE;
    msoriginating[121] = primitive + REROUTINGINDICATOR;
    msoriginating[122] = primitive + INVOCATIONOFCALLHOLD;
    msoriginating[123] = primitive + RETRIEVALOFHELDCALL;
    msoriginating[124] = primitive + DISCONNECTIONTIME;
    msoriginating[125] = primitive + ORIGINATINGCARRIER;
    msoriginating[126] = primitive + ORIGINATINGCHARGEAREA;
    msoriginating[127] = primitive + TDSCOUNTER;
    msoriginating[128] = primitive + TERMINATINGACCESSISDN;
    msoriginating[129] = primitive + TERMINATINGCARRIER;
    msoriginating[130] = primitive + TERMINATINGCHARGEAREA;
    msoriginating[131] = primitive + TERMINATINGMOBILEUSERCLASS1;
    msoriginating[132] = primitive + TERMINATINGMOBILEUSERCLASS2;
    msoriginating[133] = primitive + TERMINATINGUSERCLASS;
    msoriginating[134] = primitive + CONTRACTORNUMBER;
    msoriginating[135] = primitive + CARRIERINFORMATION;
    msoriginating[136] = primitive + CARRIERSELECTIONSUBSTITUTIONINFORMATION;
    msoriginating[137] = primitive + CHARGENUMBER;
    msoriginating[138] = primitive + INTEREXCHANGECARRIERINDICATOR;
    msoriginating[139] = primitive + ORIGINATINGLINEINFORMATION;
    msoriginating[140] = primitive + SELECTEDCODEC;
    msoriginating[141] = primitive + WPSCALLINDICATOR;
    msoriginating[142] = primitive + USERTOUSERINFORMATION;
    msoriginating[143] = primitive + CALLINGSUBSCRIBERIMEISV;
    msoriginating[144] = primitive + GLOBALCALLREFERENCE;
    msoriginating[145] = primitive + ROAMINGPRIORITYLEVEL;
    msoriginating[146] = primitive + RTCINDICATOR;
    msoriginating[147] = primitive + RTCSESSIONID;
    msoriginating[148] = primitive + RTCDEFAULTSERVICEHANDLING;
    msoriginating[149] = primitive + RTCFAILUREINDICATOR;
    msoriginating[150] = primitive + RTCNOTINVOKEDREASON;
    msoriginating[151] = primitive + CALLEDDIRECTORYNUMBER;
    msoriginating[152] = primitive + OUTGOINGPCHARGINGVECTOR;
    msoriginating[153] = primitive + IUCODEC;
    msoriginating[154] = primitive + BLADEID;
    msoriginating[155] = primitive + BUDDYBLADEINDICATOR;
    msoriginating[156] = primitive + TRAFFICISOLATIONINDICATOR;
    msoriginating[157] = primitive + CCBSCALLINDICATOR;
    msoriginating[158] = primitive + MMENAME;
    msoriginating[159] = primitive + MMEIDENTITY;
    msoriginating[160] = primitive + SRVCCINDICATOR;
    msoriginating[161] = primitive + SRVCCALERTINGINDICATOR;
    msoriginating[162] = primitive + PCHARGINGVECTORRELATED;
    msoriginating[163] = primitive + EMERGENCYSERVICECATEGORY;
    msoriginating[164] = primitive + SRVCCORIGINATINGPREALERTINGINDICATOR;
    msoriginating[165] = primitive + SRVCCCALLHOLDINDICATOR;
    msoriginating[166] = primitive + SRVCCADDITIONALSESSIONINDICATOR;
    msoriginating[167] = primitive + SRVCCCONFERENCEINDICATOR;
    msoriginating[168] = primitive + MOBILESTATIONROAMINGNUMBERINFO; /* market correction */
}


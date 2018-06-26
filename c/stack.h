#ifndef __STACK__
#define __STACK__


#include "components.h"

#define UNKNOWN -1


typedef struct stackitem
{
    asn1Object       **list;
    int              end;
    struct stackitem *next;
} stackitem;


extern asn1Object **stackInitialise(void);
extern asn1Object **stackPush(int, int, int);
extern asn1Object **stackPop(int);
extern asn1Object **stackEndIndefinite(int);
extern void       stackPrint(void);

// extern asn1Object *root[];
// extern asn1Object *compositeCallDataRecord[];
// extern asn1Object *uMTSGSMPLMNCallDataRecord[];



#endif


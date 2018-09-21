#ifndef __SQLRECORD__
#define __SQLRECORD__


extern void sqlInitialise(void);
extern void setCdrFile(char *);
extern void setCdrTable(char *);
extern void sqlPrint(void);
extern void setCallPosition(char *);
extern void parseField(char *, char *);



#endif


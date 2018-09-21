#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sqlrecord.h"

#define TRUE  1
#define FALSE 0
#define SPACE 32
#define ONE_DAY 86400

#define TYPE_NONE 0
#define TYPE_INT  1
#define TYPE_CHAR 2
#define TYPE_ADDR 3
#define TYPE_DATE 4
#define TYPE_TIME 5

int  nparams;
char cdrfile[32];
char insert[1024];
char values[1024];
char cdrType[32];

time_t  dstart, tstart, tstop;

void sqlInitialise(void)
{
    nparams = 0;
    memset(insert, 0, 256);
    memset(values, 0, 256);
    memset(cdrType, 0, 32);
}

void setCdrFile(char *s)
{
    sprintf(cdrfile, "%s", s);
}

void sqlPrint(void)
{
    if (strlen(cdrType) == 0)
        return;

    strcat(insert, ")");
    strcat(values, ")");
    printf("%s %s;\n", insert, values);
}

void setCdrType(char *s)
{
    sprintf(cdrType, s);
    sprintf(insert, "insert into %s(cdrfile", cdrType);
    sprintf(values, "values ('%s'", cdrfile);
}

void parseField(char *key, char *value)
{
    int  type;
    char *pos;
    char digits[33], buf[33];
    char *ton;
    int  ss, mm, hh, dd, mon, yy, seconds;
    struct tm ts;

    type  = TYPE_NONE;

/********************/
/*  INTEGER TYPES   */
/********************/
    /* callPosition | faultCode | redirectionCounter | serviceKey | subscriptionType */
    if (strstr(key, "callPosition") || strstr(key, "faultCode") || strstr(key, "redirectionCounter") || strstr(key, "serviceKey") || strstr(key, "subscriptionType") || strstr(key, "triggerDetectionPoint"))
    {
        /* extra processing for callPosition */
        if (strstr(key, "callPosition"))
        {
            pos = strchr(value, SPACE);
            if (pos)
                *pos = 0;
        }

        type = TYPE_INT;
    }


/********************/
/*  ADDRESS TYPES   */
/********************/
    /* called/calling PartyNumber */
    if (strstr(key, "PartyNumber") || strstr(key, "redirectingNumber") || strstr(key, "translatedNumber") || strstr(key, "mobileStationRoamingNumberInfo") || strstr(key, "gsmSCFAddress") || strstr(key, "globalTitleAndSubSystemNumber"))
    {
        pos = strrchr(value, '=') + 1;
        strcpy(digits, pos);

        pos = strchr(value, SPACE);
        *pos = 0;
        ton = strrchr(value, '=') + 1;

        type = TYPE_ADDR;
    }

/********************/
/*  TIME    TYPES   */
/********************/
    /* timeForStartOfCharge */
    /* timeForStopOfCharge */
    if (strstr(key, "dateForStartOfCharge"))
    {
        pos = strrchr(value, '/');
        yy = atoi(pos + 1) + 2000 - 1900;	/* years since 1900 */

        *pos = 0;
        pos = strrchr(value, '/');
        mon = atoi(pos + 1);

        *pos = 0;
        dd = atoi(value);

        ts.tm_sec = 0;
        ts.tm_min = 0;
        ts.tm_hour = 0;
        ts.tm_mday = dd;
        ts.tm_mon = mon - 1;	 /* struct range is 0 to 11, but decoder output is 1 to 12 */
        ts.tm_year = yy;
        ts.tm_wday = 0;
        ts.tm_yday = 0;
        ts.tm_isdst = 0;
        dstart = mktime(&ts);
    }

    if (strstr(key, "timeForStartOfCharge") || strstr(key, "timeForStopOfCharge") || strstr(key, "chargeableDuration"))
    {
        pos = strrchr(value, ':');
        ss = atoi(pos + 1);

        *pos = 0;
        pos = strrchr(value, ':');
        mm = atoi(pos + 1);

        *pos = 0;
        hh = atoi(value);

        seconds = hh * 3600 + mm * 60 + ss;
        if (strstr(key, "timeForStartOfCharge"))
            tstart = seconds;
        if (strstr(key, "timeForStopOfCharge"))
        {
            /* stop time has crossed over midnight */
            tstop = seconds;
            if (tstop < tstart)
                tstop += ONE_DAY;
        }

        type = TYPE_TIME;
    }

/********************/
/*  CHAR    TYPES   */
/********************/
    /* incomingRoute | outgoingRoute | called/calling Subscriber IMSI | called/calling Subscriber IMEI */
    if (strstr(key, "gRoute") || (strstr(key, "SubscriberIM") && !strstr(key, "SV")) || (strstr(key, "LocationInformation") && !strstr(key, "Extension")) || strstr(key, "globalCallReference"))
    {
        type = TYPE_CHAR;

        /* extra processing for first/last called/calling LocationInformation */
        if (strstr(key, "LocationInformation"))
        {
            pos = strstr(key, "Information");
            *pos = 0;
        }

        /* do not include the 0x prefix for octetstrings */
        if (strstr(key, "globalCallReference"))
        {
            /* memset(buf, 0, 33); */
            /* strcpy(buf, value + 2); */
            /* strcpy(value, buf); */
            value += 2;
        }

        /* do not include SubscriberIMSI in transit records */
        if (strstr(key, "SubscriberIMSI") && strcmp(cdrType, "transit") == 0)
            type = TYPE_NONE;
    }


    /* append the column name and value to the sql query */
    if (type != TYPE_NONE)
    {
        strcat(insert, ", ");
        strcat(values, ", ");

        if (type == TYPE_INT || type == TYPE_CHAR)
        {
            strcat(insert, key);
            if (type == TYPE_INT)
                strcat(values, value);
            else
            {
                strcat(values, "'");
                strcat(values, value);
                strcat(values, "'");
            }
        }
        else if (type == TYPE_ADDR)
        {
            /* special processing for globalTitleAndSubSystemNumber */
            if (strcmp(key, "globalTitleAndSubSystemNumber") == 0)
                strcat(insert, "gsmSCFAddress");
            else
                strcat(insert, key);

            strcat(values, "'");
            strcat(values, digits);
            strcat(values, "'");

            /* if field is not gsmSCFAddress, append "Digits" to field name and add Ton field */
            if (strcmp(key, "gsmSCFAddress") != 0 && strcmp(key, "globalTitleAndSubSystemNumber") != 0)
            {
                strcat(insert, "Digits");

                strcat(insert, ", ");
                strcat(values, ", ");

                strcat(insert, key);
                strcat(insert, "Ton");
                strcat(values, ton);
            }
        }
        else if (type == TYPE_TIME)
        {
            if (strstr(key, "timeForStartOfCharge"))
            {
                strcat(insert, key);
                sprintf(buf, "%d", dstart + tstart);
                strcat(values, buf);
            }
            else if (strstr(key, "timeForStopOfCharge"))
            {
                strcat(insert, key);
                sprintf(buf, "%d", dstart + tstop);
                strcat(values, buf);
            }
            else if (strstr(key, "chargeableDuration"))
            {
                strcat(insert, key);
                sprintf(buf, "%d", seconds);
                strcat(values, buf);
            }
        }
    }
}


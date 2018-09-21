#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "components.h"
#include "stack.h"
#include "sqlrecord.h"


/* states for ASN.1 FSM */
#define STATE_TAG    0x00
#define STATE_LENGTH 0x10
#define STATE_VALUE  0x20

/* tag types */
#define IS_CONSTRUCTOR(x) (x & 0x20)
#define IS_EOC(t, c, l) ((t == 0) & (c == PRIMITIVE) & (l == 0))

#define EXTENDED_TAG 0x1f
#define EXT_BIT_MASK 7

#define LEN_INDEFINITE 0x80
#define BLOCK_SIZE 65536

#define FALSE 0
#define TRUE  1

#define FIELD_LEN 48


int main(int argc, char *argv[])
{
    int ptr, tagOffset, state, depth;
    int datalen, n, len, ll, nbytes;
    byte tag, ch, *data, flIndefinite;
    asn1TagType type;
    char *fname, *basename;
    FILE *fh;
    struct stat buf;
    char SPACES[MAX_LINE_LEN], padding[MAX_LINE_LEN];
    char key[MAX_LINE_LEN], value[MAX_LINE_LEN];
    asn1Object **list;
    int flDataRecord = FALSE;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return -1;
    }


    /* set up spaces */
    memset(SPACES, ' ', MAX_LINE_LEN - 1);
    SPACES[MAX_LINE_LEN - 1] = 0;

    /* input filename */
    fname = argv[argc - 1];

    fh = fopen(fname, "rb");
    if (fh == NULL)
    {
        /* check that the given input file is readable */
        fprintf(stderr, "Could not open file %s\n", fname);
        return -1;
    }

    /* get the file size and allocate memory to store cdr content */
    stat(fname, &buf);
    datalen = buf.st_size;
    data = (byte*) malloc(datalen);

    /* read cdr file contents in blocks */
    ptr = 0;
    while (ptr < buf.st_size)
    {
        nbytes = fread(data + ptr, 1, BLOCK_SIZE, fh);
        ptr += nbytes;
    }
    fclose(fh);

    /* initialise all of the objects */
    initialiseCme20Mss16a();
    list = stackInitialise();
    sqlInitialise();

    /* in case fname comes with a path... */
    basename = strrchr(fname, '/');
    if (basename)
        basename++;
    else
        basename = fname;
    setCdrFile(basename);

    /* go through the ASN.1 state machine */
    state = STATE_TAG;
    ptr = 0;
    depth = 0;
    while (ptr < datalen)
    {
        switch(state)
        {
            case STATE_TAG:
                /* the type is determined by the first octet, even if it is an extended tag */
                type = (IS_CONSTRUCTOR(data[ptr]) ? CONSTRUCTOR : PRIMITIVE);

                if ((data[ptr] & EXTENDED_TAG) == EXTENDED_TAG)
                {
                    ptr++;

                    /* need to read each byte to see if extension bit is set */
                    tag = 0;
                    while (data[ptr] >> EXT_BIT_MASK)
                    {
                        tag = tag * 128 + (data[ptr] & 0x7f);
                        ptr++;
                    }
                    tag = tag * 128 + (data[ptr] & 0x7f);
                }
                else
                    tag = data[ptr] & 0x1f;

                tagOffset = ptr;
                ptr++;

                /* fall through to STATE_LENGTH for efficiency */
                state = STATE_LENGTH;

            case STATE_LENGTH:
                ch = data[ptr++];
                flIndefinite = FALSE;

                if (ch < LEN_INDEFINITE)
                {
                    len = ch;
                    state = STATE_VALUE;
                }
                else
                if (ch == LEN_INDEFINITE)
                {
/* need some way to mark the end of constructor when len is indefinite */
                    flIndefinite = TRUE;
                    len = UNKNOWN;
                    state = STATE_TAG;
                }
                else
                {
                    /* remove the extension flag from the length indicator */
                    ll = ch & 0x7f;

                    len = 0;
                    for (n = 0; n < ll; n++)
                        len = (len << 8) + data[ptr++];

                    state = STATE_VALUE;
                }

                if (IS_EOC(tag, type, len))
                {
                    state = STATE_TAG;
                    list = stackEndIndefinite(ptr);
                    depth = stackDepth();
                }
                else
                {
                    /* print the label, regardless of primitive or constructor */
                    /* but need to check that tag doesn't exceed the array bounds */
                    if (list[tag] != NULL)
                    {
                        /* this is where the tag name is printed */
                        if (list[tag]->name != NULL)
                        {
                            /* check for recognised cdr types */
                            if (flDataRecord)
                            {
                                if (tag == 0)
                                    setCdrType("transit");
                                if (tag == 1)
                                    setCdrType("moc");
                                if (tag == 4)
                                    setCdrType("mtc");

                                flDataRecord = FALSE;
                            }

                            if (strcmp(list[tag]->name, "uMTSGSMPLMNCallDataRecord") == 0)
                            {
                                flDataRecord = TRUE;
                                /* print out previous record */
                                sqlPrint();
                                /* then initialise for new result */
                                sqlInitialise();
                            }
                        }

                        /* but only decode if object is primitive */
                        if (type == PRIMITIVE && list[tag]->ref.decode != NULL)
                        {
                            sprintf(key, list[tag]->name);
                            sprintf(value, list[tag]->ref.decode(len, data + ptr));

                            /* check for recognised fields */
                            parseField(key, value);
                        }
                    }

                    /* if constructor, we need to push it onto the stack */
                    if (type == CONSTRUCTOR)
                    {
                        depth++;
                        list = stackPush(tag, ptr, len);
                    }

                }

                break;

            case STATE_VALUE:
                if (type == PRIMITIVE)
                {
                    ptr += len;
                    list = stackPop(ptr);
                    depth = stackDepth();
                }

                state = STATE_TAG;

                break;
        }

        fflush(stdin);
    }

    return 0;
}


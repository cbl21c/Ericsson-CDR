#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stack.h"
#include "components.h"


stackitem  *stack, *sp;

asn1Object **stackInitialise(void)
{
    /* initialise stack */
    stack = (stackitem*) malloc(sizeof(stackitem));
    stack->list = root;
    stack->end  = INT_MAX;
    stack->next = NULL;

    return stack->list;
}

asn1Object **stackPush(int tag, int pos, int len)
{
    sp = (stackitem*) malloc(sizeof(stackitem));
    if (stack->list[tag] == NULL)
        fprintf(stderr, "Tag %d not found\n", tag);

    sp->list = stack->list[tag]->ref.next;
    /* special case for indefinite length */
    sp->end = (len == UNKNOWN ? UNKNOWN : pos + len);
    sp->next = stack;
    stack = sp;

    // fprintf(stderr, "Push Tag %d at %d ending at %d\n", tag, pos, sp->end);

    return stack->list;
}

asn1Object **stackPop(int pos)
{
    /* do not pop compositeCallDataRecord off the stack */
    while (stack->end != UNKNOWN && pos >= stack->end && stack->next != NULL)
    {
        sp = stack->next;
        free(stack);
        stack = sp;
    }

    return stack->list;
}

asn1Object **stackEndIndefinite(int pos)
{
    while (pos >= stack->end)
    {
        sp = stack->next;
        free(stack);
        stack = sp;
    }

    return stack->list;
}

void stackPrint(void)
{
    int n;

    n = 0;
    sp = stack;
    while (sp != NULL)
    {
        printf(" %d element name: %s\n", n, sp->list[0]->name);
        sp = sp->next;
        n++;
    }
}

int stackDepth(void)
{
    int n;

    n = 0;
    sp = stack;
    while (sp != NULL)
    {
        sp = sp->next;
        n++;
    }

    return n - 1;
}


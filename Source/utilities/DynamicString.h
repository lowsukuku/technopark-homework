#ifndef _DYNAMIC_STRING_H_
#define _DYNAMIC_STRING_H_

#include <stdlib.h>

typedef struct
{
    char *text;
    size_t tailPosition;
    size_t size;
} DynamicString;

int pushSymbol(char symbol, DynamicString *target);
int clearString(DynamicString *target);

#endif
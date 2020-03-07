#ifndef _PARSER_H_
#define _PARSER_H_
#include "utilities/DynamicString.h"
#include "functionDescriptor.h"

char *getDescriptor(char *stringToParse, FunctionDescriptor_t *upperDescriptor, int *lineIndexPointer);
#endif
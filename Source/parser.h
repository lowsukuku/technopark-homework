#ifndef _PARSER_H_
#define _PARSER_H_
#include "utilities/DynamicString.h"
#include "functionDescriptor.h"
char *getDescriptors(char *stringToParse, FunctionDescriptor_t *upperDescriptor, int *lineIndexPointer, DescriptorsList_t **descriptorsList);
void cleanup(DescriptorsList_t *list);
#endif
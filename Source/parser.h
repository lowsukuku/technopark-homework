#ifndef _PARSER_H_
#define _PARSER_H_
#include "utilities/DynamicString.h"
#include "functionDescriptor.h"
extern DescriptorsList_t *descriptorsList;
char *getDescriptors(char *stringToParse, FunctionDescriptor_t *upperDescriptor, int *lineIndexPointer);
void cleanup(DescriptorsList_t *list);
#endif
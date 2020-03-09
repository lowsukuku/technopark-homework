#ifndef _IO_H_
#define _IO_H_
#include "parser.h"
#include <stdio.h>
char *getInput(FILE* stream);
void printDescriptors(DescriptorsList_t *head, FILE* stream);
#endif
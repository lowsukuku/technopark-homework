#ifndef _FUNCTIONAL_DESCRIPTOR_H
#define _FUNCTIONAL_DESCRIPTOR_H

typedef struct
{
    int lineNumber;
    struct LinesList_t *next;
} LinesList_t;

typedef struct
{
    char *name;
    unsigned int parametersCount;
    LinesList_t *linesList;
} FunctionDescriptor_t;

typedef struct 
{
    FunctionDescriptor_t descriptor;
    struct DescriptorsList_t *next;
} DescriptorsList_t;

DescriptorsList_t *addDescriptor(FunctionDescriptor_t descriptor, DescriptorsList_t *head);
DescriptorsList_t *findDescriptor(char *name, DescriptorsList_t *head);
int addEntry(int line, DescriptorsList_t *node);

#endif
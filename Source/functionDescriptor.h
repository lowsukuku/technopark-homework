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
    LinesList_t linesList;
} FunctionDescriptor_t;

typedef struct 
{
    FunctionDescriptor_t descriptor;
    struct DescriptorsList_t *next;
} DescriptorsList_t;

#endif
#include "parser.h"
#include <stdio.h>
#include <string.h>

#define is_potential_identifier_start(c) ( \
    ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || (c) == '_')

#define is_potential_identifier_char(c) ( \
    ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || ((c) >= '0' && (c) <= '9') || (c) == '_')

#define is_skippable_character(c) ( \
    (c) == ' ' || (c) == '\t' || (c) == '\n')

DescriptorsList_t *descriptorsList;

char *getDescriptor(char *stringToParse, FunctionDescriptor_t *upperDescriptor, int *lineIndexPointer)
{
    int identifierLine = 0;
    int isIdentifierStarted = 0;
    int argumentsCount = 0;
    DynamicString identifier = {0};
    FunctionDescriptor_t currentDescriptor = {0};
    while (*stringToParse)
    {
        if (*stringToParse == '#')
        {
            stringToParse = strchr(stringToParse, '\n');
            continue;
        }
        if (*stringToParse == '\'')
        {
            stringToParse = strchr(stringToParse + 1, '\'') + 1;
            continue;
        }
        if (*stringToParse == '"')
        {
            stringToParse = strchr(stringToParse + 1, '"') + 1;
            continue;
        }
        if (is_skippable_character(*stringToParse))
        {
            if (*stringToParse == '\n')
            {
                (*lineIndexPointer)++;
            }
            isIdentifierStarted = 0;
        }
        else if (*stringToParse == ',')
        {
            if (upperDescriptor != NULL)
            {
                upperDescriptor->parametersCount++;
            }
        }
        else if (*stringToParse == '(')
        {
            identifierLine = *lineIndexPointer;
            stringToParse = getDescriptor(stringToParse + 1, &currentDescriptor, lineIndexPointer);
            if (identifier.text != NULL)
            {
                DescriptorsList_t *searchResult = findDescriptor(identifier.text, descriptorsList);
                if (searchResult == NULL)
                {
                    if (descriptorsList != NULL)
                    {
                        void *allocator = malloc(identifier.tailPosition);
                        if (allocator != NULL)
                        {
                            currentDescriptor.name = allocator;
                            strcpy(currentDescriptor.name, identifier.text);
                            addEntrance(identifierLine, addDescriptor(currentDescriptor, descriptorsList));
                        }
                        else
                        {
                            //IMPLEMENT
                        }
                    }
                    else
                    {
                        descriptorsList = malloc(sizeof(DescriptorsList_t)); //CHECK FOR NULL
                        descriptorsList->descriptor.linesList = NULL;
                        void *allocator = malloc(identifier.tailPosition);
                        if (allocator != NULL)
                        {
                            descriptorsList->descriptor.name = allocator;
                            strcpy(descriptorsList->descriptor.name, identifier.text);
                            descriptorsList->descriptor.parametersCount = currentDescriptor.parametersCount;
                            descriptorsList->next = NULL;
                            addEntrance(identifierLine, descriptorsList);
                        }
                        else
                        {
                            //IMPLEMENT
                        }
                    }
                }
                else
                {
                    addEntrance(identifierLine, searchResult);
                }
            }
        }
        else if (*stringToParse == ')')
        {
            if (upperDescriptor->parametersCount > 0 || isIdentifierStarted)
            {
                upperDescriptor->parametersCount++;
            }
            return stringToParse;
        }
        else if (isIdentifierStarted == 0)
        {
            if (is_potential_identifier_start(*stringToParse))
            {
                isIdentifierStarted = 1;
                clearString(&identifier);
                pushSymbol(*stringToParse, &identifier);
            }
        }
        else
        {
            if (is_potential_identifier_char(*stringToParse))
            {
                pushSymbol(*stringToParse, &identifier);
            }
        }
        stringToParse++;
    }
    return 0;
}
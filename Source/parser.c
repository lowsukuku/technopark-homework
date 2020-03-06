#include "parser.h"
#include <stdio.h>
#include <string.h>
#include "utilities/DynamicString.h"
#include "functionDescriptor.h"

#define is_potential_identifier_start(c) ( \
    ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || (c) == '_')

#define is_potential_identifier_char(c) ( \
    ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || ((c) >= '0' && (c) <= '9') || (c) == '_')

#define is_skippable_symbol(c) (\
    (c) == ' ' || (c) == '\t' || (c) == '\n')

DescriptorsList_t *descriptorsList;


int parse(int line, char* stringToParse, size_t stringSize)
{
    
    int isIdentifierStarted = 0, openingBraces = 0, closingBraces = 0, isArgumentStarted = 0;
    int skippableSymbolHit = 0;
    unsigned int argumentsCount = 0;
    DynamicString identifier = {0};
    FunctionDescriptor_t descriptor = {0};
    while (*stringToParse)
    {
        if (*stringToParse == '#')
        {
            stringToParse = strchr(stringToParse, '\n');
            if (stringToParse == NULL) break;
            stringToParse++; continue;
        }
        if (isIdentifierStarted == 0 && is_potential_identifier_start(*stringToParse))
        {
            isIdentifierStarted = 1;
            pushSymbol(*stringToParse, &identifier);
        }
        else if (isIdentifierStarted == 1)
        {
            if (is_potential_identifier_char(*stringToParse))
            {
                if (openingBraces == 1)
                {
                    if (isArgumentStarted == 0)
                    {
                        isArgumentStarted = 1;
                    }
                }
                else if (openingBraces == 0)
                {
                    pushSymbol(*stringToParse, &identifier);
                }
            }
            else if (*stringToParse == '(')
            {
                skippableSymbolHit = 0;
                openingBraces++;
            }
            else if (*stringToParse == ',')
            {
                if (openingBraces-closingBraces == 1 && isArgumentStarted)
                {
                    argumentsCount++;
                    isArgumentStarted = 0;
                }
            }
            else if (*stringToParse == ')')
            {
                skippableSymbolHit = 0;
                closingBraces++;
                if (closingBraces > openingBraces)
                {
                    printf("Error: invalid syntax\n");
                    break;
                }
                else if (closingBraces == openingBraces)
                {
                    if (isArgumentStarted)
                        argumentsCount++;
                    pushSymbol(0, &identifier);
                    DescriptorsList_t *searchResult = findDescriptor(identifier.text, descriptorsList);
                    if (searchResult == NULL)
                    {
                        if (descriptorsList != NULL)
                        {
                            void* allocator = malloc(identifier.tailPosition);
                            if (allocator != NULL)
                            {
                                descriptor.name = allocator;
                                strcpy(descriptor.name, identifier.text);
                                descriptor.parametersCount = argumentsCount;
                                addEntrance(line, addDescriptor(descriptor, descriptorsList));
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
                                strcpy(descriptorsList->descriptor.name, identifier.text); //NAME = NULL!!!!!!!!!
                                descriptorsList->descriptor.parametersCount = argumentsCount;
                                descriptorsList->next = NULL;
                                addEntrance(line, descriptorsList);
                            }
                            else
                            {
                                //IMPLEMENT
                            }
                        } 
                    }
                    else
                    {
                        addEntrance(line, searchResult);
                    }
                    printf("%s, %d\n",identifier.text, argumentsCount);
                    break;
                }
            }
            else if (is_skippable_symbol(*stringToParse))
            {
                skippableSymbolHit = 1;
            }
        }
        stringToParse++;
    }
    if (identifier.text != 0)
    {
        free(identifier.text);
    }
    if (openingBraces > closingBraces)
        return 1;
    return 0;
}
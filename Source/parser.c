#include "parser.h"
#include <stdio.h>
#include <string.h>
#include "utilities/DynamicString.h"
#include "functionDescriptor.h"

#define is_potential_identifier_start(c) ( \
    ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || (c) == '_')

#define is_potential_identifier_char(c) ( \
    ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || ((c) >= '0' && (c) <= '9') || (c) == '_')

DescriptorsList_t *descriptorsList;


int parse(char* stringToParse)
{
    
    int isIdentifierStarted = 0, openingBraces = 0, closingBraces = 0, isArgumentStarted = 0;
    unsigned int argumentsCount = 0;
    DynamicString identifier = {0};
    FunctionDescriptor_t descriptor = {0};
    while (*stringToParse)
    {
        if (*stringToParse == '#')
            break;
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
                            descriptor.name = identifier.text;
                            descriptor.parametersCount = argumentsCount;
                            addEntrance(228, addDescriptor(descriptor, descriptorsList));
                        }
                        else
                        {
                            descriptorsList = malloc(sizeof(DescriptorsList_t)); //CHECK FOR NULL
                            descriptorsList->descriptor.linesList = NULL;
                            strcpy(descriptorsList->descriptor.name, identifier.text); //NAME = NULL!!!!!!!!!
                            descriptorsList->descriptor.parametersCount = argumentsCount;
                            descriptorsList->next = NULL;
                            addEntrance(228, descriptorsList);
                        } 
                    }
                    printf("%s, %d\n",identifier.text, argumentsCount);
                    break;
                }
            }
            else if ((*stringToParse == ' ' || *stringToParse == '\t') && closingBraces == openingBraces)
            {
                isIdentifierStarted = 0;
                clearString(&identifier);
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
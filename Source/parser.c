#include "parser.h"
#include <stdio.h>
#include "utilities/DynamicString.h"

#define is_potential_identifier_start(c) ( \
    ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || (c) == '_')

#define is_potential_identifier_char(c) ( \
    ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || ((c) >= '0' && (c) <= '9') || (c) == '_')

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


void parse(char* stringToParse)
{
    int isIdentifierStarted = 0, isBraceOpened = 0, isBraceClosed = 0, isArgumentStarted = 0;
    unsigned int parametersCount = 0;
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
                if (isBraceOpened == 1)
                {
                    if (isArgumentStarted == 0)
                    {
                        isArgumentStarted = 1;
                    }
                }
                else
                {
                    pushSymbol(*stringToParse, &identifier);
                }
            }
            else if (*stringToParse == '(')
            {
                if (isBraceOpened == 0)
                    isBraceOpened = 1;
                else
                {
                    printf("Error: there should be no nested braces");
                    break;
                }
            }
            else if (*stringToParse == ',')
            {
                if (isBraceOpened && isArgumentStarted)
                {
                    parametersCount++;
                    isArgumentStarted = 0;
                }
                else
                {
                    printf("Error: invalid syntax");
                    break;
                }
            }
            else if (*stringToParse == ')')
            {
                if (isBraceOpened == 0)
                {
                    printf("Error: invalid syntax");
                    break;
                }
            }
        }
        stringToParse++;
    }
    free(identifier.text);
}
#include "io.h"

#include "utilities/DynamicString.h"


char *getInput(FILE* stream)
{
    int line = 1;
    printf("Enter your python code here. Escape character is Ctrl+D for Linux, Ctrl+Z and Enter for Windows\n%d>> ", line);
    int a = 0;
    DynamicString str = {0};
    while ((a = getc(stream)) != EOF)
    {
        pushSymbol(a, &str);
        if (a == '\n')
        {
            line++;
            printf("%d>> ", line);
        }
    }
    return str.text;
}

void printEntries(LinesList_t* head)
{
    printf("lines: ");
    while (head != NULL)
    {
        printf("%d, ", head->lineNumber);
        head = head->next;
    }
    printf("\b\b  \n");
}

void printDescriptors(DescriptorsList_t *head)
{
    while (head != NULL)
    {
        printf("\nfunction name: %s\narguments: %d\n", head->descriptor.name, head->descriptor.parametersCount);
        printEntries(head->descriptor.linesList);
        head = head->next;
    }  
}
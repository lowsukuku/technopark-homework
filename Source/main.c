#include <stdio.h>
//#include "buffer.h"
#include "parser.h"
#include "utilities/DynamicString.h"
int main()
{
    printf("Enter your python code here. Escape character is Ctrl+D for Linux, Ctrl+Z and Enter for Windows\n>> ");
    int a = 0;
    DynamicString str = {0};
    while ((a = getchar()) != EOF)
    {
        pushSymbol(a, &str);
        if (a == '\n')
        {
            pushSymbol(0, &str);
            parse(str.text);
            printf(">> ");
        }
    }

    return 0;
}


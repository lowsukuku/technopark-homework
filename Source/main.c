#include <stdio.h>
//#include "buffer.h"
#include "parser.h"
#include "utilities/DynamicString.h"
int main()
{
    int line = 1;
    printf("Enter your python code here. Escape character is Ctrl+D for Linux, Ctrl+Z and Enter for Windows\n%d>> ", line);
    int a = 0;
    DynamicString str = {0};
    while ((a = getchar()) != EOF)
    {
        pushSymbol(a, &str);
        if (a == '\n')
        {
            line++;
            printf("%d>> ", line);
        }
    }
    line = 1;
    getDescriptor(str.text, NULL, &line);
    return 0;
}


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
            pushSymbol(0, &str);
            if (parse(line, str.text, str.size) == 0)
            {
                clearString(&str);
            }
            line++;
            printf("%d>> ", line);
        }
    }

    return 0;
}


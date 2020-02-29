#include <stdio.h>

int main()
{
    printf("Enter your python code here. Escape character is Ctrl+D for Linux, Ctrl+Z and Enter for Windows\n>> ");
    int a = 0;
    while ((a = getchar()) != EOF)
    {
        if (a == '\n') 
        {
            printf(">> ");
        }
    }
    
    return 0;
}
#include "io.h"
#include "parser.h"
#include <stdio.h>

int main()
{
    char *input = getInput(stdin);
    int line = 1;
    getDescriptors(input, NULL, &line);
    printDescriptors(descriptorsList);
    cleanup(descriptorsList);
    free(input);
    getchar();
    return 0;
}


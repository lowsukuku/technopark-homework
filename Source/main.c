#include "io.h"
#include "parser.h"
#include <stdio.h>

int main()
{
    char *input = getInput();
    getDescriptors(input, NULL, NULL);
    printDescriptors(descriptorsList);
    cleanup(descriptorsList);
    free(input);
    getchar();
    return 0;
}


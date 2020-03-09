#include "io.h"
#include "parser.h"
#include <stdio.h>

int main()
{
    char *input = getInput(stdin);
    int line = 1;
    DescriptorsList_t* list = NULL;
    getDescriptors(input, NULL, &line, &list);
    printDescriptors(list, stdout);
    cleanup(list);
    free(input);
    getchar();
    return 0;
}


#include "../Source/io.h"
#include "../Source/parser.h"
#include <stdio.h>

int main()
{
    FILE *file = fopen("../tests/testscript.py","r");
    if (file != NULL)
    {
    fseek(file , 0 , SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    char *input = malloc(fileSize);
    fread(input, 1, fileSize, file);
    int line = 1;
    getDescriptors(input, NULL, &line);
    printDescriptors(descriptorsList);
    cleanup(descriptorsList);
    free(input);
    }
    fclose(file);
    return 0;
}

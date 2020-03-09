extern "C"
{
#include "../Source/io.h"
#include "../Source/parser.h"
}
#include <stdio.h>
#include <gtest/gtest.h>

TEST(test, test1)
{
    FILE *file = fopen("../tests/testscript.py", "r");
    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        size_t fileSize = ftell(file);
        rewind(file);
        char* input = (char *)calloc(fileSize + 1, 1);
        if (input != NULL)
        {
            fread(input, 1, fileSize, file);
            int line = 1;
            getDescriptors(input, NULL, &line);
            printDescriptors(descriptorsList);
            cleanup(descriptorsList);
            free(input);
        }
    }
    fclose(file);
}

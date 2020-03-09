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

TEST(test, stringResizeTest)
{
    DynamicString testString = {0};
    char testMessage[] = "This message should trigger dynamic string resize operation";
    char *messagePointer = testMessage; 
    while(*messagePointer)
    {
        pushSymbol(*messagePointer, &testString);
        messagePointer++;
    }
    ASSERT_STREQ(testString.text, testMessage);
    ASSERT_GT(testString.size, 50);
    ASSERT_EQ(testString.tailPosition, strlen(testMessage));
    free(testString.text);
}

TEST(test, nullDescriptorsListTest)
{
    FunctionDescriptor_t testDescriptor = {(char *)"test",0,0};
    DescriptorsList_t* testList = addDescriptor(testDescriptor, NULL);
    ASSERT_TRUE(testList != NULL);
    ASSERT_STREQ(testList->descriptor.name, testDescriptor.name);
    free(testList);
}

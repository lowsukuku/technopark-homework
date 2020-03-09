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
        char *input = getInput(file);
        int line = 1;
        DescriptorsList_t* list = NULL;
        getDescriptors(input, NULL, &line, &list);
        printDescriptors(list, stdout);
        cleanup(list);
        free(input);
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

TEST(pytests, t1)
{
    FILE *outFile = fopen("testOutput", "w+");
    FILE *inFile = fopen("../tests/reference.py", "r");
    char *input = getInput(inFile);
    int line = 1;
    DescriptorsList_t *list = NULL;
    getDescriptors(input, NULL, &line, &list);
    printDescriptors(list, outFile);
    cleanup(list);
    fclose(outFile);
    fclose(inFile);
    free(input);
    outFile = fopen("testOutput", "r");
    fseek(outFile, 0, SEEK_END);
    size_t fSize = ftell(outFile);
    rewind(outFile);
    char *output = (char *)calloc(fSize + 1, sizeof(char));
    fread(output, 1, fSize, outFile);
    FILE *refFile = fopen("../tests/referenceOutput.txt", "r");
    fseek(refFile, 0, SEEK_END);
    fSize = ftell(refFile);
    rewind(refFile);
    char *refOut = (char *)calloc(fSize + 1, sizeof(char));
    fread(refOut, 1, fSize, refFile);
    ASSERT_STREQ(output, refOut);
    fclose(outFile);
    fclose(refFile);
    free(output);
    free(refOut);
}

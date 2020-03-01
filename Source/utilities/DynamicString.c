#include "DynamicString.h"

#define INITIAL_STRING_SIZE 50

static int resizeString(DynamicString *target);
static int initializeString(DynamicString *target);

int initializeString(DynamicString *target)
{
    if (target == NULL)
        return -1;

    if (target->text == NULL)
    {
        target->text = malloc(INITIAL_STRING_SIZE);
        if (target->text == NULL)
            return -1;
        target->size = INITIAL_STRING_SIZE;
    }
    return 0;
}

int pushSymbol(char symbol, DynamicString* target)
{
    if (target == NULL)
        return -1;
    if (target->text == NULL)
    {
        if (initializeString(target) == -1)
            return -1;
    }
    if (target->tailPosition == target->size)
    {
        if (resizeString(target) == -1)
            return -1;
    }
    target->text[target->tailPosition++] = symbol;
    return 0;
}

int resizeString(DynamicString *target)
{
    if (target == NULL)
        return -1;
    if (target->text == NULL)
    {
        if (initializeString(target) == -1)
            return -1;
    }
    size_t newSize = target->size * 2;
    void *allocator = realloc(target->text, newSize);
    if (allocator == NULL)
        return -1;
    target->size = newSize;
    target->text = allocator;
    return 0;
}

int clearString(DynamicString *target)
{
    if (target == NULL)
        return -1;
    if (target->text == NULL)
    {
        return -1;
    }
    target->tailPosition = 0;
    return 0;
}
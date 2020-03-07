#include "functionDescriptor.h"
#include <stdlib.h>
#include <string.h>

DescriptorsList_t* addDescriptor(FunctionDescriptor_t descriptor, DescriptorsList_t* head)
{
    if (head == NULL)
    {
        head = malloc(sizeof(DescriptorsList_t));
        head->descriptor = descriptor;
        head->next = NULL;
        return head;
    }
    DescriptorsList_t *node = head;
    while (node->next != NULL)
    {
        node = node->next;
    }
    node->next = malloc(sizeof(DescriptorsList_t));
    if (node->next == NULL)
        return NULL;
    node = node->next;
    node->descriptor = descriptor;
    node->next = NULL;
    return node;
}

DescriptorsList_t* findDescriptor(char* name, DescriptorsList_t* head)
{
    if (head == NULL)
        return NULL;
    DescriptorsList_t *node = head;
    while (node != NULL)
    {
        if (node->descriptor.name != NULL)
        {
            if (strcmp(node->descriptor.name, name) == 0)
                return node;
        }
        node = node->next;
    }
    return NULL;
}

int addEntry(int line, DescriptorsList_t *node)
{
    if (node == NULL)
        return -1;
    if (node->descriptor.linesList == NULL)
    {
        void *allocator = malloc(sizeof(LinesList_t));
        if (allocator == NULL)
            return -1;
        node->descriptor.linesList = allocator;
        node->descriptor.linesList->lineNumber = line;
        node->descriptor.linesList->next = NULL;
        return 0;
    }
    LinesList_t *listNode = node->descriptor.linesList;
    while (listNode->next != NULL)
    {
        listNode = listNode->next;
    }
    listNode->next = malloc(sizeof(LinesList_t));
    if (listNode->next == NULL)
        return -1;
    listNode = listNode->next;
    listNode->lineNumber = line;
    listNode->next = NULL;
    return 0;
}
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
    while (node != NULL)
    {
        node = node->next;
    }
    node = malloc(sizeof(DescriptorsList_t));
    node->descriptor = descriptor;
    node->next = NULL;
    return head;
}

DescriptorsList_t* findDescriptor(char* name, DescriptorsList_t* head)
{
    if (head == NULL)
        return NULL;
    DescriptorsList_t *node = head;
    while (node != NULL)
    {
        if (strcmp(node->descriptor.name, name) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}
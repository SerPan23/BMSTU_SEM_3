#ifndef STACK_LIST
#define STACK_LIST

#include "defines.h"

typedef struct list_node
{
    char value;
    struct list_node *prev_el;
} list_node_t;

typedef struct stack_list
{
    list_node_t *ptr;
    size_t size;
} stack_list_t;

int stack_list_pop(stack_list_t *list);
int stack_list_push(stack_list_t *list, char value);
void stack_list_print(stack_list_t *list);

#endif

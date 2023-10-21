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
    void **free_area;
    size_t free_area_size;
    size_t free_area_size_alloc;
} stack_list_t;

int stack_list_pop(stack_list_t *list);
int stack_list_push(stack_list_t *list, char value);
void stack_list_print(stack_list_t *list);
void stack_list_free(stack_list_t *stack);
int init_free_area(stack_list_t *stack, size_t size);
int add_free_area(stack_list_t *stack, void *ptr);

#endif

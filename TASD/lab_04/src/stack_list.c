#include "stack_list.h"

int stack_list_pop(stack_list_t *stack)
{
    if (stack->ptr == NULL)
        return ERROR_EMPTY_STACK;

    list_node_t *tmp = stack->ptr;
    stack->ptr = tmp->prev_el;
    --stack->size;

    free(tmp);
    return EXIT_SUCCESS;
}

int stack_list_push(stack_list_t *stack, char value)
{
    if (stack->size + 1 > MAX_STACK_LEN)
        return ERROR_STACK_OVERFLOW;
    
    list_node_t *new = NULL;
    new = malloc(sizeof(list_node_t));
    if (!new)
        return ERROR_MEMORY;

    new->value = value;
    new->prev_el = stack->ptr;
    stack->ptr = new;
    ++stack->size;
    return EXIT_SUCCESS;
}

void stack_list_print(stack_list_t *stack)
{
    list_node_t *el = stack->ptr;
    if (el == NULL)
        printf("Stack is empty.\n");

    for (; el != NULL; el = el->prev_el)
        printf("%c (%p)\n", el->value, (void *) el);
}

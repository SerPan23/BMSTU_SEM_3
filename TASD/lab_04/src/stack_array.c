#include "stack_array.h"

int stack_array_pop(stack_array_t *stack)
{
    if (stack->size == 0)
        return ERROR_EMPTY_STACK;

    stack->size--;
    
    return EXIT_SUCCESS;
}

int stack_array_push(stack_array_t *stack, char value)
{
    if (stack->size + 1 > MAX_STACK_LEN)
        return ERROR_STACK_OVERFLOW;
    stack->data[stack->size++] = value;
    return EXIT_SUCCESS;
}

void stack_array_print(stack_array_t *stack)
{
    if (stack->size == 0)
        printf("Stack is empty.\n");
    
    for (ptrdiff_t i = stack->size - 1; i >= 0; i--)
        printf("%c\n", stack->data[i]);
}

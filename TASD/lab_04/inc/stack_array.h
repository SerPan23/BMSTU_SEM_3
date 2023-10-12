#ifndef STACK_ARRAY
#define STACK_ARRAY

#include "defines.h"

typedef struct stack_array
{
    char *data;
    size_t size;
} stack_array_t;

int stack_array_pop(stack_array_t *array);
int stack_array_push(stack_array_t *array, char value);
void stack_array_print(stack_array_t *array);

#endif

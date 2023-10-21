#include "stack_list.h"

int stack_list_pop(stack_list_t *stack)
{
    if (stack->size == 0)
        return ERROR_EMPTY_STACK;

    list_node_t *tmp = stack->ptr;
    stack->ptr = tmp->prev_el;
    --stack->size;

    if (stack->free_area_size_alloc)
        add_free_area(stack, tmp);

    free(tmp);
    return EXIT_SUCCESS;
}

int stack_list_push(stack_list_t *stack, char value)
{
    // printf("%zu %zu (%d)\n", stack->size, stack->size + 1, MAX_STACK_LEN);
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

    printf("\nFree area:\n");
    if (stack->free_area_size == 0)
        printf("No free areas.\n");
    else
    {
        for (size_t i = 0; i < stack->free_area_size; i++)
            printf("%p\n", stack->free_area[i]);
    }
}

void stack_list_free(stack_list_t *stack)
{
    while (stack->ptr)
    {
        int rc = stack_list_pop(stack);
        if (rc != EXIT_SUCCESS)
            break;
    }
    if (stack->free_area_size_alloc)
        free(stack->free_area);
    stack->free_area_size = 0;
    stack->free_area_size_alloc = 0;
}

int init_free_area(stack_list_t *stack, size_t size)
{
    void *ptmp = NULL;
    ptmp = realloc(ptmp, size * sizeof(void *));
    if (!ptmp)
        return ERROR_MEMORY;
    stack->free_area = ptmp;
    stack->free_area_size = 0;
    stack->free_area_size_alloc = size;
    return EXIT_SUCCESS;
}

int add_free_area(stack_list_t *stack, void *ptr)
{
    int rc = EXIT_SUCCESS;
    if (stack->free_area_size + 1 > stack->free_area_size_alloc)
        rc = init_free_area(stack, stack->free_area_size_alloc + MAX_STACK_LEN);

    if (rc != EXIT_SUCCESS)
        return rc;

    stack->free_area[stack->free_area_size++] = ptr;
    return rc;
}

// #include "menu.h"
#include "stack_list.h"
#include "stack_array.h"

char stack_array_data[MAX_STACK_LEN];

int main(void)
{
    // int rc = menu();
    // return rc;

    stack_list_t stack_list;
    stack_list.ptr = NULL;
    stack_list.size = 0;

    stack_array_t stack_array;
    stack_array.data = stack_array_data;
    stack_array.size = 0;

    // STACK BY LIST
    printf("\nSTACK BY ARRAY\n");
    stack_list_push(&stack_list, '(');
    stack_list_push(&stack_list, '*');
    stack_list_push(&stack_list, ')');

    stack_list_push(&stack_list, '(');

    stack_list_print(&stack_list);
    printf("\n");

    stack_list_pop(&stack_list);

    stack_list_print(&stack_list);

    // STACK BY ARRAY
    printf("\nSTACK BY ARRAY\n");

    stack_array_push(&stack_array, '[');
    stack_array_push(&stack_array, '8');
    stack_array_push(&stack_array, ']');

    stack_array_push(&stack_array, '[');

    stack_array_print(&stack_array);
    printf("\n");

    stack_array_pop(&stack_array);

    stack_array_print(&stack_array);

    return 0;
}

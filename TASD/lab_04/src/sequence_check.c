#include "sequence_check.h"

int is_bracket_seq(char *str, size_t len, int stack_type_list, stack_list_t *stack_list, stack_array_t *stack_array, int is_need_max_size, size_t *max_stack_size)
{
    // stack_list_t stack;
    // stack.ptr = NULL;
    // stack.size = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (is_need_max_size)
        {
            if (stack_type_list)
            {
                if (*max_stack_size < stack_list->size)
                    *max_stack_size = stack_list->size;
            }
            else 
            {
                if (*max_stack_size < stack_array->size)
                    *max_stack_size = stack_array->size;
            }
        }

        char el = str[i];
        if (el == '(' || el == '[' || el == '{')
        {
            if (stack_type_list)
                stack_list_push(stack_list, el);
            else
                stack_array_push(stack_array, el);
        }
        else if (el == ')' || el == ']' || el == '}')
        {
            char st_el;
            if (stack_type_list)
            {
                if (!stack_list->ptr)
                    return 0;
                st_el = stack_list->ptr->value;
            }
            else
            {
                if (stack_array->size == 0)
                    return 0;
                st_el = stack_array->data[stack_array->size - 1];
            }

            if ((el == ')' && st_el == '(') ||
                (el == ']' && st_el == '[') ||
                (el == '}' && st_el == '{'))
            {
                if (stack_type_list)
                    stack_list_pop(stack_list);
                else
                    stack_array_pop(stack_array);
            }
            else
                return 0;
        }
    }
    if (stack_type_list)
    {
        if (stack_list->size != 0)
            return 0;
    }
    else
    {
        if (stack_array->size != 0)
            return 0;
    }
    return 1;
}

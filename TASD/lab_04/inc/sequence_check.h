#ifndef SEQUENCE_CHECK_H
#define FUNCS_H

#include "stack_array.h"
#include "stack_list.h"

int is_bracket_seq(char *str, size_t len, int stack_type_list, stack_list_t *stack_list, stack_array_t *stack_array, int is_need_max_size, size_t *max_stack_size);

#endif

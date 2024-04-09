#ifndef CHECK_FUNCS_H
#define CHECK_FUNCS_H

#include <stdlib.h>
#include <check.h>
#include "my_list.h"

Suite *list_find_suite(void);
Suite *list_pop_front_suite(void);
Suite *list_pop_back_suite(void);
Suite *list_append_suite(void);
Suite *list_remove_dupl_suite(void);
Suite *list_sort_suite(void);

#endif

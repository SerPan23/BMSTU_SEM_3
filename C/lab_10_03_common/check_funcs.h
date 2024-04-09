#ifndef CHECK_FUNCS_H
#define CHECK_FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "associative_array.h"

Suite *insert_suite(void);
Suite *find_suite(void);
Suite *remove_suite(void);
Suite *clear_suite(void);
Suite *each_suite(void);
Suite *min_suite(void);
Suite *max_suite(void);

#endif

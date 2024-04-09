#ifndef CHECK_FUNCS_H
#define CHECK_FUNCS_H

#include <stdlib.h>
#include <check.h>
#include "my_matrix.h"

Suite *matrix_mul_suite(void);
Suite *matrix_pow_suite(void);
Suite *matrix_to_new_size_suite(void);
Suite *matrix_to_square_form_suite(void);

#endif

#ifndef CHECK_FUNCS_H
#define CHECK_FUNCS_H

#include <stdlib.h>
#include <check.h>
#include "polynomial.h"

Suite *p_val_suite(void);
Suite *p_ddx_suite(void);
Suite *p_sum_suite(void);
Suite *p_dvd_suite(void);

#endif
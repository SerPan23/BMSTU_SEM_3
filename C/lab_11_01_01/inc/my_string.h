#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_INT_LEN 15

#define ERROR_WRONG_STR_LEN 1
#define ERROR_PARSE_ARG 2

int int_to_str(int num, int base, char *str, size_t *len, size_t max_len);

int parse_arg(const char *restrict format, size_t *ind, char *buf, size_t *len, size_t max_len, va_list args);

size_t my_strlen(const char *s);

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...);

#endif
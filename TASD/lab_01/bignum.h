#ifndef BIGNUM_H
#define BIGNUM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <math.h>

#define ERROR_MANTISSA_LEN 1
#define ERROR_EXPONET_SIZE 2
#define ERROR_INVALID_SYMBOL 3
#define ERROR_EMPTY_INPUT 4
#define ERROR_NUM_LEN 5

#define MAX_STR_LEN 100
#define MAX_MANTISSA_LEN 40

typedef struct
{
    int is_negative;
    int mantissa[MAX_MANTISSA_LEN];
    size_t mantissa_len;
    int32_t exponet;
} bignum_t;

// convert string to bignum
int str_to_bignum(char s[], size_t len, bignum_t *a);

// convert bignum to string
int bignum_to_str(char s[], size_t *len, bignum_t *a);

// printing bignum in console
int bignum_print(bignum_t *a);

// scan bignum from console
int bignum_scan(bignum_t *a);

// multiple two bignums
int bignum_mul(bignum_t *a, bignum_t *b, bignum_t *result);

#endif
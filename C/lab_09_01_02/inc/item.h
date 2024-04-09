#ifndef ITEM_H
#define ITEM_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_WRONG_INPUT 1
#define ERROR_EMPTY_INPUT 2
#define ERROR_EMPTY_PRINT 3
#define ERROR_INCORRECT_NUM_VALUE 4
#define ERROR_STR_ALLOC 5
#define ERROR_MEM_ALLOC 6

#define MAX_NAME_LEN 25
#define MAX_ITEMS 15

#define EPS 1e-8

typedef struct
{
    char *name;
    size_t name_len;
    double weight;
    double volume;
} item_t;

int item_create(item_t **item);
void item_free(item_t *item);
int item_fill(item_t **item, char *s, double *weight, double *volume);
int item_scan(FILE *f, item_t **item);
void item_print(item_t *item);
int item_cmp_by_density(item_t *i1, item_t *i2);

#endif

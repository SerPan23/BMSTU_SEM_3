#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_MEM_ALLOC 1
#define ERROR_MEM_REALLOC 2
#define ERROR_INVALID_SIZE 3
#define ERROR_INVALID_NUM 4


typedef struct array
{
    int *data;
    size_t size;
    size_t size_alloc;
} array_t;

int array_alloc(array_t *arr, size_t size);
void array_free(array_t *arr);
int array_realoc(array_t *arr, size_t size);
int array_fill(array_t *arr);
void array_print(array_t *arr);

int del_nums_dels_on_3(array_t *arr);

#endif
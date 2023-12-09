#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include "defines.h"
#include "useful_funcs.h"

#define CAPACITY_SIZE 10

typedef struct dynamic_array
{
    void **data;
    size_t size;
    size_t size_alloc;
} dynamic_array_t;

int dynamic_arr_init(dynamic_array_t *arr);
int dynamic_arr_destroy(dynamic_array_t *arr);

int dynamic_arr_push(dynamic_array_t *arr, void *data);
int dynamic_arr_pop(dynamic_array_t *arr, void **data);

#endif

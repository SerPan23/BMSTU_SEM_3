#include "dynamic_array.h"

int dynamic_arr_init(dynamic_array_t *arr)
{   
    arr->data = malloc(CAPACITY_SIZE * sizeof(void *));
    if (!arr->data)
        return ERROR_MEMMORY_ALLOC;

    arr->size = 0;
    arr->size_alloc = CAPACITY_SIZE;
    
    return EXIT_SUCCESS;
}

int dynamic_arr_destroy(dynamic_array_t *arr)
{
    free(arr->data);
    arr = NULL;
    return EXIT_SUCCESS;
}

int dynamic_arr_realloc(dynamic_array_t *arr)
{
    void *tmp = realloc(arr->data, (arr->size_alloc + CAPACITY_SIZE) * sizeof(void *));
    if (!tmp)
        return ERROR_MEMMORY_ALLOC;

    arr->data = tmp;
    arr->size_alloc += CAPACITY_SIZE;
    return EXIT_SUCCESS;
}

int dynamic_arr_push(dynamic_array_t *arr, void *data)
{
    int rc;
    if (arr->size + 1 > arr->size_alloc)
    {
        rc = dynamic_arr_realloc(arr);
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    arr->data[arr->size++] = data;

    return EXIT_SUCCESS;
}

int dynamic_arr_pop(dynamic_array_t *arr, void **data)
{
    if (arr->size == 0)
        *data = NULL;

    *data = arr->data[arr->size - 1];

    arr->size--;

    return EXIT_SUCCESS;
}

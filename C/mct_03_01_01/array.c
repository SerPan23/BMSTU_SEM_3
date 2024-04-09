#include "array.h"

int array_alloc(array_t *arr, size_t size)
{
    void *ptmp;
    ptmp = calloc(size, sizeof(int));
    if (!ptmp)
        return ERROR_MEM_ALLOC;
    
    arr->data = ptmp;
    arr->size = size;
    arr->size_alloc = size;

    return EXIT_SUCCESS;
}

void array_free(array_t *arr)
{
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->size_alloc = 0;
}

int array_realoc(array_t *arr, size_t new_size)
{
    void *ptmp;
    ptmp = realloc(arr->data, new_size * sizeof(int));
    if (!ptmp)
        return ERROR_MEM_REALLOC;
    
    arr->data = ptmp;
    arr->size_alloc = new_size;

    return EXIT_SUCCESS;
}

int array_fill(array_t *arr)
{
    for (size_t i = 0; i < arr->size; i++)
        if (scanf("%d", &arr->data[i]) != 1)
            return ERROR_INVALID_NUM;

    return EXIT_SUCCESS;
}

void array_print(array_t *arr)
{
    for (size_t i = 0; i < arr->size; i++)
        printf("%d ", arr->data[i]);
}

int del_nums_dels_on_3(array_t *arr)
{
    size_t count = 0;
    for (size_t i = 0; i < arr->size; i++)
    {
        if (arr->data[i] % 3 == 0)
            count++;
        else
        {
            arr->data[i - count] = arr->data[i];
        }
    }
    arr->size -= count;

    int rc = array_realoc(arr, arr->size);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}

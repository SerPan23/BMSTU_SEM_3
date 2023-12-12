#include "my_vector.h"

int vector_init(vector_t **vec, int n)
{
    *vec = malloc(sizeof(vector_t));
    if (!(*vec))
        return ERROR_MEMMORY_ALLOC;

    (*vec)->data = calloc(n, sizeof(int));
    if (!(*vec)->data)
        return ERROR_MEMMORY_ALLOC;

    (*vec)->size = 0;
    (*vec)->size_alloc = n;

    return EXIT_SUCCESS;
}

void vector_free(vector_t **vec)
{
    free((*vec)->data);
    free(*vec);
    vec = NULL;
}

int vector_push(vector_t *vec, int el)
{
    if (vec->size + 1 > vec->size_alloc)
    {
        size_t new_size = vec->size_alloc + 1 + (vec->size_alloc / 10);
        void *ptmp = realloc(vec->data, new_size);
        if (!ptmp)
            return ERROR_MEMMORY_ALLOC;
        vec->data = ptmp;
    }

    vec->data[vec->size++] = el;

    return EXIT_SUCCESS;
}

int vector_pop(vector_t *vec, int *el)
{
    if (vec->size - 1 < 0)
        return ERROR_EMPTY_VECTOR;

    *el = vec->data[--vec->size];

    return EXIT_SUCCESS;
}

void vector_print(vector_t *vec, char sep, char end)
{
    for (int i = 0; i < vec->size; i++)
    {
        printf("%d", vec->data[i]);
        if (i < vec->size - 1)
            printf("%c", sep);
    }
    printf("%c", end);
}

void vector_reverse(vector_t *vec)
{
    for (int i = 0; i < vec->size / 2; i++)
    {
        int tmp = vec->data[i];
        vec->data[i] = vec->data[vec->size - 1 - i];
        vec->data[vec->size - 1 - i] = tmp;
    }
}

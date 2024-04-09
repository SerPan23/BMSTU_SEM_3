#include "associative_array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node
{
    const char *key;
    int value;
} node_t;

void node_free(node_t **node)
{
    free(*node);
    *node = NULL;
}

struct assoc_array_type
{
    node_t **data;
    size_t size;
    size_t size_alloc;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t assoc_array = NULL;

    assoc_array = malloc(sizeof(struct assoc_array_type));
    if (!assoc_array)
        return NULL;

    assoc_array->data = malloc(1 * sizeof(node_t *));
    if (!assoc_array->data)
    {
        free(assoc_array);
        return NULL;
    }

    assoc_array->size = 0;
    assoc_array->size_alloc = 1;
    return assoc_array;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr)
        return;

    if (!(*arr))
        return;

    for (size_t i = 0; i < (*arr)->size; i++)
        node_free(&(*arr)->data[i]);

    free((*arr)->data);

    (*arr)->size = 0;
    (*arr)->size_alloc = 0;
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
        if (strcmp(arr->data[i]->key, key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;

    if (arr->size + 1 > arr->size_alloc)
    {
        size_t new_size = arr->size_alloc + arr->size_alloc / 10 + 1;
        void *tmp = realloc(arr->data, new_size * sizeof(node_t *));
        if (!tmp)
            return ASSOC_ARRAY_MEM;
        arr->data = tmp;
        arr->size_alloc = new_size;
    }

    node_t *new_node = NULL;
    new_node = malloc(sizeof(node_t));
    if (!new_node)
        return ASSOC_ARRAY_MEM;

    new_node->key = key;
    new_node->value = num;

    arr->data[arr->size++] = new_node;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
        if (strcmp(arr->data[i]->key, key) == 0)
        {
            *num = &arr->data[i]->value;
            return ASSOC_ARRAY_OK;
        }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    int flag = 0;
    for (size_t i = 0; i < arr->size; i++)
    {
        if (!flag && (strcmp(arr->data[i]->key, key) == 0))
        {
            flag = 1;
            node_free(&arr->data[i]);
            arr->data[i] = NULL;
        }
        else if (flag)
        {
            arr->data[i - 1] = arr->data[i];
            arr->data[i] = NULL;
        }
    }
    if (flag)
    {
        arr->data[arr->size - 1] = NULL;
        arr->size--;
        return ASSOC_ARRAY_OK;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
        node_free(&arr->data[i]);

    arr->size = 0;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!action)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
        action(arr->data[i]->key, &arr->data[i]->value, param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    size_t min_key_id = 0;

    for (size_t i = 0; i < arr->size; i++)
        if (strcmp(arr->data[i]->key, arr->data[min_key_id]->key) < 0)
            min_key_id = i;

    *num = &arr->data[min_key_id]->value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    size_t max_key_id = 0;

    for (size_t i = 0; i < arr->size; i++)
        if (strcmp(arr->data[i]->key, arr->data[max_key_id]->key) > 0)
            max_key_id = i;

    *num = &arr->data[max_key_id]->value;

    return ASSOC_ARRAY_OK;
}

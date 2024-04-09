#include "associative_array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node node_t;

struct node
{
    const char *key;
    int value;
    node_t *next;
};

void node_free(node_t **node)
{
    free(*node);
    *node = NULL;
}

struct assoc_array_type
{
    node_t *head;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t assoc_array = NULL;

    assoc_array = malloc(sizeof(struct assoc_array_type));
    if (!assoc_array)
        return NULL;

    assoc_array->head = NULL;

    return assoc_array;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr)
        return;

    if (!(*arr))
        return;

    node_t *next = NULL;

    for (; (*arr)->head != NULL; (*arr)->head = next)
    {
        next = (*arr)->head->next;
        node_free(&(*arr)->head);
    }

    (*arr)->head = NULL;
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *cur = NULL;
    node_t *tail = NULL;
    for (cur = arr->head; cur != NULL; cur = cur->next)
    {
        if (strcmp(cur->key, key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;
        tail = cur;
    }

    node_t *new_node = calloc(1, sizeof(node_t));
    if (!new_node)
        return ASSOC_ARRAY_MEM;

    new_node->key = key;
    new_node->value = num;
    new_node->next = NULL;

    if (arr->head != NULL)
        tail->next = new_node;
    else
        arr->head = new_node;

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

    for (node_t *cur = arr->head; cur != NULL; cur = cur->next)
    {
        if (strcmp(cur->key, key) == 0)
        {
            *num = &cur->value;
            return ASSOC_ARRAY_OK;
        }
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->head == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *prev = NULL;
    for (node_t *cur = arr->head; cur != NULL; cur = cur->next)
    {
        if (strcmp(cur->key, key) == 0)
        {
            if (prev)
            {
                prev->next = cur->next;
                node_free(&cur);
                // cur = prev;
                return ASSOC_ARRAY_OK;
            }
            else
            {
                prev = cur->next;
                node_free(&cur);
                arr->head = prev;
                // cur = prev;
                return ASSOC_ARRAY_OK;
            }
        }
        prev = cur;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *next = NULL;

    for (; arr->head != NULL; arr->head = next)
    {
        next = arr->head->next;
        node_free(&arr->head);
    }

    arr->head = NULL;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!action)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (node_t *cur = arr->head; cur != NULL; cur = cur->next)
    {
        action(cur->key, &cur->value, param);
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->head == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *min_node = arr->head;

    for (node_t *cur = arr->head; cur != NULL; cur = cur->next)
    {
        if (strcmp(cur->key, min_node->key) < 0)
        {
            min_node = cur;
        }
    }

    *num = &min_node->value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->head == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *max_node = arr->head;

    for (node_t *cur = arr->head; cur != NULL; cur = cur->next)
    {
        if (strcmp(cur->key, max_node->key) > 0)
        {
            max_node = cur;
        }
    }

    *num = &max_node->value;

    return ASSOC_ARRAY_OK;
}

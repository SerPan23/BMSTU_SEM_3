#ifndef ITEMS_H
#define ITEMS_H

#include "item.h"

#define CAPACITY_PER_BY_SIZE 10

#define ERROR_MEMORY_ALLOC 10
#define ERROR_MEMORY_REALLOC 11
#define ERROR_EMPTY_ARR 12
#define ERROR_INVALID_INDEX 13

#define ERROR_WRONG_FILEPATH 100
#define ERROR_EMPTY_FILE 101

typedef struct items
{
    item_t **data;
    size_t size;
    size_t size_alloc;
} items_t;

int items_alloc(items_t *items, size_t size);
void items_free(items_t *items);
int items_realloc(items_t *items, size_t new_size);
int items_append(items_t *items, item_t *item);


int sort_by_density(items_t *items);
int read_items(char *filepath, items_t *items);
int sort_and_print(char *filepath, int (*sort)(items_t *));
int print_all(char *filepath);
int print_substr_start(char *filepath, char *substr);

#endif

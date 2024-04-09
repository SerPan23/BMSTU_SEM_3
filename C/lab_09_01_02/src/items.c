#include "items.h"

int items_alloc(items_t *items, size_t size)
{
    items->data = calloc(size, sizeof(item_t *));
    if (!items->data)
        return ERROR_MEMORY_ALLOC;
    
    items->size = 0;
    items->size_alloc = size;

    return EXIT_SUCCESS;
}

void items_free(items_t *items)
{
    if (items->size_alloc != 0)
    {
        for (size_t i = 0; i < items->size; i++)
            item_free(items->data[i]);
        free(items->data);
    }
    items->data = NULL;
    items->size_alloc = 0;
}

int items_realloc(items_t *items, size_t new_size)
{
    void *ptmp;
    ptmp = realloc(items->data, new_size * sizeof(item_t *));
    if (!ptmp)
        return ERROR_MEMORY_REALLOC;

    items->data = ptmp;
    items->size_alloc = new_size;
    return EXIT_SUCCESS;
}

int items_append(items_t *items, item_t *item)
{
    int rc = EXIT_SUCCESS;
    if (items->size + 1 > items->size_alloc)
    {
        rc = items_realloc(items, items->size_alloc + 1 + items->size_alloc * (CAPACITY_PER_BY_SIZE / 100));
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    items->data[items->size++] = item;

    return EXIT_SUCCESS;
}

int items_pop_by_id(items_t *items, size_t ind)
{
    if (items->size == 0)
        return ERROR_EMPTY_ARR;

    if (ind >= items->size)
        return ERROR_INVALID_INDEX;

    item_free(items->data[ind]);
    for (size_t i = ind + 1; i < items->size; i++)
        items->data[i - 1] = items->data[i];
    items->size--;
    return EXIT_SUCCESS;
}

int read_items(char *filepath, items_t *items)
{
    FILE *f;
    f = fopen(filepath, "r");
    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    item_t *tmp = NULL;
    // item_create(&tmp);
    int rc;
    while ((rc = item_scan(f, &tmp)) == EXIT_SUCCESS)
    {
        rc = items_append(items, tmp);
        if (rc != EXIT_SUCCESS)
        {
            item_free(tmp);
            fclose(f);
            return rc;
        }
        tmp = NULL;
    }
    // printf("%d\n", rc);
    // item_print(&tmp);
    // item_free(&tmp);
    if (items->size == 0)
    {
        fclose(f);
        return ERROR_EMPTY_FILE;
    }
    if (rc != ERROR_EMPTY_INPUT && rc != EXIT_SUCCESS)
    {
        fclose(f);
        return rc;
    }
    fclose(f);
    return EXIT_SUCCESS;
}

int sort_by_density(items_t *items)
{
    for (size_t i = 0; i < items->size; i++)
        for (size_t j = 0; j < items->size - 1 - i; j++)
        {
            if (item_cmp_by_density(items->data[j], items->data[j + 1]) > 0)
            {
                void *tmp = items->data[j];
                items->data[j] = items->data[j + 1];
                items->data[j + 1] = tmp;
            }
        }
    return EXIT_SUCCESS;
}

int sort_and_print(char *filepath, int (*sort)(items_t *))
{
    items_t items = { NULL, 0, 0 };
    items_alloc(&items, 1);
    int rc = read_items(filepath, &items);
    if (rc != EXIT_SUCCESS)
    {
        items_free(&items);
        return rc;
    }

    sort(&items);

    for (size_t i = 0; i < items.size; i++)
        item_print(items.data[i]);

    items_free(&items);

    return EXIT_SUCCESS;
}

int print_all(char *filepath)
{
    items_t items = { NULL, 0, 0 };
    items_alloc(&items, 1);
    int rc = read_items(filepath, &items);
    if (rc != EXIT_SUCCESS)
    {
        items_free(&items);
        return rc;
    }

    for (size_t i = 0; i < items.size; i++)
        item_print(items.data[i]);

    items_free(&items);

    return EXIT_SUCCESS;
}

int print_substr_start(char *filepath, char *substr)
{
    items_t items = { NULL, 0, 0 };
    items_alloc(&items, 1);
    int rc = read_items(filepath, &items);
    if (rc != EXIT_SUCCESS)
    {
        items_free(&items);
        return rc;
    }

    int is_smt_print = 0;
    for (size_t i = 0; i < items.size; i++)
        if (strncmp(substr, items.data[i]->name, strlen(substr)) == 0)
        {
            is_smt_print = 1;
            item_print(items.data[i]);
        }

    items_free(&items);

    if (!is_smt_print)
        return ERROR_EMPTY_PRINT;
    return EXIT_SUCCESS;
}

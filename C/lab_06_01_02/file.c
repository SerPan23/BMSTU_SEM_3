#include "file.h"

int read_items(char *filepath, items_t items, size_t *n)
{
    FILE *f;
    f = fopen(filepath, "r");
    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    *n = 0;
    item_t tmp;
    int rc;
    while ((rc = scan_item(f, &tmp)) == EXIT_SUCCESS)
    {
        if (*n < MAX_ITEMS)
            items[(*n)++] = tmp;
        else
        {
            fclose(f);
            return ERROR_WRONG_ITEMS_COUNT;
        }
    }
    if (*n == 0)
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

int sort_by_density(items_t items, size_t n)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n - 1 - i; j++)
        {
            item_t it1 = items[j];
            item_t it2 = items[j + 1];
            double t1 = it1.weight / it1.volume;
            double t2 = it2.weight / it2.volume;
            if (t1 > t2)
            {
                items[j] = it2;
                items[j + 1] = it1;
            }
        }
    return EXIT_SUCCESS;
}

int sort_and_print(char *filepath)
{
    size_t n = 0;
    items_t items;
    int rc = read_items(filepath, items, &n);
    if (rc != EXIT_SUCCESS)
        return rc;

    sort_by_density(items, n);

    for (size_t i = 0; i < n; i++)
        print_item(items[i]);

    return EXIT_SUCCESS;
}

int print_all(char *filepath)
{
    size_t n = 0;
    items_t items;
    int rc = read_items(filepath, items, &n);
    if (rc != EXIT_SUCCESS)
        return rc;
    
    for (size_t i = 0; i < n; i++)
        print_item(items[i]);

    return EXIT_SUCCESS;
}

int print_substr_start(char *filepath, char *substr)
{
    size_t n = 0;
    items_t items;
    int rc = read_items(filepath, items, &n);
    if (rc != EXIT_SUCCESS)
        return rc;
    
    int is_smt_print = 0;

    for (size_t i = 0; i < n; i++)
        if (strncmp(substr, items[i].name, strlen(substr)) == 0)
        {
            is_smt_print = 1;
            print_item(items[i]);
        }

    if (!is_smt_print)
        return ERROR_EMPTY_PRINT;
    return EXIT_SUCCESS;
}

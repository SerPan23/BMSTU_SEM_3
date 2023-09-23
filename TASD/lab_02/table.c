#include "table.h"

int get_file_size(FILE *input, size_t *rows_count)
{
    rewind(input);
    int rc;
    country_t tmp_country;
    while(!feof(input))
    {
        rc = read_country(&tmp_country, input);
        if (rc != EXIT_SUCCESS)
            return rc;
        ++(*rows_count);
    }
    return EXIT_SUCCESS;
}

int read_table_from_file(table_t *table, FILE *input)
{
    int rc;
    table->rows_count = 0;
    size_t rows_count = 0;
    rc = get_file_size(input, &rows_count);
    if (rc != EXIT_SUCCESS)
        return rc;
    if (rows_count == 0)
        return ERROR_EMPRY_FILE;
    rewind(input);
    country_t tmp_country;
    for(size_t i = 0; i < rows_count; i++)
    {
        read_country(&tmp_country, input);
        rc = add_row(table, &tmp_country);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    return EXIT_SUCCESS;
}

int add_row(table_t *table, country_t *row)
{
    if (table->rows_count + 1 > MAX_ROW_COUNT)
        return ERROR_ROW_COUNT;
    table->keys[table->rows_count].country_id = table->rows_count;
    table->keys[table->rows_count].min_rest_cost = row->min_rest_cost;
    table->countries[table->rows_count++] = *row;
    return EXIT_SUCCESS;
}

int find_key_by_id(table_t *table, size_t country_id, size_t *key_id)
{
    *key_id = 0;
    if (country_id > table->rows_count)
        return ERROR_WRONG_ID;
    for (size_t i = 0; i < table->rows_count; i++)
        if (table->keys[i].country_id == country_id)
        {
            *key_id = i;
            break;
        }
    return EXIT_SUCCESS;
}

int del_row_by_id(table_t *table, size_t id)
{
    if (id > table->rows_count)
        return ERROR_WRONG_ID;

    size_t key_id;
    int rc = find_key_by_id(table, id, &key_id);

    if (rc != EXIT_SUCCESS)
        return rc;

    // for (size_t i = key_id; i < table->rows_count; i++)
    //     table->keys[i] = table->keys[i + 1];

    for (size_t i = id; i < table->rows_count; i++)
        table->countries[i] = table->countries[i + 1];

    table->rows_count--;
    for (size_t i = 0; i < table->rows_count; i++)
    {
        table->keys[i].country_id = i;
        table->keys[i].min_rest_cost = table->countries[i].min_rest_cost;
    }
    
    return EXIT_SUCCESS;
}


void print_table(table_t *table, FILE *output)
{
    for (size_t i = 0; i < table->rows_count; i++)
    {
        printf("------------------------------\n");
        printf("ID: %zu\n", i);
        print_country(&table->countries[i], output);
    }
    printf("------------------------------\n");
}

void print_with_args(table_t *table, continent_enum continent, int max_cost, sports_enum sport_type, FILE *output)
{
    int is_some_print = 0;
    for (size_t i = 0; i < table->rows_count; i++)
    {
        country_t tmp_c = table->countries[i];
        if (tmp_c.tourism_type == SPORTS && tmp_c.continent == continent
            && tmp_c.min_rest_cost < max_cost && tmp_c.tourism.sport_type == sport_type)
        {
            is_some_print = 1;
            printf("------------------------------\n");
            printf("ID: %zu\n", i);
            print_country(&table->countries[i], output);
        }
    }
    if (is_some_print)
        printf("------------------------------\n");
}

void print_key(keys_table_t *key, FILE *output)
{
    fprintf(output, "Country id: %zu\n", key->country_id);
    fprintf(output, "Min rest cost: %d\n", key->min_rest_cost);
}

void print_keys_table(table_t *table, FILE *output)
{
    for (size_t i = 0; i < table->rows_count; i++)
    {
        printf("------------------------------\n");
        printf("ID: %zu\n", i);
        print_key(&table->keys[i], output);
    }
    printf("------------------------------\n");
}

void print_table_by_keys(table_t *table, FILE *output)
{
    for (size_t i = 0; i < table->rows_count; i++)
    {
        printf("------------------------------\n");
        printf("ID: %zu\n", i);
        print_country(&table->countries[table->keys[i].country_id], output);
    }
    printf("------------------------------\n");
}

int cmp_keys_cost(const void *p, const void *q)
{
    const keys_table_t *a = p;
    const keys_table_t *b = q;
    return a->min_rest_cost - b->min_rest_cost;
}

void swap_keys(table_t *base, ptrdiff_t ind1, ptrdiff_t ind2)
{
    size_t key1, key2;
    find_key_by_id(base, ind1, &key1);
    void *k1 = &base->keys[key1];
    find_key_by_id(base, ind2, &key2);
    void *k2 = &base->keys[key2];

    base->keys[key1].country_id = ind2;
    base->keys[key2].country_id = ind1;
    swap(k1, k2, sizeof(keys_table_t));
}

void buble_sort_table(table_t *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *), int by_key)
{
    for (size_t i = 0; i < nmemb; i++)
        for (size_t j = 0; j < nmemb - 1 - i; j++)
        {
            void *t1, *t2;
            if (by_key)
            {
                t1 = &base->keys[j];
                t2 = &base->keys[j + 1];
            }
            else
            {
                t1 = &base->countries[j];
                t2 = &base->countries[j + 1];
            }
            if (compar(t1, t2) > 0)
            {
                swap(t1, t2, size);
                if (!by_key)
                    swap_keys(base, j, j + 1);
            }
        }
}

void upgraded_buble_sort_table(table_t *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *), int by_key)
{
    ptrdiff_t l = 0, r = nmemb - 1;
    for (size_t i = 0; i < nmemb; i++)
    {
        if (i % 2 != 0)
        {
            for (ptrdiff_t j = l; j < r; j++)
            {
                void *t1, *t2;
                if (by_key)
                {
                    t1 = &base->keys[j];
                    t2 = &base->keys[j + 1];
                }
                else
                {
                    t1 = &base->countries[j];
                    t2 = &base->countries[j + 1];
                }
                if (compar(t1, t2) > 0)
                {
                    swap(t1, t2, size);
                    if (!by_key)
                        swap_keys(base, j, j + 1);
                }
            }
            r--;
        }
        else
        {
            for (ptrdiff_t j = r; j >= l; j--)
            {
                void *t1, *t2;
                if (by_key)
                {
                    t1 = &base->keys[j];
                    t2 = &base->keys[j - 1];
                }
                else
                {
                    t1 = &base->countries[j];
                    t2 = &base->countries[j - 1];
                }
                if (compar(t1, t2) < 0)
                {
                    swap(t1, t2, size);
                    if (!by_key)
                        swap_keys(base, j, j + 1);
                }
            }
            l++;
        }
    }
}

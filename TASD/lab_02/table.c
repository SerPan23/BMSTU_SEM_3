#include "table.h"

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

    for (size_t i = key_id + 1; i < table->rows_count; i++)
        table->keys[i] = table->keys[i + 1];

    for (size_t i = id + 1; i < table->rows_count; i++)
        table->countries[i] = table->countries[i + 1];
    
    table->rows_count--;
    return EXIT_SUCCESS;
}

void print_table(table_t *table)
{
    for (size_t i = 0; i < table->rows_count; i++)
    {
        printf("------------------------------\n");
        printf("ID: %zu\n", i);
        print_country(&table->countries[i]);
    }
    printf("------------------------------\n");
}

void print_with_args(table_t *table, char *continent, int max_cost, sports_enum sport_type)
{
    int is_some_print = 0;
    for (size_t i = 0; i < table->rows_count; i++)
    {
        country_t tmp_c = table->countries[i];
        if (tmp_c.tourism_type == SPORTS && strcmp(tmp_c.continent, continent) 
            && tmp_c.min_rest_cost < max_cost && tmp_c.tourism.sports.sport_type = sport_type)
        {
            is_some_print = 1;
            printf("------------------------------\n");
            printf("ID: %zu\n", i);
            print_country(&table->countries[i]);
        }
    }
    if (is_some_print)
        printf("------------------------------\n");
}

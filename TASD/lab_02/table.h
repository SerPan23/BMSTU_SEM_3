#ifndef TABLE_H
#define TABLE_H

#include "country.h"

#define MAX_ROW_COUNT 100

#define ERROR_ROW_COUNT 10
#define ERROR_WRONG_ID 11

typedef struct
{
    size_t country_id;
    int min_rest_cost;
} keys_table_t;

typedef struct
{
    keys_table_t keys[MAX_ROW_COUNT];
    country_t countries[MAX_ROW_COUNT];
    size_t rows_count;
} table_t;

int add_row(table_t *table, country_t *row);
int del_row_by_id(table_t *table, size_t id);
void print_table(table_t *table);
void print_with_args(table_t *table, char *continent, int max_cost, sports_enum sport_type);

#endif

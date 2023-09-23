#ifndef TABLE_H
#define TABLE_H

#include "country.h"

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

int read_table_from_file(table_t *table, FILE *input);
int add_row(table_t *table, country_t *row);
int del_row_by_id(table_t *table, size_t id);

void print_table(table_t *table, FILE *output);
void print_with_args(table_t *table, continent_enum continent, int max_cost, sports_enum sport_type, FILE *output);
void print_keys_table(table_t *table, FILE *output);
void print_table_by_keys(table_t *table, FILE *output);

int cmp_keys_cost(const void *p, const void *q);
void buble_sort_table(table_t *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *), int by_key);
void upgraded_buble_sort_table(table_t *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *), int by_key);

#endif

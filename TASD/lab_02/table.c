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

void print_header(FILE *f)
{
    // %4zu %*s %*s %*s %4s %2d:%2d %*d %10d %10s %10s %5.2lf %5.2lf %15s
    fprintf(f, "┌%s┬%s┬%s┬%s┬%s┬%s┬%s┬%s┬%s┬%s┬%s┬%s┬%s┬%s┐\n",
            "────",
            MAX_CELL_LINE,
            MAX_CELL_LINE,
            MAX_CELL_LINE,
            "────",
            "───────────────",
            MAX_CELL_LINE,
            "──────────",
            "──────────",
            "──────────",
            "──────────",
            "──────────",
            "───────────",
            "───────────────");
    //TODO: make header
    // fprintf(f, "│%4s│%4s│%*s│\n", "ID", "TABLE ID", MAX_STR_LEN, "Min rest cost");
    fprintf(f, "│%4s│%*s│%*s│%*s│%4s│%15s│%*s│%10s│%10s│%10s│%10s│%10s│%11s│%15s│\n",
            "ID",
            MAX_STR_LEN, "Name",
            MAX_STR_LEN, "Capital",
            MAX_STR_LEN, "Continent",
            "Visa",
            "Flight time",
            MAX_STR_LEN, "Min cost",
            "Tour type",
            "Obj count",
            "Objs type",
            "Season",
            "Air temp",
            "Water temp",
            "Sport type");
    // fprintf(f, "├%s┼%s┼%s┤\n")
    fprintf(f, "├%s┼%s┼%s┼%s┼%s┼%s┼%s┼%s┼%s┼%s┼%s┼%s┼%s┼%s┤\n",
            "────",
            MAX_CELL_LINE,
            MAX_CELL_LINE,
            MAX_CELL_LINE,
            "────",
            "───────────────",
            MAX_CELL_LINE,
            "──────────",
            "──────────",
            "──────────",
            "──────────",
            "──────────",
            "───────────",
            "───────────────");
}
void print_footer(FILE *f)
{
    // %4zu %*s %*s %*s %4s %2d:%2d %*d %10s %10d %10s %10s %5.2lf %5.2lf %15s
    fprintf(f, "└%s┴%s┴%s┴%s┴%s┴%s┴%s┴%s┴%s┴%s┴%s┴%s┴%s┴%s┘\n",
            "────",
            MAX_CELL_LINE,
            MAX_CELL_LINE,
            MAX_CELL_LINE,
            "────",
            "───────────────",
            MAX_CELL_LINE,
            "──────────",
            "──────────",
            "──────────",
            "──────────",
            "──────────",
            "───────────",
            "───────────────");
}

void print_row(size_t id, country_t *row)
{
    printf("│%4zu│%*s│%*s│%*s│%4s│%12d:%02d│%*d│", id,
           MAX_STR_LEN, row->name,
           MAX_STR_LEN, row->capital,
           MAX_STR_LEN, get_str_continent(row->continent),
           row->is_need_visa ? "Yes" : "No",
           row->flight_time.hours, row->flight_time.minute,
           MAX_STR_LEN, row->min_rest_cost);
    // printf("%10d %10s %10s %5.2lf %5.2lf %15s");
    switch (row->tourism_type)
    {
    case EXCURSION:
        printf("%10s│", "excursion");
        printf("%10d│%10s│%10s│%10s│%11s│%15s",
               row->tourism.excursion.obj_count,
               get_obj_main_type_str(row->tourism.excursion.obj_main_type),
               "-", "-", "-", "-");
        break;
    case BEACH:
        printf("%10s│", "beach");
        printf("%10s│%10s│%10s│%10.2lf│%11.2lf│%15s",
               "-", "-",
               get_season_str(row->tourism.beach.main_season),
               row->tourism.beach.air_temp,
               row->tourism.beach.water_temp, "-");
        break;
    case SPORTS:
        printf("%10s│", "sports");
        printf("%10s│%10s│%10s│%10s│%11s│%15s",
               "-", "-", "-", "-", "-",
               get_sports_str(row->tourism.sport_type));
        break;
    }
    printf("│\n");
}

void print_table(table_t *table, FILE *output)
{
    // for (size_t i = 0; i < table->rows_count; i++)
    // {
    //     printf("------------------------------\n");
    //     printf("ID: %zu\n", i);
    //     print_country(&table->countries[i], output);
    // }
    // printf("------------------------------\n");
    print_header(output);
    for (size_t i = 0; i < table->rows_count; i++)
    {
        print_row(i, &table->countries[i]);
    }
    print_footer(output);
}

void print_with_args(table_t *table, continent_enum continent, int max_cost, sports_enum sport_type, FILE *output)
{
    print_header(output);
    int is_some_print = 0;
    for (size_t i = 0; i < table->rows_count; i++)
    {
        country_t tmp_c = table->countries[i];
        if (tmp_c.tourism_type == SPORTS && tmp_c.continent == continent
            && tmp_c.min_rest_cost < max_cost && tmp_c.tourism.sport_type == sport_type)
        {
            is_some_print = 1;
            // printf("------------------------------\n");
            // printf("ID: %zu\n", i);
            // print_country(&table->countries[i], output);
            print_row(i, &table->countries[i]);
        }
    }
    if (is_some_print)
        print_footer(output);
        // printf("------------------------------\n");
}
void print_table_by_keys(table_t *table, FILE *output)
{
    // for (size_t i = 0; i < table->rows_count; i++)
    // {
    //     printf("------------------------------\n");
    //     printf("ID: %zu\n", i);
    //     print_country(&table->countries[table->keys[i].country_id], output);
    // }
    // printf("------------------------------\n");
    print_header(output);
    for (size_t i = 0; i < table->rows_count; i++)
    {
        print_row(i, &table->countries[table->keys[i].country_id]);
    }
    print_footer(output);
}

void print_key_header(FILE *f)
{

    fprintf(f, "┌%s┬%s┬%s┐\n",
            "────",
            "────────",
            MAX_CELL_LINE);
    fprintf(f, "│%4s│%4s│%*s│\n", "ID", "TABLE ID", MAX_STR_LEN, "Min rest cost");
    fprintf(f, "├%s┼%s┼%s┤\n",
            "────",
            "────────",
            MAX_CELL_LINE);
}

void print_key_footer(FILE *f)
{
    fprintf(f, "└%s┴%s┴%s┘\n",
            "────",
            "────────",
            MAX_CELL_LINE);
}

void print_key(size_t id, keys_table_t *key, FILE *output)
{
    // fprintf(output, "Country id: %zu\n", key->country_id);
    // fprintf(output, "Min rest cost: %d\n", key->min_rest_cost);
    fprintf(output, "│%4zu│%8zu│%*d│\n", id, key->country_id, MAX_STR_LEN, key->min_rest_cost);
}

void print_keys_table(table_t *table, FILE *output)
{
    // for (size_t i = 0; i < table->rows_count; i++)
    // {
    //     printf("------------------------------\n");
    //     printf("ID: %zu\n", i);
    //     print_key(&table->keys[i], output);
    // }
    // printf("------------------------------\n");
    print_key_header(output);
    for (size_t i = 0; i < table->rows_count; i++)
        print_key(i, &table->keys[i], output);
    print_key_footer(output);
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

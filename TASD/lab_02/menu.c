#include "menu.h"

#define MENU_ITEMS_COUNT 12

void print_menu(void)
{
    printf("------------------\n");
    printf("Menu:\n\
    1) Read table from file\n\
    2) Print keys table\n\
    3) Print table\n\
    4) Add new row\n\
    5) Delete row by id (warming: you need id from table\n\
    \tnot from keys table and you lose keys sort order!)\n\
    6) Print rows that meet conditions:\n\
    \ton the mainland that you choose,\n\
    \twith a cost below the specified one,\n\
    \twhere you can do the specified sport\n\
    7) Print sorted keys table\n\
    8) Print sorted table\n\
    9) Print table by sorted keys table\n\
    10) Print results of comparing efficiency by work with keys table and table\n\
    11) Print results of using various sorting algorithms\n\
    12) Update data in file\n\
    0) Quit programm\n");
    printf("------------------\n");
}

int choose_menu_item(int *command)
{
    printf("Choose menu item (0-%d):\n", MENU_ITEMS_COUNT);
    if (read_int(command, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        return ERROR_WRONG_MENU_ITEM;
    if (*command < 0 || *command > MENU_ITEMS_COUNT)
        return ERROR_WRONG_MENU_ITEM;
    return EXIT_SUCCESS;
}

void read_file_item(table_t *table, char *file_path)
{
    FILE *file;
    char tmp[MAX_STR_LEN + 1];
    size_t tmp_len;
    int rc;
    do
    {
        printf("Enter path to file with data:\n");
        rc = read_string(tmp, &tmp_len, MAX_STR_LEN, stdin);
        if (rc != EXIT_SUCCESS)
        {
            printf("ERROR: Invalid path\n");
            continue;
        }
        file = fopen(tmp, "r");
        if (file == NULL)
        {
            printf("ERROR: wrong path or file\n");
            rc = ERROR_WRONG_FILEPATH;
            continue;
        }
        rc = read_table_from_file(table, file);
        if (rc != EXIT_SUCCESS)
        {
            printf("ERROR: wrong file\n");
            continue;
        }
    } while (rc != EXIT_SUCCESS);
    strncpy(file_path, tmp, tmp_len);
    fclose(file);
    printf("FILE LOADED SUCCESS!\n");
}

void add_row_item(table_t *table)
{
    country_t tmp_country;
    int rc;
    do
    {
        printf("Enter new country:\n");
        read_country(&tmp_country, stdin);
        rc = add_row(table, &tmp_country);
        if (rc != EXIT_SUCCESS)
            printf("ERROR: something went wrong (code: %d)", rc);
    } while (rc != EXIT_SUCCESS);
}

void del_item(table_t *table)
{
    int id, rc;
    do
    {
        printf("Enter row id that you want delete:\n");
        if ((rc = read_int(&id, MAX_STR_LEN, stdin)) != EXIT_SUCCESS || id < 0)
            printf("ERROR: incorrect id\n");
        if (rc == EXIT_SUCCESS && ((size_t)id > table->rows_count))
        {
            printf("ERROR: id not in range of table ids\n");
            rc = EXIT_FAILURE;
        }
    } while(rc != EXIT_SUCCESS);
    del_row_by_id(table, id);
}

void args_print_item(table_t *table)
{
    int rc, max_cost;
    continent_enum continent;
    sports_enum sport_type;
    do
    {
        rc = read_continent(&continent, stdin);
        if (rc != EXIT_SUCCESS)
            printf("ERROR: %d\n", rc);
    } while (rc != EXIT_SUCCESS);
    do
    {
        printf("Enter max cost:\n");
        rc = read_int(&max_cost, MAX_STR_LEN, stdin);
        if (rc != EXIT_SUCCESS)
            printf("ERROR: %d\n", rc);
    } while (rc != EXIT_SUCCESS);
    do
    {
        rc = read_sports(&sport_type, stdin);
        if (rc != EXIT_SUCCESS)
            printf("ERROR: %d\n", rc);
    } while (rc != EXIT_SUCCESS);

    print_with_args(table, continent, max_cost, sport_type, stdout);
}

void menu(table_t *table)
{
    int command = -1, is_file = 0;
    char file_path[MAX_STR_LEN + 1] = "";
    while (command != 0)
    {
        print_menu();
        int rc = choose_menu_item(&command);
        if (rc != EXIT_SUCCESS)
        {
            printf("ERROR: wrong choose, you need enter numbers from 0 to %d\n", MENU_ITEMS_COUNT);
            continue;
        }
        if (command == 0)
            break;
        else if (command == 1)
        {
            read_file_item(table, file_path);
            is_file = 1;
        }
        else if (is_file)
        {
            if (command == 2)
                print_keys_table(table, stdout);
            else if (command == 3)
                print_table(table, stdout);
            else if(command == 4)
                add_row_item(table);
            else if (command == 5)
                del_item(table);
            else if (command == 6)
                args_print_item(table);
            else if (command == 7)
            {
                buble_sort_table(table, table->rows_count, sizeof(keys_table_t), cmp_keys_cost, 1);
                print_keys_table(table, stdout);
            }
            else if (command == 8)
            {
                buble_sort_table(table, table->rows_count, sizeof(country_t), cmp_country_cost, 0);
                print_table(table, stdout);
            }
            else if (command == 9)
            {
                buble_sort_table(table, table->rows_count, sizeof(keys_table_t), cmp_keys_cost, 1);
                print_table_by_keys(table, stdout);
            }
            else if (command == 10)
            {
                unsigned long long time1, time2;
                table_t tmp_table = *table;
                unsigned long long begin, end;

                begin = cur_ms_gettimeofday();
                buble_sort_table(&tmp_table, table->rows_count, sizeof(country_t), cmp_country_cost, 0);
                end = cur_ms_gettimeofday();
                time1 = end - begin;

                begin = cur_ms_gettimeofday();
                buble_sort_table(&tmp_table, table->rows_count, sizeof(keys_table_t), cmp_country_cost, 1);
                end = cur_ms_gettimeofday();
                time2 = end - begin;

                char *header = "┌──────────────────────────────┬───────────────┬───────────────┐\n";
                char *sep = "├──────────────────────────────┼───────────────┼───────────────┤\n";
                char *footer = "└──────────────────────────────┴───────────────┴───────────────┘\n";
                printf("%s", header);
                printf("│%30s│%15s│%15s│\n", "Operation type", "Time (ms)", "Memory (bytes)");
                printf("%s", sep);
                printf("│%30s│%15llu│%15zu│\n", "sort table by buble", time1, sizeof(country_t) * table->rows_count);
                printf("│%30s│%15llu│%15zu│\n", "sort keys by buble", time2, sizeof(keys_table_t) * table->rows_count);
                printf("%s", footer);
            }
            else if (command == 11)
            {
                unsigned long long time1, time2, time3, time4, time5;
                table_t tmp_table = *table;
                table_t tmp_table2 = *table;
                unsigned long long begin, end;

                begin = cur_ms_gettimeofday();
                buble_sort_table(&tmp_table, table->rows_count, sizeof(country_t), cmp_country_cost, 0);
                end = cur_ms_gettimeofday();
                time1 = end - begin;

                begin = cur_ms_gettimeofday();
                buble_sort_table(&tmp_table, table->rows_count, sizeof(keys_table_t), cmp_country_cost, 1);
                end = cur_ms_gettimeofday();
                time2 = end - begin;

                begin = cur_ms_gettimeofday();
                upgraded_buble_sort_table(&tmp_table2, table->rows_count, sizeof(country_t), cmp_country_cost, 0);
                end = cur_ms_gettimeofday();
                time3 = end - begin;

                begin = cur_ms_gettimeofday();
                upgraded_buble_sort_table(&tmp_table2, table->rows_count, sizeof(keys_table_t), cmp_country_cost, 1);
                end = cur_ms_gettimeofday();
                time4 = end - begin;

                country_t tc;
                begin = cur_ms_gettimeofday();
                for(size_t i = 0; i < table->rows_count; i++)
                {
                    tc = tmp_table2.countries[table->keys[i].country_id];
                    tc.min_rest_cost = tc.min_rest_cost;
                }
                end = cur_ms_gettimeofday();
                time5 = end - begin;
                char *header = "┌──────────────────────────────┬───────────────┬───────────────┐\n";
                char *sep = "├──────────────────────────────┼───────────────┼───────────────┤\n";
                char *footer = "└──────────────────────────────┴───────────────┴───────────────┘\n";
                printf("%s", header);
                printf("│%30s│%15s│%15s│\n", "Operation type", "Time (ms)", "Memory (bytes)");
                printf("%s", sep);
                printf("│%30s│%15llu│%15zu│\n", "sort table by buble", time1, sizeof(country_t) * table->rows_count);
                printf("│%30s│%15llu│%15zu│\n", "sort keys by buble", time2, sizeof(keys_table_t) * table->rows_count);
                printf("│%30s│%15llu│%15zu│\n", "sort table by upgrade buble", time3, sizeof(country_t) * table->rows_count);
                printf("│%30s│%15llu│%15zu│\n", "sort keys by upgrade buble", time4, sizeof(keys_table_t) * table->rows_count);
                printf("%s", sep);
                printf("│%30s│%15llu│%15zu│\n", "work table by sort keys", time5 + time4, (sizeof(keys_table_t) + sizeof(country_t)) * table->rows_count);
                printf("%s", footer);
            }
            else if (command == 12)
            {
                FILE *file = fopen(file_path, "w");
                for (size_t i = 0; i < table->rows_count; i++)
                    print_country(&table->countries[i], file);
                fclose(file);
                printf("FILE UPDATED!\n");
            }

        }
        else
            printf("ERROR: you need read file before doing something!\n");
    }
}

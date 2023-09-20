#include "table.h"

int main(void)
{
    country_t test;
    int rc = read_country(&test);
    if (rc != EXIT_SUCCESS)
    {
        printf("ERROR: %d\n", rc);
        return rc;
    }
    table_t table;
    rc = add_row(&table, &test);
    if (rc != EXIT_SUCCESS)
    {
        printf("ERROR: %d\n", rc);
        return rc;
    }
    print_table(&table);
    return 0;
}

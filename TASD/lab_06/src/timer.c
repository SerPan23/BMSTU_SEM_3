#include "timer.h"

char *header = "┌─────┬────────────────────┬────────────────────┬─────────────────────────┬─────────────────────────┐\n";
char *sep = "├─────┼────────────────────┼────────────────────┼─────────────────────────┼─────────────────────────┤\n";
char *footer = "└─────┴────────────────────┴────────────────────┴─────────────────────────┴─────────────────────────┘\n";

void print_table_header(void)
{
    printf("%s", header);
    printf("│%5s│%20s│%20s│%25s│%25s│\n", "Len", "String time(ns)",
           "Tree time(ns)", "Max string size(bytes)", "Max tree size(bytes)");
    printf("%s", sep);
}
void print_table_footer(void)
{
    printf("%s", footer);
}

void print_time(char *str)
{
    long time1, time2;
    long sum1 = 0, sum2 = 0;

    struct timespec begin, end;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        char *s = malloc((strlen(str) + 1) * sizeof(char));
        if (!s)
            break;
        strcpy(s, str);

        clock_gettime(CLOCK_REALTIME, &begin);
        del_repeats_from_str(s, strlen(s));
        clock_gettime(CLOCK_REALTIME, &end);
        sum1 += delta_time(begin, end);

        free(s);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    tree_node_t *tree = NULL;
    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        tree = tree_create_from_str(str, strlen(str));

        clock_gettime(CLOCK_REALTIME, &begin);
        tree_del_not_unique_nodes(&tree);
        clock_gettime(CLOCK_REALTIME, &end);
        sum2 += delta_time(begin, end);

        tree_free(&tree);
        tree = NULL;
    }
    time2 = sum2 / ITER_COUNT_TIME;

    size_t size1 = strlen(str) * sizeof(char);
    size_t size2 = strlen(str) * sizeof(tree_node_t);
    printf("│%5zu", strlen(str));
    printf("│%20lu│%20lu│", time1, time2);
    printf("%25zu│%25zu│\n", size1, size2);
    
}

void print_time_measurements(void)
{
    const size_t tests_len = 4;
    char *tests[tests_len] = {
        "13224",
        "718326699",
        "CEAA1BD2D2",
        "B2163455768972B",
    };

    printf("DEL ANALYZE\n");
    print_table_header();
    for (size_t i = 0; i < tests_len; i++)
        print_time(tests[i]);
    print_table_footer();

    printf("\n");
}

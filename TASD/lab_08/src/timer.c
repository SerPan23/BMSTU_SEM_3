#include "timer.h"

char *header = "┌───────────────┬──────────────────────────────┬──────────────────────────────┐\n";
char *sep = "├───────────────┼──────────────────────────────┼──────────────────────────────┤\n";
char *footer = "└───────────────┴──────────────────────────────┴──────────────────────────────┘\n";

void print_table_header(char *s1, char *s2, char *s3)
{
    printf("%s", header);
    printf("│%15s│%30s│%30s│\n", s1, s2, s3);
    printf("%s", sep);
}
void print_table_footer(void)
{
    printf("%s", footer);
}

void print_time(char *str, int start_node)
{
    graph_t *g = NULL;
    FILE *file = fopen(str, "r");
    graph_read_from_file(&g, file);
    fclose(file);

    path_t *path = NULL;

    long time1;
    long sum1 = 0;

    struct timespec begin, end;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);
        dijkstra(g, &path, start_node - 1);
        clock_gettime(CLOCK_REALTIME, &end);
        sum1 += delta_time(begin, end);

        path_free(&path);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    size_t size1 = g->n * sizeof(int) + 2 * sizeof(int);

    printf("│%15d", g->n);
    printf("│%30lu│%30zu│\n", time1, size1);

    graph_free(&g);
}

void print_time_measurements(void)
{
    const size_t tests_len = 4;
    char *tests[tests_len] = {
        "./data/graph_3.txt",
        "./data/graph_5.txt",
        "./data/graph_7.txt",
        "./data/graph_10.txt",
    };

    int tests_value[tests_len] = {
        1,
        1,
        1,
        1,
    };

    printf("PATH FIND ANALYZE\n");
    print_table_header("Node count", "Time(ns)", "Size (bytes)");
    for (size_t i = 0; i < tests_len; i++)
        print_time(tests[i], tests_value[i]);
    print_table_footer();
    printf("\n");
}

#include "timer.h"

char stack_array_data[MAX_STACK_LEN];

char *header = "┌─────┬────────────────────┬────────────────────┬─────────────────────────┬─────────────────────────┬──────────────────────────────┐\n";
char *sep    = "├─────┼────────────────────┼────────────────────┼─────────────────────────┼─────────────────────────┼──────────────────────────────┤\n";
char *footer = "└─────┴────────────────────┴────────────────────┴─────────────────────────┴─────────────────────────┴──────────────────────────────┘\n";

void print_table_header(void)
{
    printf("%s", header);
    printf("│%5s│%20s│%20s│%25s│%25s│%30s│\n", "Len", "Array stack time(ns)",
           "List stack time(ns)", "Max arr stack size(bytes)", "Array alloc size(bytes)", "Max list stack size(bytes)");
    printf("%s", sep);
}
void print_table_footer(void)
{
    printf("%s", footer);
}

void print_time(char *str, size_t strlen)
{
    stack_list_t stack_list;
    stack_list.ptr = NULL;
    stack_list.size = 0;
    stack_list.free_area_size_alloc = 0;

    stack_array_t stack_array;
    stack_array.data = stack_array_data;
    stack_array.size = 0;

    long time1, time2;
    long sum1 = 0, sum2 = 0;

    struct timespec begin, end;

    size_t max_size_1 = 0;
    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);
        is_bracket_seq(str, strlen, 0, &stack_list, &stack_array, 1, &max_size_1);
        clock_gettime(CLOCK_REALTIME, &end);
        sum1 += delta_time(begin, end);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    size_t max_size_2 = 0;
    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);
        is_bracket_seq(str, strlen, 1, &stack_list, &stack_array, 1, &max_size_2);
        clock_gettime(CLOCK_REALTIME, &end);
        sum2 += delta_time(begin, end);
    }
    time2 = sum2 / ITER_COUNT_TIME;

    size_t size1 = max_size_1 * sizeof(char);
    size_t size1_2 = MAX_STACK_LEN * sizeof(char);
    size_t size2 = max_size_2 * sizeof(list_node_t);
    printf("│%5zu", strlen);
    printf("│%20lu│%20lu│", time1, time2);
    printf("%25zu│%25zu│%30zu│\n", size1, size1_2, size2);
    stack_list_free(&stack_list);
}

void print_time_measurements(void)
{
    const size_t tests_len = 7;
    char *tests[tests_len] = {
        "{[[()]]}",
        "([{(((())))}])",
        "{([{(((())))}])[[[[()]]]]}",
        "[[[[[(((((((({([{(((())))}])[[[[()]]]]}))))))))]]]]]",
        "[[[[[(((((((({([{(((([[[[[(((((((({([{(((())))}])[[[[()]]]]}))))))))]]]]]))))}])[[[[()]]]]}))))))))]]]]]",
        "[[[[[(((((((({([{(((([[[[[(((((((({([{(((({([{(((())))}])[[[[()]]]]}))))}])[[[[({([{(((())))}])[[[[()]]]]})]]]]}))))))))]]]]]))))}])[[[[({([{(((())))}])[[[[()]]]]})]]]]}))))))))]]]]]",
        "[[[[[(((((((({([{(((([[[[[(((((((({([{(((({([{(((([[[[[(((((((({([{(((())))}])[[[[([[[[[(((((((({([{(((())))}])[[[[()]]]]}))))))))]]]]])]]]]}))))))))]]]]]))))}])[[[[()]]]]}))))}])[[[[({([{(((())))}])[[[[()]]]]})]]]]}))))))))]]]]]))))}])[[[[({([{(((())))}])[[[[()]]]]})]]]]}))))))))]]]]]",
    };

    print_table_header();
    for (size_t i = 0; i < tests_len; i++)
        print_time(tests[i], strlen(tests[i]));
    print_table_footer();
    printf("\n");
}

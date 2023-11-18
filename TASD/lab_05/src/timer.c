#include "timer.h"

char *header = "┌─────┬────────────────────┬────────────────────┬─────────────────────────┬─────────────────────────┬─────────────────────────┐\n";
char *sep = "├─────┼────────────────────┼────────────────────┼─────────────────────────┼─────────────────────────┼─────────────────────────┤\n";
char *footer = "└─────┴────────────────────┴────────────────────┴─────────────────────────┴─────────────────────────┴─────────────────────────┘\n";

void print_table_header(void)
{
    printf("%s", header);
    printf("│%5s│%20s│%20s│%25s│%25s│%25s│\n", "Size", "Array queue time(ns)",
           "List queue time(ns)", "Array queue size(bytes)", "Array alloc size(bytes)", "List queue size(bytes)");
    printf("%s", sep);
}
void print_table_footer(void)
{
    printf("%s", footer);
}

void fill_queue(int is_list_type, void *queue, size_t size)
{
    if (is_list_type)
    {
        queue_list_t *queue_list = queue;
        for (size_t i = 0; i < size; i++)
        {
            list_node_t *tmp;
            list_node_init(&tmp);
            queue_list_push(queue_list, tmp);
        }
    }
    else
    {
        queue_array_t *queue_ar = queue;
        for (size_t i = 0; i < size; i++)
        {
            array_element_t tmp;
            array_el_init(&tmp);
            queue_array_push(queue_ar, &tmp);
        }
    }
}

void clear_queue(int is_list_type, void *queue, size_t size)
{
    if (is_list_type)
    {
        queue_list_t *queue_list = queue;
        for (size_t i = 0; i < size; i++)
        {
            queue_list_pop(queue_list, NULL);
        }
    }
    else
    {
        queue_array_t *queue_ar = queue;
        for (size_t i = 0; i < size; i++)
        {
            queue_array_pop(queue_ar, NULL);
        }
    }
}

void print_time_push(size_t size)
{
    queue_array_t queue_arr;
    queue_array_init(&queue_arr);

    queue_list_t queue_list;
    queue_list_init(&queue_list);

    long time1, time2;
    long sum1 = 0, sum2 = 0;

    struct timespec begin, end;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);
        fill_queue(0, (void *)&queue_arr, size);
        clock_gettime(CLOCK_REALTIME, &end);
        clear_queue(0, (void *)&queue_arr, size);
        sum1 += delta_time(begin, end);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        list_node_t *tmp;
        list_node_init(&tmp);
        clock_gettime(CLOCK_REALTIME, &begin);
        fill_queue(1, (void *)&queue_list, size);
        clock_gettime(CLOCK_REALTIME, &end);
        clear_queue(1, (void *)&queue_list, size);
        sum2 += delta_time(begin, end);
    }
    time2 = sum2 / ITER_COUNT_TIME;

    size_t size1 = size * sizeof(array_element_t);
    size_t size1_2 = MAX_QUEUE_LEN * sizeof(array_element_t);
    size_t size2 = size * sizeof(list_node_t);
    printf("│%5zu", size);
    printf("│%20lu│%20lu│", time1, time2);
    printf("%25zu│%25zu│%25zu│\n", size1, size1_2, size2);
    queue_list_free(&queue_list);
}

void print_time_pop(size_t size)
{
    queue_array_t queue_arr;
    queue_array_init(&queue_arr);

    queue_list_t queue_list;
    queue_list_init(&queue_list);

    long time1, time2;
    long sum1 = 0, sum2 = 0;

    struct timespec begin, end;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        fill_queue(0, (void *)&queue_arr, size);
        clock_gettime(CLOCK_REALTIME, &begin);
        clear_queue(0, (void *)&queue_arr, size);
        clock_gettime(CLOCK_REALTIME, &end);
        sum1 += delta_time(begin, end);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        fill_queue(1, (void *)&queue_list, size);
        clock_gettime(CLOCK_REALTIME, &begin);
        clear_queue(1, (void *)&queue_list, size);
        clock_gettime(CLOCK_REALTIME, &end);
        sum2 += delta_time(begin, end);
    }
    time2 = sum2 / ITER_COUNT_TIME;

    size_t size1 = size * sizeof(array_element_t);
    size_t size1_2 = MAX_QUEUE_LEN * sizeof(array_element_t);
    size_t size2 = size * sizeof(list_node_t);
    printf("│%5zu", size);
    printf("│%20lu│%20lu│", time1, time2);
    printf("%25zu│%25zu│%25zu│\n", size1, size1_2, size2);
    queue_list_free(&queue_list);
}

void print_time_measurements(void)
{
    const size_t tests_len = 7;
    size_t tests[tests_len] = { 10, 25, 50, 100, 250, 500, 1000 };

    printf("PUSH ANALYZE\n");
    print_table_header();
    for (size_t i = 0; i < tests_len; i++)
        print_time_push(tests[i]);
    print_table_footer();
    printf("\n");

    printf("POP ANALYZE\n");
    print_table_header();
    for (size_t i = 0; i < tests_len; i++)
        print_time_pop(tests[i]);
    print_table_footer();
    printf("\n");
}

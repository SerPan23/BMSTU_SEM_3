#include "timer.h"

char *header = "┌─────┬──────────────────────────────┬──────────────────────────────┬──────────────────────────────┬──────────────────────────────┬──────────────────────────────┐\n";
char *sep = "├─────┼──────────────────────────────┼──────────────────────────────┼──────────────────────────────┼──────────────────────────────┼──────────────────────────────┤\n";
char *footer = "└─────┴──────────────────────────────┴──────────────────────────────┴──────────────────────────────┴──────────────────────────────┴──────────────────────────────┘\n";

void print_table_header(char *s1, char *s2, char *s3, char *s4, char *s5)
{
    printf("%s", header);
    // printf("│%5s│%20s│%20s│%25s│%25s│\n", "Len",
    //        "Tree time(ns)", "Balanced tree time(ns)", "Hash table time(ns)",
    //        "Tree size(bytes)", "Balanced tree size(bytes)", "Hash table size(bytes)");
    printf("│%5s│%30s│%30s│%30s│%30s│%30s│\n", "Len", s1, s2, s3, s4, s5);
    printf("%s", sep);
}
void print_table_footer(void)
{
    printf("%s", footer);
}

void print_time(char *str, char value)
{
    tree_node_t *tree = NULL;
    tree = tree_create_from_str(str, strlen(str));

    tree_del_not_unique_nodes(&tree);

    tree_node_t *balanced_tree = tree_balance_BST(tree);

    tree_node_t *avl_tree = AVL_tree_from_tree(tree);

    hash_table_t *table_opened;
    table_opened = table_init(OPENED);

    table_create_from_str(&table_opened, str);

    table_restruct_if_need(&table_opened);

    hash_table_t *table_closed;
    table_closed = table_init(CLOSED);

    table_create_from_str(&table_closed, str);

    table_restruct_if_need(&table_closed);


    long time1, time2, time3, time4, time5;
    long sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;

    struct timespec begin, end;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        tree_node_t *node = NULL;
        int flag = 0;

        clock_gettime(CLOCK_REALTIME, &begin);
        tree_search_in_sorted(&tree, &node, value, &flag, NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        sum1 += delta_time(begin, end);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    
    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        tree_node_t *node = NULL;
        int flag = 0;

        clock_gettime(CLOCK_REALTIME, &begin);
        tree_search(&tree, &node, value, &flag, NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        sum2 += delta_time(begin, end);
    }
    time2 = sum2 / ITER_COUNT_TIME;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {   
        tree_node_t *node = NULL;
        int flag = 0;

        clock_gettime(CLOCK_REALTIME, &begin);
        tree_search_in_sorted(&tree, &node, value, &flag, NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        sum3 += delta_time(begin, end);
    }
    time3 = sum3 / ITER_COUNT_TIME;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);
        table_search(table_opened, value, NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        sum4 += delta_time(begin, end);
    }
    time4 = sum4 / ITER_COUNT_TIME;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);
        table_search(table_closed, value, NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        sum5 += delta_time(begin, end);
    }
    time5 = sum5 / ITER_COUNT_TIME;

    printf("│%5zu", strlen(str));
    printf("│%30lu│%30lu│%30lu│%30lu│%30lu│\n", time1, time2, time3, time4, time5);

    tree_free(&tree);
    tree_free(&balanced_tree);
    tree_free(&avl_tree);
    table_free(table_opened);
    table_free(table_closed);
}

void print_sizes(char *str)
{

    tree_node_t *tree = NULL;
    tree = tree_create_from_str(str, strlen(str));

    tree_del_not_unique_nodes(&tree);

    tree_node_t *balanced_tree = tree_balance_BST(tree);

    tree_node_t *avl_tree = AVL_tree_from_tree(tree);

    size_t size1 = tree_count_nodes(tree) * sizeof(tree_node_t);
    size_t size2 = tree_count_nodes(balanced_tree) * sizeof(tree_node_t);
    size_t size3 = tree_count_nodes(avl_tree) * sizeof(tree_node_t);

    hash_table_t *table_opened;
    table_opened = table_init(OPENED);

    table_create_from_str(&table_opened, str);
    table_restruct_if_need(&table_opened);

    size_t size4 = table_opened->size * sizeof(data_t);

    hash_table_t *table_closed;
    table_closed = table_init(CLOSED);

    table_create_from_str(&table_closed, str);
    table_restruct_if_need(&table_closed);

    size_t size5 = table_closed->size * sizeof(data_t);

    printf("│%5zu", strlen(str));
    printf("│%30zu│%30zu│%30zu│%30lu│%30lu│\n", size1, size2, size3, size4, size5);

    tree_free(&tree);
    tree_free(&balanced_tree);
    tree_free(&avl_tree);
    table_free(table_opened);
    table_free(table_closed);
}

void print_cmp_counts(char *str, char value)
{
    tree_node_t *tree = NULL;
    tree = tree_create_from_str(str, strlen(str));

    tree_del_not_unique_nodes(&tree);

    tree_node_t *balanced_tree = tree_balance_BST(tree);

    tree_node_t *avl_tree = AVL_tree_from_tree(tree);

    hash_table_t *table_opened;
    table_opened = table_init(OPENED);

    table_create_from_str(&table_opened, str);
    table_restruct_if_need(&table_opened);

    hash_table_t *table_closed;
    table_closed = table_init(CLOSED);

    table_create_from_str(&table_closed, str);
    table_restruct_if_need(&table_closed);

    tree_node_t *node = NULL;
    int flag = 0;

    int cmp_1 = 0;
    int cmp_2 = 0;
    int cmp_3 = 0;
    int cmp_4 = 0;
    int cmp_5 = 0;

    tree_search_in_sorted(&tree, &node, value, &flag, &cmp_1);

    node = NULL;
    flag = 0;

    tree_search(&balanced_tree, &node, value, &flag, &cmp_2);

    node = NULL;
    flag = 0;

    tree_search_in_sorted(&avl_tree, &node, value, &flag, &cmp_3);

    table_search(table_opened, value, &cmp_4);

    table_search(table_closed, value, &cmp_5);

    printf("│%5zu", strlen(str));
    printf("│%30d│%30d│%30d│%30d│%30d│\n", cmp_1, cmp_2, cmp_3, cmp_4, cmp_5);

    // char tmp[30];

    // sprintf(tmp, "result_%c", value);
    // open_tree_img(tmp, tree);

    // sprintf(tmp, "result_balanced_%c", value);
    // open_tree_img(tmp, balanced_tree);

    // sprintf(tmp, "result_avl_%c", value);
    // open_tree_img("result_avl", avl_tree);

    tree_free(&tree);
    tree_free(&balanced_tree);
    tree_free(&avl_tree);
    table_free(table_opened);
    table_free(table_closed);
}

void print_time_measurements(void)
{
    const size_t tests_len = 6;
    char *tests[tests_len] = {
        "13224",
        "718326699",
        "CEAA1BD2D2",
        "B2163455768972B",
        "B613457982bac",
        "abcdefghijklmnopqrstuvwxyz",
        // "poelpospalincorporated1233742069aaquickbrownfoxjumpsoverthelazybulldog",
    };

    char tests_value[tests_len] = {
        '1',
        '2',
        'B',
        '9',
        '7',
        'z',
        // 'g',
    };

    printf("SEARCH ANALYZE\n");
    print_table_header("Tree time(ns)", "Balanced tree time(ns)",
                       "AVL tree time(ns)", "Hash table opened time(ns)", "Hash table closed time(ns)");
    for (size_t i = 0; i < tests_len; i++)
        print_time(tests[i], tests_value[i]);
    print_table_footer();
    printf("\n");

    print_table_header("Tree size(bytes)", "Balanced tree size(bytes)",
                       "AVL tree size(bytes)", "Hash table opened size(bytes)", "Hash table closed size(bytes)");
    for (size_t i = 0; i < tests_len; i++)
        print_sizes(tests[i]);
    print_table_footer();
    printf("\n");

    print_table_header("Tree cmp count", "Balanced cmp count",
                       "AVL cmp count", "Hash cmp opened count", "Hash cmp closed count");
    for (size_t i = 0; i < tests_len; i++)
        print_cmp_counts(tests[i], tests_value[i]);
    print_table_footer();
    printf("\n");
}

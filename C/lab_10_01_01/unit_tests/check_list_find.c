#include "check_funcs.h"
#include <string.h>

static int my_strcmp(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}

/* -----positives----- */
START_TEST(one_element)
{
    node_t *head = NULL;
    char *data = "test";
    list_push(&head, (void *)data);

    node_t *find_node = find(head, data, my_strcmp);

    int rc = my_strcmp(find_node->data, data);
    ck_assert_int_eq(rc, 0);

    list_free(&head);
}

START_TEST(find_null)
{
    node_t *head = NULL;
    char *data = "test";

    node_t *find_node = find(head, data, my_strcmp);

    int rc = find_node == NULL;

    ck_assert_int_eq(rc, 1);

    list_free(&head);
}

START_TEST(simple_test)
{
    node_t *head = NULL;
    char *data[5] = {
        "test",
        "test1",
        "2test2",
        "t2",
        "a"
    };
    for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        list_push(&head, (void *)data[i]);

    char *find_data = "a";

    node_t *find_node = find(head, find_data, my_strcmp);

    int rc = my_strcmp(find_node->data, find_data);
    ck_assert_int_eq(rc, 0);

    list_free(&head);
}

END_TEST
/* ------------------- */

Suite *list_find_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("list_find");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, one_element);
    tcase_add_test(tc_pos, find_null);
    tcase_add_test(tc_pos, simple_test);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

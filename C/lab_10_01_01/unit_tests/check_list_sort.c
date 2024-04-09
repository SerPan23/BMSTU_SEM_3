#include "check_funcs.h"
#include <string.h>

static int my_strcmp(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}

/* -----positives----- */
START_TEST(no_els)
{
    node_t *head = NULL;

    head = sort(head, my_strcmp);

    int rc = head == NULL;
    ck_assert_int_eq(rc, 1);

    list_free(&head);
}

START_TEST(one_el)
{
    node_t *head = NULL;
    char *data[1] = { "test" };
    size_t n = sizeof(data) / sizeof(data[0]);
    for (size_t i = 0; i < n; i++)
        list_push(&head, (void *)data[i]);

    head = sort(head, my_strcmp);

    char *result[1] = { "test" };

    size_t n_res = sizeof(result) / sizeof(result[0]);
    node_t *cur = head;
    for (size_t i = 0; i < n_res; i++)
    {
        int rc = strcmp(cur->data, result[i]);
        ck_assert_int_eq(rc, 0);
        cur = cur->next;
    }

    list_free(&head);
}

START_TEST(simple_test)
{
    node_t *head = NULL;
    char *data[5] = {
        "2",
        "5",
        "3",
        "4",
        "1",
    };
    size_t n = sizeof(data) / sizeof(data[0]);
    for (size_t i = 0; i < n; i++)
        list_push(&head, (void *)data[i]);

    head = sort(head, my_strcmp);

    char *result[5] = {
        "1",
        "2",
        "3",
        "4",
        "5",
    };

    size_t n_res = sizeof(result) / sizeof(result[0]);
    node_t *cur = head;
    for (size_t i = 0; i < n_res; i++)
    {
        int rc = strcmp(cur->data, result[i]);
        ck_assert_int_eq(rc, 0);
        cur = cur->next;
    }

    list_free(&head);
}

END_TEST
/* ------------------- */

Suite *list_sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("list_sort");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, no_els);
    tcase_add_test(tc_pos, one_el);
    tcase_add_test(tc_pos, simple_test);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

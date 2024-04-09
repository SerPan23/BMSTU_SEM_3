#include "check_funcs.h"
#include <string.h>

/* -----positives----- */
START_TEST(clear_list)
{
    node_t *head = NULL;
    char *data = "test";
    list_push(&head, (void *)data);

    void *tmp = pop_back(&head);

    int rc = strcmp((char *)tmp, data);
    ck_assert_int_eq(rc, 0);

    list_free(&head);
}

START_TEST(pop_from_null_list)
{
    node_t *head = NULL;

    void *tmp = pop_back(&head);

    int rc = tmp == NULL;

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
        "a"};
    size_t n = sizeof(data) / sizeof(data[0]);
    for (size_t i = 0; i < n; i++)
        list_push(&head, (void *)data[i]);

    void *tmp = pop_back(&head);

    int rc = strcmp((char *)tmp, data[n - 1]);
    ck_assert_int_eq(rc, 0);

    list_free(&head);
}

END_TEST
/* ------------------- */

Suite *list_pop_back_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("list_pop_back");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, clear_list);
    tcase_add_test(tc_pos, pop_from_null_list);
    tcase_add_test(tc_pos, simple_test);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

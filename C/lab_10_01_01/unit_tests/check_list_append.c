#include "check_funcs.h"
#include <string.h>

/* -----positives----- */
START_TEST(app_null_el)
{
    node_t *head_1 = NULL;

    node_t *head_2 = NULL;
    char *data = "test";
    list_push(&head_2, (void *)data);

    append(&head_1, &head_2);

    int rc = head_1->next == NULL && strcmp(head_1->data, data) == 0;
    ck_assert_int_eq(rc, 1);

    list_free(&head_1);
}

START_TEST(app_el_null)
{
    node_t *head_2 = NULL;

    node_t *head_1 = NULL;
    char *data = "test";
    list_push(&head_1, (void *)data);

    append(&head_1, &head_2);

    int rc = head_1->next == NULL && strcmp(head_1->data, data) == 0;
    ck_assert_int_eq(rc, 1);

    list_free(&head_1);
}

END_TEST

START_TEST(app_el_el)
{
    node_t *head_1 = NULL;
    char *data = "test";
    list_push(&head_1, (void *)data);

    node_t *head_2 = NULL;
    char *data2 = "test2";
    list_push(&head_2, (void *)data2);

    append(&head_1, &head_2);

    int rc = head_1->next != NULL && strcmp(head_1->data, data) == 0;
    rc = rc && head_1->next->next == NULL && strcmp(head_1->next->data, data2) == 0;
    ck_assert_int_eq(rc, 1);

    list_free(&head_1);
    list_free(&head_2);
}
/* ------------------- */

Suite *list_append_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("list_append");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, app_null_el);
    tcase_add_test(tc_pos, app_el_null);
    tcase_add_test(tc_pos, app_el_el);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

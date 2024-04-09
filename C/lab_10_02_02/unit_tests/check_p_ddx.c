#include "check_funcs.h"

/* -----positives----- */
START_TEST(two_coef)
{
    polynomial_t polynomial = {NULL, 0};

    int data[2] = { 3, 4 };

    size_t n = sizeof(data) / sizeof(data[0]);

    for (size_t i = 0; i < n; i++)
    {
        pnode_t *new_node;
        pnode_alloc(&new_node);
        new_node->coefficient = data[i];
        new_node->next = NULL;
        polynomial_push(&polynomial, new_node);
    }

    int result[1] = { 3 };
    size_t n_res = sizeof(result) / sizeof(result[0]);

    polynomial_ddx(&polynomial);

    pnode_t *cur = polynomial.list_head;

    for (size_t i = 0; i < n_res; i++)
    {
        ck_assert_int_eq(cur->coefficient, result[i]);
        cur = cur->next;
    }

    polynomial_free(&polynomial);
}

START_TEST(simple_test)
{
    polynomial_t polynomial = {NULL, 0};

    int data[5] = { 3, 4, 1, 0, 2 };

    size_t n = sizeof(data) / sizeof(data[0]);

    for (size_t i = 0; i < n; i++)
    {
        pnode_t *new_node;
        pnode_alloc(&new_node);
        new_node->coefficient = data[i];
        new_node->next = NULL;
        polynomial_push(&polynomial, new_node);
    }

    int result[4] = { 12, 12, 2, 0 };
    size_t n_res = sizeof(result) / sizeof(result[0]);

    polynomial_ddx(&polynomial);

    pnode_t *cur = polynomial.list_head;

    for (size_t i = 0; i < n_res; i++)
    {
        ck_assert_int_eq(cur->coefficient, result[i]);
        cur = cur->next;
    }

    polynomial_free(&polynomial);
}

END_TEST
/* ------------------- */

Suite *p_ddx_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("p_ddx");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, two_coef);
    tcase_add_test(tc_pos, simple_test);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}
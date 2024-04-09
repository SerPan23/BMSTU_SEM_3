#include "check_funcs.h"

/* -----positives----- */
START_TEST(two_and_two_coef)
{
    polynomial_t polynomial_1 = {NULL, 0};

    int data_1[2] = { 10, 3 };

    size_t n = sizeof(data_1) / sizeof(data_1[0]);

    for (size_t i = 0; i < n; i++)
    {
        pnode_t *new_node;
        pnode_alloc(&new_node);
        new_node->coefficient = data_1[i];
        new_node->next = NULL;
        polynomial_push(&polynomial_1, new_node);
    }

    polynomial_t polynomial_2 = {NULL, 0};

    int data_2[2] = { 3, 4 };

    size_t n_2 = sizeof(data_2) / sizeof(data_2[0]);

    for (size_t i = 0; i < n_2; i++)
    {
        pnode_t *new_node;
        pnode_alloc(&new_node);
        new_node->coefficient = data_2[i];
        new_node->next = NULL;
        polynomial_push(&polynomial_2, new_node);
    }

    int result[2] = { 13, 7 };
    size_t n_res = sizeof(result) / sizeof(result[0]);


    polynomial_sum(&polynomial_1, &polynomial_2);

    pnode_t *cur = polynomial_1.list_head;

    for (size_t i = 0; i < n_res; i++)
    {
        ck_assert_int_eq(cur->coefficient, result[i]);
        cur = cur->next;
    }

    polynomial_free(&polynomial_1);
    polynomial_free(&polynomial_2);
}

START_TEST(five_and_three_coef)
{
    polynomial_t polynomial_1 = { NULL, 0 };

    int data_1[5] = { 10, 3, 9, 37, 0 };

    size_t n = sizeof(data_1) / sizeof(data_1[0]);

    for (size_t i = 0; i < n; i++)
    {
        pnode_t *new_node;
        pnode_alloc(&new_node);
        new_node->coefficient = data_1[i];
        new_node->next = NULL;
        polynomial_push(&polynomial_1, new_node);
    }

    polynomial_t polynomial_2 = { NULL, 0 };

    int data_2[3] = { 1, 3, 4 };

    size_t n_2 = sizeof(data_2) / sizeof(data_2[0]);

    for (size_t i = 0; i < n_2; i++)
    {
        pnode_t *new_node;
        pnode_alloc(&new_node);
        new_node->coefficient = data_2[i];
        new_node->next = NULL;
        polynomial_push(&polynomial_2, new_node);
    }

    int result[5] = { 10, 3, 10, 40, 4 };
    size_t n_res = sizeof(result) / sizeof(result[0]);

    polynomial_sum(&polynomial_1, &polynomial_2);

    pnode_t *cur = polynomial_1.list_head;

    for (size_t i = 0; i < n_res; i++)
    {
        ck_assert_int_eq(cur->coefficient, result[i]);
        cur = cur->next;
    }

    polynomial_free(&polynomial_1);
    polynomial_free(&polynomial_2);
}

END_TEST
/* ------------------- */

Suite *p_sum_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("p_sum");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, two_and_two_coef);
    tcase_add_test(tc_pos, five_and_three_coef);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}
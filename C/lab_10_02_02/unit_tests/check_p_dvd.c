#include "check_funcs.h"

/* -----positives----- */
START_TEST(two_coef)
{
    polynomial_t polynomial = { NULL, 0 };

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

    int result_even[1] = { 4 };
    size_t n_res_e = sizeof(result_even) / sizeof(result_even[0]);

    int result_odd[1] = { 3 };
    size_t n_res_o = sizeof(result_odd) / sizeof(result_odd[0]);

    polynomial_t even = { NULL, 0 };
    polynomial_t odd = { NULL, 0 };

    polynomial_dvd(&polynomial, &even, &odd);

    pnode_t *cur_even = even.list_head;

    for (size_t i = 0; i < n_res_e; i++)
    {
        ck_assert_int_eq(cur_even->coefficient, result_even[i]);
        cur_even = cur_even->next;
    }

    pnode_t *cur_odd = odd.list_head;

    for (size_t i = 0; i < n_res_o; i++)
    {
        ck_assert_int_eq(cur_odd->coefficient, result_odd[i]);
        cur_odd = cur_odd->next;
    }

    polynomial_free(&polynomial);
    polynomial_free(&even);
    polynomial_free(&odd);
}

START_TEST(five_coef)
{
    polynomial_t polynomial = { NULL, 0 };

    int data[5] = { 3, 4, 10, 7, 2 };

    size_t n = sizeof(data) / sizeof(data[0]);

    for (size_t i = 0; i < n; i++)
    {
        pnode_t *new_node;
        pnode_alloc(&new_node);
        new_node->coefficient = data[i];
        new_node->next = NULL;
        polynomial_push(&polynomial, new_node);
    }

    int result_even[3] = { 3, 10, 2 };
    size_t n_res_e = sizeof(result_even) / sizeof(result_even[0]);

    int result_odd[2] = { 4, 7 };
    size_t n_res_o = sizeof(result_odd) / sizeof(result_odd[0]);

    polynomial_t even = { NULL, 0 };
    polynomial_t odd = { NULL, 0 };

    polynomial_dvd(&polynomial, &even, &odd);

    pnode_t *cur_even = even.list_head;

    for (size_t i = 0; i < n_res_e; i++)
    {
        ck_assert_int_eq(cur_even->coefficient, result_even[i]);
        cur_even = cur_even->next;
    }

    pnode_t *cur_odd = odd.list_head;

    for (size_t i = 0; i < n_res_o; i++)
    {
        ck_assert_int_eq(cur_odd->coefficient, result_odd[i]);
        cur_odd = cur_odd->next;
    }

    polynomial_free(&polynomial);
    polynomial_free(&even);
    polynomial_free(&odd);
}

END_TEST
/* ------------------- */

Suite *p_dvd_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("p_dvd");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, two_coef);
    tcase_add_test(tc_pos, five_coef);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}
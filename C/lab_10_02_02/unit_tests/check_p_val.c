#include "check_funcs.h"

/* -----positives----- */
START_TEST(one_coef)
{
    polynomial_t polynomial = {NULL, 0};

    int data[1] = { 1 };

    size_t n = sizeof(data) / sizeof(data[0]);

    for (size_t i = 0; i < n; i++)
    {
        pnode_t *new_node;
        pnode_alloc(&new_node);
        new_node->coefficient = data[i];
        new_node->next = NULL;
        polynomial_push(&polynomial, new_node);
    }

    int a = 3;

    int result = 1;

    int tmp = polynomial_val(&polynomial, a);
    
    ck_assert_int_eq(tmp, result);

    polynomial_free(&polynomial);
}

START_TEST(simple_test)
{
    polynomial_t polynomial = {NULL, 0};

    int data[3] = {3, 4, 1};

    size_t n = sizeof(data) / sizeof(data[0]);

    for (size_t i = 0; i < n; i++)
    {
        pnode_t *new_node;
        pnode_alloc(&new_node);
        new_node->coefficient = data[i];
        new_node->next = NULL;
        polynomial_push(&polynomial, new_node);
    }

    int a = 3;

    int result = 40;

    int tmp = polynomial_val(&polynomial, a);

    ck_assert_int_eq(tmp, result);

    polynomial_free(&polynomial);
}

END_TEST
/* ------------------- */

Suite *p_val_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("p_val");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, one_coef);
    tcase_add_test(tc_pos, simple_test);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}
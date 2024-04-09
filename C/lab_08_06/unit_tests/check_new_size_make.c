#include "check_funcs.h"

/* -----positives----- */
START_TEST(test_add_one_size)
{
    matrix_t mat_a = { NULL, 0, 0 };
    mat_a.n = 2;
    mat_a.m = 2;
    matrix_alloc(&mat_a);
    int data[2][2] = {
        {1, 2},
        {4, 5},
    };

    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            mat_a.matrix[i][j] = data[i][j];

    int result[3][3] = {
        {1, 2, 1},
        {4, 5, 4},
        {2, 3, 2},
    };

    int rc = matrix_to_new_size(&mat_a, 3);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(mat_a.matrix[i][j], result[i][j]);

    matrix_free(&mat_a);
}
END_TEST

START_TEST(test_simple)
{
    matrix_t mat_a = { NULL, 0, 0 };
    mat_a.n = 1;
    mat_a.m = 1;
    matrix_alloc(&mat_a);
    int data[1][1] = {
        {1},
    };

    for (size_t i = 0; i < 1; i++)
        for (size_t j = 0; j < 1; j++)
            mat_a.matrix[i][j] = data[i][j];

    int result[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1},
    };

    int rc = matrix_to_new_size(&mat_a, 3);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(mat_a.matrix[i][j], result[i][j]);

    matrix_free(&mat_a);
}
END_TEST

Suite *matrix_to_new_size_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("matrix_to_new_size");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_add_one_size);
    tcase_add_test(tc_pos, test_simple);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

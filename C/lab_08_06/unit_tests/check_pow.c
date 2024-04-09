#include "check_funcs.h"

/* -----negatives----- */

START_TEST(test_not_square_matrix)
{
    matrix_t mat_a = { NULL, 0, 0 };
    mat_a.n = 4;
    mat_a.m = 3;
    matrix_alloc(&mat_a);
    int data[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {7, 8, 9},
    };

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 3; j++)
            mat_a.matrix[i][j] = data[i][j];

    int rc = matrix_pow(&mat_a, 2);
    ck_assert_int_eq(rc, ERROR_NOT_SQUARE_MATRIX);

    matrix_free(&mat_a);
}
END_TEST

/* ------------------- */

/* -----positives----- */
START_TEST(test_simple_pow)
{
    matrix_t mat_a = { NULL, 0, 0 };
    mat_a.n = 3;
    mat_a.m = 3;
    matrix_alloc(&mat_a);
    int data[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            mat_a.matrix[i][j] = data[i][j];

    int result[3][3] = {
        {30, 36, 42},
        {66, 81, 96},
        {102, 126, 150},
    };

    int rc = matrix_pow(&mat_a, 2);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(mat_a.matrix[i][j], result[i][j]);

    matrix_free(&mat_a);
}
END_TEST

START_TEST(test_zero_pow)
{
    matrix_t mat_a = { NULL, 0, 0 };
    mat_a.n = 3;
    mat_a.m = 3;
    matrix_alloc(&mat_a);
    int data[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            mat_a.matrix[i][j] = data[i][j];

    int result[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };

    int rc = matrix_pow(&mat_a, 0);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(mat_a.matrix[i][j], result[i][j]);

    matrix_free(&mat_a);
}
END_TEST

Suite *matrix_pow_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("matrix_pow");

    tc_neg = tcase_create("negatives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_neg, test_not_square_matrix);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_simple_pow);
    tcase_add_test(tc_pos, test_zero_pow);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

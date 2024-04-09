#include "check_funcs.h"

/* -----positives----- */
START_TEST(test_del_rows)
{
    matrix_t mat_a = { NULL, 0, 0 };
    mat_a.n = 4;
    mat_a.m = 3;
    matrix_alloc(&mat_a);
    int data[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, -1, 9},
        {7, 8, 9},
    };

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 3; j++)
            mat_a.matrix[i][j] = data[i][j];

    int result[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    int rc = matrix_to_square_form(&mat_a);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(mat_a.matrix[i][j], result[i][j]);

    matrix_free(&mat_a);
}
END_TEST

START_TEST(test_del_columns)
{
    matrix_t mat_a = { NULL, 0, 0 };
    mat_a.n = 3;
    mat_a.m = 4;
    matrix_alloc(&mat_a);
    int data[3][4] = {
        {1, 2, 3, -1},
        {4, 5, 6, 1},
        {7, 8, 9, 0},
    };

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 4; j++)
            mat_a.matrix[i][j] = data[i][j];

    int result[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    int rc = matrix_to_square_form(&mat_a);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(mat_a.matrix[i][j], result[i][j]);

    matrix_free(&mat_a);
}
END_TEST

Suite *matrix_to_square_form_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("matrix_to_square_form");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_del_rows);
    tcase_add_test(tc_pos, test_del_columns);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

#include "check_funcs.h"

/* -----negatives----- */

START_TEST(test_unsuitable_sizes)
{
    matrix_t mat_a = { NULL, 0, 0 }, mat_b = { NULL, 0, 0 }, tmp = { NULL, 0, 0 };
    mat_a.n = 3;
    mat_a.m = 3;
    matrix_alloc(&mat_a);
    int dataA[3][3] = {
        {1, 2, 1},
        {3, 4, 1},
        {5, 6, 1},
    };

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            mat_a.matrix[i][j] = dataA[i][j];

    mat_b.n = 2;
    mat_b.m = 3;
    matrix_alloc(&mat_b);
    int dataB[2][3] = {
        {1, 2, 3},
        {4, 5, 6},
    };

    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 3; j++)
            mat_b.matrix[i][j] = dataB[i][j];

    int rc = matrix_mul(&mat_a, &mat_b, &tmp);

    ck_assert_int_eq(rc, ERROR_INVALID_MATRIX_SIZES);

    matrix_free(&mat_a);
    matrix_free(&mat_b);
}
END_TEST

/* ------------------- */

/* -----positives----- */
START_TEST(test_simple_mul_3x3)
{
    matrix_t mat_a = { NULL, 0, 0 }, tmp = { NULL, 0, 0 };
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

    int rc = matrix_mul(&mat_a, &mat_a, &tmp);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(tmp.matrix[i][j], result[i][j]);
    
    matrix_free(&mat_a);
    matrix_free(&tmp);
}
END_TEST

START_TEST(test_simple_mul_1x1)
{
    matrix_t mat_a = { NULL, 0, 0 }, tmp = { NULL, 0, 0 };
    mat_a.n = 1;
    mat_a.m = 1;
    matrix_alloc(&mat_a);
    int data[1][1] = {
        {1},
    };

    for (size_t i = 0; i < 1; i++)
        for (size_t j = 0; j < 1; j++)
            mat_a.matrix[i][j] = data[i][j];

    int result[1][1] = {
        {1},
    };

    int rc = matrix_mul(&mat_a, &mat_a, &tmp);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < 1; i++)
        for (size_t j = 0; j < 1; j++)
            ck_assert_int_eq(tmp.matrix[i][j], result[i][j]);

    matrix_free(&mat_a);
    matrix_free(&tmp);
}
END_TEST

START_TEST(test_mul_differents_sizes)
{
    matrix_t mat_a = { NULL, 0, 0 }, mat_b = { NULL, 0, 0 }, tmp = { NULL, 0, 0 };
    mat_a.n = 3;
    mat_a.m = 2;
    matrix_alloc(&mat_a);
    int dataA[3][2] = {
        {1, 2},
        {3, 4},
        {5, 6},
    };

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 2; j++)
            mat_a.matrix[i][j] = dataA[i][j];

    mat_b.n = 2;
    mat_b.m = 3;
    matrix_alloc(&mat_b);
    int dataB[2][3] = {
        {1, 2, 3},
        {4, 5, 6},
    };

    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 3; j++)
            mat_b.matrix[i][j] = dataB[i][j];

    int result[3][3] = {
        {9, 12, 15},
        {19, 26, 33},
        {29, 40, 51},
    };

    
    int rc = matrix_mul(&mat_a, &mat_b, &tmp);

    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(tmp.matrix[i][j], result[i][j]);

    matrix_free(&mat_a);
    matrix_free(&mat_b);
    matrix_free(&tmp);
}
END_TEST

/* ------------------- */

Suite *matrix_mul_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("matrix_mul");

    tc_neg = tcase_create("negatives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_neg, test_unsuitable_sizes);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_simple_mul_3x3);
    tcase_add_test(tc_pos, test_simple_mul_1x1);
    tcase_add_test(tc_pos, test_mul_differents_sizes);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

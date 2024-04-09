#include "check_funcs.h"

/* -----negatives----- */

START_TEST(test_no_elements)
{
    size_t nmemb = 0;
    int *a = calloc(nmemb, sizeof(int));
    int rc;
    int *pb_new = NULL;
    int *pe_new = NULL;

    rc = key(a, a + nmemb, &pb_new, &pe_new);
    ck_assert_int_eq(rc, ERROR_NO_ELEMETS);
    free(a);
    free(pb_new);
}
END_TEST

START_TEST(test_after_key_no_elements)
{
    int a[] = {2};
    int rc;
    int *pb_new = NULL;
    int *pe_new = NULL;

    size_t nmemb = sizeof(a) / sizeof(a[0]);

    rc = key(a, a + nmemb, &pb_new, &pe_new);
    ck_assert_int_eq(rc, ERROR_EMPTY_RESULT);
    free(pb_new);
}
END_TEST

/* ------------------- */

/* -----positives----- */
START_TEST(test_simple_filter)
{
    int a[] = {1, 2, 3, 4, 5, 6};
    int result[] = {4, 5, 6};
    int rc;
    int *pb_new = NULL;
    int *pe_new = NULL;

    size_t nmemb = sizeof(a) / sizeof(a[0]);

    rc = key(a, a + nmemb, &pb_new, &pe_new);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(sizeof(result) / sizeof(result[0]), pe_new - pb_new);
    int *p = pb_new;
    for (size_t i = 0; p < pe_new; i++, p++)
        ck_assert_int_eq(*p, result[i]);
    free(pb_new);
}

START_TEST(test_simple_filter_many_elements)
{
    int a[] = {16, 21, 13, 10, 2, 1, 4, 11, 5, 6, 123, 9, 45};
    int result[] = {21, 123, 45};
    int rc;
    int *pb_new = NULL;
    int *pe_new = NULL;

    size_t nmemb = sizeof(a) / sizeof(a[0]);

    rc = key(a, a + nmemb, &pb_new, &pe_new);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(sizeof(result) / sizeof(result[0]), pe_new - pb_new);
    int *p = pb_new;
    for (size_t i = 0; p < pe_new; i++, p++)
        ck_assert_int_eq(*p, result[i]);
    free(pb_new);
}

START_TEST(test_one_element_after_filter)
{
    int a[] = {1, 2, 5};
    int result[] = {5};
    int rc;
    int *pb_new = NULL;
    int *pe_new = NULL;

    size_t nmemb = sizeof(a) / sizeof(a[0]);

    rc = key(a, a + nmemb, &pb_new, &pe_new);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(sizeof(result) / sizeof(result[0]), pe_new - pb_new);
    int *p = pb_new;
    for (size_t i = 0; p < pe_new; i++, p++)
        ck_assert_int_eq(*p, result[i]);
    free(pb_new);
}

END_TEST

/* ------------------- */

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции key
    s = suite_create("key");

    // Создадим тестовый случай из функций-тестов, которые проверяют разного
    // рода ошибочные ситуации при вызове key
    tc_neg = tcase_create("negatives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_neg, test_no_elements);
    tcase_add_test(tc_neg, test_after_key_no_elements);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // key для корректных параметров
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_simple_filter);
    tcase_add_test(tc_pos, test_simple_filter_many_elements);
    tcase_add_test(tc_pos, test_one_element_after_filter);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

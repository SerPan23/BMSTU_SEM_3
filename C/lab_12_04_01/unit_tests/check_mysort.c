#include "check_funcs.h"

/* -----positives----- */
START_TEST(test_sorted_arr)
{
    int a[] = {1, 2, 3, 4, 5, 6};
    int result[] = {1, 2, 3, 4, 5, 6};

    size_t nmemb = sizeof(a) / sizeof(a[0]);

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp_int);
    ck_assert_int_eq(sizeof(result) / sizeof(result[0]), nmemb);
    for (size_t i = 0; i < nmemb; i++)
        ck_assert_int_eq(a[i], result[i]);
}
END_TEST

START_TEST(test_rev_sorted_arr)
{
    int a[] = {6, 5, 4, 3, 2, 1};
    int result[] = {1, 2, 3, 4, 5, 6};

    size_t nmemb = sizeof(a) / sizeof(a[0]);

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp_int);
    ck_assert_int_eq(sizeof(result) / sizeof(result[0]), nmemb);
    for (size_t i = 0; i < nmemb; i++)
        ck_assert_int_eq(a[i], result[i]);
}
END_TEST

START_TEST(test_simple_arr)
{
    int a[] = {6, 3, 2, 4, 5, 1};
    int result[] = {1, 2, 3, 4, 5, 6};

    size_t nmemb = sizeof(a) / sizeof(a[0]);

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp_int);
    ck_assert_int_eq(sizeof(result) / sizeof(result[0]), nmemb);
    for (size_t i = 0; i < nmemb; i++)
        ck_assert_int_eq(a[i], result[i]);
}
END_TEST

START_TEST(test_simple_with_same_els_arr)
{
    int a[] = {1, 6, 3, 2, 4, 3, 5, 1};
    int result[] = {1, 1, 2, 3, 3, 4, 5, 6};

    size_t nmemb = sizeof(a) / sizeof(a[0]);

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp_int);
    ck_assert_int_eq(sizeof(result) / sizeof(result[0]), nmemb);
    for (size_t i = 0; i < nmemb; i++)
        ck_assert_int_eq(a[i], result[i]);
}
END_TEST

START_TEST(test_one_element)
{
    int a[] = {1};
    int result[] = {1};

    size_t nmemb = sizeof(a) / sizeof(a[0]);

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp_int);
    ck_assert_int_eq(sizeof(result) / sizeof(result[0]), nmemb);
    for (size_t i = 0; i < nmemb; i++)
        ck_assert_int_eq(a[i], result[i]);
}
END_TEST

/* ------------------- */

Suite *my_sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции my_sort
    s = suite_create("my_sort");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // my_sort для корректных параметров
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_sorted_arr);
    tcase_add_test(tc_pos, test_rev_sorted_arr);
    tcase_add_test(tc_pos, test_simple_arr);
    tcase_add_test(tc_pos, test_simple_with_same_els_arr);
    tcase_add_test(tc_pos, test_one_element);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

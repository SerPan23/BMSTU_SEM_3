#include "check_funcs.h"

/* -----negatives----- */

START_TEST(test_no_mem)
{
    size_t nmemb = 0;

    int rc;
    rc = arr_fill_fibonacci(NULL, nmemb, 10);

    ck_assert_int_eq(rc, 10);
}
END_TEST

START_TEST(test_no_elements)
{
    size_t nmemb = 0;
    int *a = calloc(nmemb, sizeof(int));
    int rc;
    rc = arr_fill_fibonacci(a, nmemb, 5);

    ck_assert_int_eq(rc, 5);
}
END_TEST

/* ------------------- */

/* -----positives----- */
START_TEST(test_fibonacci_0)
{
    int n = 0;
    size_t nmemb = 1;
    int *a = calloc(nmemb, sizeof(int));
    int result[] = {0, 1, 1, 2, 3};
    int rc;

    rc = arr_fill_fibonacci(a, nmemb, n);

    ck_assert_int_eq(rc, n);

    for (int i = 0; i < rc; i++)
        ck_assert_int_eq(a[i], result[i]);
}

START_TEST(test_fibonacci_1)
{
    int n = 1;
    size_t nmemb = 1;
    int *a = calloc(nmemb, sizeof(int));
    int result[] = {0, 1, 1, 2, 3};
    int rc;

    rc = arr_fill_fibonacci(a, nmemb, n);

    ck_assert_int_eq(rc, n);

    for (int i = 0; i < rc; i++)
        ck_assert_int_eq(a[i], result[i]);
}

START_TEST(test_fibonacci_5)
{
    int n = 5;
    size_t nmemb = 5;
    int *a = calloc(nmemb, sizeof(int));
    int result[] = {0, 1, 1, 2, 3};
    int rc;

    rc = arr_fill_fibonacci(a, nmemb, n);

    ck_assert_int_eq(rc, n);

    for (int i = 0; i < rc; i++)
        ck_assert_int_eq(a[i], result[i]);
}


/* ------------------- */

Suite *fibonacci_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("fibonacci");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_no_mem);
    tcase_add_test(tc_neg, test_no_elements);


    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_fibonacci_0);
    tcase_add_test(tc_pos, test_fibonacci_1);
    tcase_add_test(tc_pos, test_fibonacci_5);

    suite_add_tcase(s, tc_pos);

    return s;
}

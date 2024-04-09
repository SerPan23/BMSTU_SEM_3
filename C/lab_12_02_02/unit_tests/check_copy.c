#include "check_funcs.h"

/* -----negatives----- */

START_TEST(test_no_dst_len)
{
    int a[] = {0, 1, 1, 2, 3};
    size_t nmemb = sizeof(a) / sizeof(a[0]);

    int rc;
    rc = arr_copy_unique(a, nmemb, NULL, 0);

    ck_assert_int_eq(rc, 4);
}
END_TEST

/* ------------------- */

/* -----positives----- */
START_TEST(test_copy_one_el)
{
    int a[] = {0};
    size_t nmemb = sizeof(a) / sizeof(a[0]);
    size_t unique_count = 1;
    int result[] = {0};

    int rc;

    int res[unique_count];
    rc = arr_copy_unique(a, nmemb, res, sizeof(res) / sizeof(res[0]));

    ck_assert_int_eq(rc, unique_count);

    for (int i = 0; i < rc; i++)
        ck_assert_int_eq(result[i], result[i]);
}

START_TEST(test_copy_one_unique)
{
    int a[] = {1, 1};
    size_t nmemb = sizeof(a) / sizeof(a[0]);
    size_t unique_count = 1;
    int result[] = {1};

    int rc;

    int res[unique_count];
    rc = arr_copy_unique(a, nmemb, res, sizeof(res) / sizeof(res[0]));

    ck_assert_int_eq(rc, unique_count);

    for (int i = 0; i < rc; i++)
        ck_assert_int_eq(result[i], result[i]);
}

START_TEST(test_simple_copy)
{
    int a[] = {0, 1, 1, 2, 3, 3};
    size_t nmemb = sizeof(a) / sizeof(a[0]);
    size_t unique_count = 4;
    int result[] = {0, 1, 2, 3};

    int rc;

    int res[unique_count];
    rc = arr_copy_unique(a, nmemb, res, sizeof(res) / sizeof(res[0]));

    ck_assert_int_eq(rc, unique_count);

    for (int i = 0; i < rc; i++)
        ck_assert_int_eq(result[i], result[i]);
}

/* ------------------- */

Suite *copy_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("copy");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_no_dst_len);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_copy_one_el);
    tcase_add_test(tc_pos, test_copy_one_unique);
    tcase_add_test(tc_pos, test_simple_copy);

    suite_add_tcase(s, tc_pos);

    return s;
}

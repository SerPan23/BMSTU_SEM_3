#include "check_funcs.h"

/* -----positives----- */

START_TEST(without_format)
{
    size_t size = 50;
    const char format[30] = "test";

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

START_TEST(double_persent)
{
    size_t size = 50;
    const char format[30] = "test %%";

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format);    

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

START_TEST(one_dec)
{
    size_t size = 50;
    const char format[30] = "test %d";
    int num = 123;

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format, num);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format, num);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

START_TEST(int_min)
{
    size_t size = 50;
    const char format[30] = "test %d";
    int num = INT32_MIN;

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format, num);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format, num);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

START_TEST(one_oct)
{
    size_t size = 50;
    const char format[30] = "test %o";
    int num = 123;

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format, num);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format, num);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

START_TEST(one_negative_oct)
{
    size_t size = 50;
    const char format[30] = "test %o";
    int num = -123;

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format, num);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format, num);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

START_TEST(three_dec)
{
    size_t size = 50;
    const char format[30] = "Num1: %d Num2: %d Num3: %d";
    int num1 = 123, num2 = -14, num3 = 6;

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format, num1, num2, num3);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format, num1, num2, num3);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

START_TEST(three_oct)
{
    size_t size = 50;
    const char format[30] = "Num1: %o Num2: %o Num3: %o";
    int num1 = 123, num2 = 14, num3 = 6;

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format, num1, num2, num3);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format, num1, num2, num3);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

START_TEST(all_specif)
{
    size_t size = 90;
    const char format[50] = "Num1: %o Num2: %d Num3: %o Num4: %d";
    int num1 = 123, num2 = -134, num3 = 6, num4 = 0;

    char buf_1[100] = "";
    int rc_1 = my_snprintf(buf_1, size, format, num1, num2, num3, num4);

    char buf_2[100] = "";
    int rc_2 = snprintf(buf_2, size, format, num1, num2, num3, num4);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

/* ------------------- */

/* -----negatives----- */
START_TEST(zero_size)
{
    size_t size = 0;
    const char format[30] = "Num1: %o Num2: %o Num3: %o";
    int num1 = 123, num2 = 14, num3 = 6;

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format, num1, num2, num3);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format, num1, num2, num3);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

START_TEST(cutoff_size)
{
    size_t size = 10;
    const char format[30] = "Num1: %d Num2: %o Num3: %o";
    int num1 = 12300, num2 = 14, num3 = 6;

    char buf_1[60] = "";
    int rc_1 = my_snprintf(buf_1, size, format, num1, num2, num3);

    char buf_2[60] = "";
    int rc_2 = snprintf(buf_2, size, format, num1, num2, num3);

    ck_assert_int_eq(rc_1, rc_2);
    ck_assert_int_eq(strcmp(buf_1, buf_2), 0);
}
END_TEST

/* ------------------- */

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("my_snprintf");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, without_format);
    tcase_add_test(tc_pos, double_persent);
    tcase_add_test(tc_pos, one_dec);
    tcase_add_test(tc_pos, int_min);
    tcase_add_test(tc_pos, one_oct);
    tcase_add_test(tc_pos, one_negative_oct);
    tcase_add_test(tc_pos, three_dec);
    tcase_add_test(tc_pos, three_oct);
    tcase_add_test(tc_pos, all_specif);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    // Создадим тестовый случай из функций-тестов, которые проверяют разного
    // рода ошибочные ситуации
    tc_neg = tcase_create("negatives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_neg, zero_size);
    tcase_add_test(tc_neg, cutoff_size);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    return s;
}END_TEST
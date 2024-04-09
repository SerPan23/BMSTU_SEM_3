#include "check_funcs.h"

/* -----positives----- */
START_TEST(simple_cmp_gt)
{
    item_t *t1 = NULL, *t2 = NULL;

    double t1_w = 2, t1_v = 1;

    double t2_w = 1, t2_v = 1;

    item_fill(&t1, NULL, &t1_w, &t1_v);
    item_fill(&t2, NULL, &t2_w, &t2_v);


    ck_assert_int_eq(item_cmp_by_density(t1, t2), 1);
    item_free(t1);
    item_free(t2);
}
END_TEST

START_TEST(simple_cmp_lt)
{
    item_t *t1 = NULL, *t2 = NULL;

    double t1_w = 2, t1_v = 1;

    double t2_w = 30, t2_v = 4;

    item_fill(&t1, NULL, &t1_w, &t1_v);
    item_fill(&t2, NULL, &t2_w, &t2_v);

    ck_assert_int_eq(item_cmp_by_density(t1, t2), -1);
    item_free(t1);
    item_free(t2);
}
END_TEST

START_TEST(simple_cmp_eq)
{
    item_t *t1 = NULL, *t2 = NULL;

    double t1_w = 1, t1_v = 1;
    
    double t2_w = 1, t2_v = 1;

    item_fill(&t1, NULL, &t1_w, &t1_v);
    item_fill(&t2, NULL, &t2_w, &t2_v);

    ck_assert_int_eq(item_cmp_by_density(t1, t2), 0);
    item_free(t1);
    item_free(t2);
}
END_TEST

/* ------------------- */

Suite *item_cmp_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("item_cmp");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, simple_cmp_gt);
    tcase_add_test(tc_pos, simple_cmp_lt);
    tcase_add_test(tc_pos, simple_cmp_eq);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

#include "check_funcs.h"

/* -----positives----- */
START_TEST(sorted_arr)
{

    items_t items = {NULL, 0, 0};
    items_alloc(&items, 1);

    double data[3][2] = {
        {1, 1},
        {5, 1},
        {10, 1},
    };

    item_t *t1 = NULL;

    for (size_t i = 0; i < 3; i++)
    {
        item_fill(&t1, NULL, &data[i][0], &data[i][1]);

        items_append(&items, t1);

        t1 = NULL;
    }

    sort_by_density(&items);

    double res_data[3][2] = {
        {1, 1},
        {5, 1},
        {10, 1},
    };

    for (size_t i = 0; i < 3; i++)
    {
        ck_assert_double_eq(items.data[i]->weight, res_data[i][0]);
        ck_assert_double_eq(items.data[i]->volume, res_data[i][1]);
    }

    items_free(&items);
}
END_TEST

START_TEST(rev_sorted_arr)
{

    items_t items = {NULL, 0, 0};
    items_alloc(&items, 1);

    double data[3][2] = {
        {10, 1},
        {5, 1},
        {1, 1},
    };

    item_t *t1 = NULL;

    for (size_t i = 0; i < 3; i++)
    {
        item_fill(&t1, NULL, &data[i][0], &data[i][1]);

        items_append(&items, t1);

        t1 = NULL;
    }

    sort_by_density(&items);

    double res_data[3][2] = {
        {1, 1},
        {5, 1},
        {10, 1},
    };

    for (size_t i = 0; i < 3; i++)
    {
        ck_assert_double_eq(items.data[i]->weight, res_data[i][0]);
        ck_assert_double_eq(items.data[i]->volume, res_data[i][1]);
    }

    items_free(&items);
}
END_TEST

START_TEST(simple_sort)
{

    items_t items = {NULL, 0, 0};
    items_alloc(&items, 1);

    double data[4][2] = {
        {5, 1},
        {10, 1},
        {1, 1},
        {3, 1},
    };

    item_t *t1 = NULL;

    for (size_t i = 0; i < 4; i++)
    {
        item_fill(&t1, NULL, &data[i][0], &data[i][1]);

        items_append(&items, t1);

        t1 = NULL;
    }

    sort_by_density(&items);

    double res_data[4][2] = {
        {1, 1},
        {3, 1},
        {5, 1},
        {10, 1},
    };

    for (size_t i = 0; i < 4; i++)
    {
        ck_assert_double_eq(items.data[i]->weight, res_data[i][0]);
        ck_assert_double_eq(items.data[i]->volume, res_data[i][1]);
    }

    items_free(&items);
}
END_TEST
/* ------------------- */

Suite *items_sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("items_sort");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, sorted_arr);
    tcase_add_test(tc_pos, rev_sorted_arr);
    tcase_add_test(tc_pos, simple_sort);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

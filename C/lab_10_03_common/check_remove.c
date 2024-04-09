#include "check_funcs.h"
#include <string.h>

/* -----positives----- */
START_TEST(one_el)
{
    assoc_array_t arr = assoc_array_create();

    char *data[1] = {
        "test",
    };

    int n = 1;

    for (int i = 0; i < n; i++)
    {
        assoc_array_error_t rc = assoc_array_insert(arr, data[i], i);

        ck_assert_int_eq(rc == ASSOC_ARRAY_OK, 1);
    }

    assoc_array_error_t rc = assoc_array_remove(arr, data[0]);
    ck_assert_int_eq(rc == ASSOC_ARRAY_OK, 1);

    assoc_array_destroy(&arr);
}

START_TEST(simple_test)
{
    assoc_array_t arr = assoc_array_create();

    char *data[5] = {
        "test",
        "2",
        "3",
        "f",
        "5",
    };

    int n = 5;

    for (int i = 0; i < n; i++)
    {
        assoc_array_error_t rc = assoc_array_insert(arr, data[i], i);

        ck_assert_int_eq(rc == ASSOC_ARRAY_OK, 1);
    }

    assoc_array_error_t rc = assoc_array_remove(arr, data[4]);
    ck_assert_int_eq(rc == ASSOC_ARRAY_OK, 1);

    assoc_array_destroy(&arr);
}
/* ------------------- */

Suite *remove_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции
    s = suite_create("remove");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, one_el);
    tcase_add_test(tc_pos, simple_test);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

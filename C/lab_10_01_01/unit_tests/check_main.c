#include "check_funcs.h"

int main(void)
{
    int no_failed = 0;
    Suite *list_find_s, *list_pop_front_s, *list_pop_back_s, *list_append_s, *list_remove_dupl_s, *list_sort_s;
    SRunner *runner;

    list_find_s = list_find_suite();
    runner = srunner_create(list_find_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    list_pop_front_s = list_pop_front_suite();
    runner = srunner_create(list_pop_front_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    list_pop_back_s = list_pop_back_suite();
    runner = srunner_create(list_pop_back_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    list_append_s = list_append_suite();
    runner = srunner_create(list_append_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    list_remove_dupl_s = list_remove_dupl_suite();
    runner = srunner_create(list_remove_dupl_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    list_sort_s = list_sort_suite();
    runner = srunner_create(list_sort_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#include "check_funcs.h"

int main(void)
{
    int no_failed = 0;
    Suite *item_cmp_s, *items_sort_s;
    SRunner *runner;

    item_cmp_s = item_cmp_suite();
    runner = srunner_create(item_cmp_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    items_sort_s = items_sort_suite();
    runner = srunner_create(items_sort_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

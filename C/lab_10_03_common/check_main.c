#include "check_funcs.h"

int main(void)
{
    int no_failed = 0;
    Suite *insert_s, *find_s, *remove_s, *clear_s, *each_s, *min_s, *max_s;
    SRunner *runner;

    insert_s = insert_suite();
    runner = srunner_create(insert_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    find_s = find_suite();
    runner = srunner_create(find_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    remove_s = remove_suite();
    runner = srunner_create(remove_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    clear_s = clear_suite();
    runner = srunner_create(clear_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    each_s = each_suite();
    runner = srunner_create(each_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    min_s = min_suite();
    runner = srunner_create(min_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    max_s = max_suite();
    runner = srunner_create(max_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

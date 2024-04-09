#include "check_funcs.h"

int main(void)
{
    int no_failed = 0;
    Suite *p_val_s, *p_ddx_s, *p_sum_s, *p_dvd_s;
    SRunner *runner;

    p_val_s = p_val_suite();
    runner = srunner_create(p_val_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    p_ddx_s = p_ddx_suite();
    runner = srunner_create(p_ddx_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    p_sum_s = p_sum_suite();
    runner = srunner_create(p_sum_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    p_dvd_s = p_dvd_suite();
    runner = srunner_create(p_dvd_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
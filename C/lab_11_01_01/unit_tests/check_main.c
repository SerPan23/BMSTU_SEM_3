#include "check_funcs.h"

int main(void)
{
    int no_failed = 0;
    Suite *my_snprintf_s;
    SRunner *runner;

    my_snprintf_s = my_snprintf_suite();
    runner = srunner_create(my_snprintf_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
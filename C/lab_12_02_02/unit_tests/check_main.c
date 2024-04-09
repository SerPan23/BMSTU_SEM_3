#include "check_funcs.h"

int main(void)
{
    int fib_no_failed = 0, copy_no_failed = 0;
    Suite *fs, *cs;
    SRunner *runner;

    fs = fibonacci_suite();
    // Для запуска тестов, всходящих в тестовый набор, нужно создать так называемый
    // "runner".
    runner = srunner_create(fs);

    // Вот таким образом запускаются все тесты. С помощью второго параметра (в данном случаев
    // CK_VERBOSE) можно детализировать вывод.
    srunner_run_all(runner, CK_VERBOSE);
    // После того, как все тесты будут выполнены, можно получить по ним дополнительную информацию,
    // например, вот так.
    fib_no_failed = srunner_ntests_failed(runner);
    // Перед завершением main "runner" нужно обязательно освободить.
    srunner_free(runner);

    cs = copy_suite();
    runner = srunner_create(cs);

    srunner_run_all(runner, CK_VERBOSE);

    copy_no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (fib_no_failed + copy_no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#include "check_funcs.h"

int main(void)
{
    int key_no_failed = 0, sort_no_failed = 0;
    Suite *ks, *ss;
    SRunner *runner;

    ks = key_suite();
    // Для запуска тестов, всходящих в тестовый набор, нужно создать так называемый
    // "runner".
    runner = srunner_create(ks);

    // Вот таким образом запускаются все тесты. С помощью второго параметра (в данном случаев
    // CK_VERBOSE) можно детализировать вывод.
    srunner_run_all(runner, CK_VERBOSE);
    // После того, как все тесты будут выполнены, можно получить по ним дополнительную информацию,
    // например, вот так.
    key_no_failed = srunner_ntests_failed(runner);
    // Перед завершением main "runner" нужно обязательно освободить.
    srunner_free(runner);

    ss = my_sort_suite();
    runner = srunner_create(ss);

    srunner_run_all(runner, CK_VERBOSE);

    sort_no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (key_no_failed + sort_no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

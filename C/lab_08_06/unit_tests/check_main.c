#include "check_funcs.h"

int main(void)
{
    int no_failed = 0;
    Suite *mul_s, *pow_s, *m_new_size_s, *make_square_s;
    SRunner *runner;

    mul_s = matrix_mul_suite();
    // Для запуска тестов, всходящих в тестовый набор, нужно создать так называемый
    // "runner".
    runner = srunner_create(mul_s);

    // Вот таким образом запускаются все тесты. С помощью второго параметра (в данном случаев
    // CK_VERBOSE) можно детализировать вывод.
    srunner_run_all(runner, CK_VERBOSE);
    // После того, как все тесты будут выполнены, можно получить по ним дополнительную информацию,
    // например, вот так.
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    pow_s = matrix_pow_suite();
    runner = srunner_create(pow_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    m_new_size_s = matrix_to_new_size_suite();
    runner = srunner_create(m_new_size_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    srunner_free(runner);

    make_square_s = matrix_to_square_form_suite();
    runner = srunner_create(make_square_s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);

    // Перед завершением main "runner" нужно обязательно освободить.
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

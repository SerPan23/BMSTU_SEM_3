#include "bignum.h"

#define MAX_FIRST_MANTISSA_LEN 35
#define MAX_SECOND_MANTISSA_LEN 40
#define MAX_RESULT_MANTISSA_LEN 40

#define MAX_RESULT_EXPONET_SIZE 99999

#define ERROR_FIRST_MANTISSA_LEN 10
#define ERROR_SECOND_MANTISSA_LEN 20
#define ERROR_RESULT_MANTISSA_LEN 30
#define ERROR_RESULT_EXPONET_SIZE 40

void debug_print(bignum_t *a)
{
    printf("\nDebug----------------------------\n");
    printf("is_neg: %d | mantissa_len: %zu | exp: %d\n",
           a->is_negative, a->mantissa_len, a->exponet);
    for (ptrdiff_t i = a->mantissa_len - 1; i >= 0; i--)
        printf("%d", a->mantissa[i]);
    printf("\n----------------------------\n");
    for (size_t i = 0; i < a->mantissa_len; i++)
        printf("%d", a->mantissa[i]);
    printf("\n----------------------------\n");
    printf("\n");
}

int main(void)
{

    printf("Программа осуществляет умножения двух действительных чисел.\n");
    bignum_t a;
    printf("Введите первое число в формате +-m.nЕ+-K, "
        "где суммарная длина мантиссы первого\nсомножителя (m+n) - до 35 значащих цифры, " 
        "порядок до 5 цифр."
        "\n----1----2----3----4----5----6----7\n");
    int rc = bignum_scan(&a);
    if (rc != EXIT_SUCCESS)
    {
        printf("ОШИБКА в сканирование числа a типа: %d\n", rc);
        return rc;
    }

    if (a.mantissa_len > MAX_FIRST_MANTISSA_LEN)
    {
        printf("ОШИБКА: мантисса первого числа слишком длинная\n");
        return ERROR_FIRST_MANTISSA_LEN;
    }

    bignum_t b;
    printf("Введите второе число в формате +-m.nЕ+-K, "
           "где суммарная длина мантиссы второго\nсомножителя (m+n) - до 40 значащих цифры, "
           "порядок до 5 цифр."
           "\n----1----2----3----4----5----6----7----8\n");
    rc = bignum_scan(&b);
    if (rc != EXIT_SUCCESS)
    {
        printf("ОШИБКА в сканирование числа b типа: %d\n", rc);
        return rc;
    }

    if (b.mantissa_len > MAX_SECOND_MANTISSA_LEN)
    {
        printf("ОШИБКА: мантисса второго числа слишком длинная\n");
        return ERROR_SECOND_MANTISSA_LEN;
    }

    //10
    //22
    // 0.0220E4
    //00000.01000

    //999
    //2
    //0.1998E4 - 0.2E4

    // debug_print(&a);
    // bignum_print(&a);
    // debug_print(&b);
    // bignum_print(&b);

    bignum_t res;
    bignum_mul(&a, &b, &res);

    if (res.mantissa_len > MAX_RESULT_MANTISSA_LEN)
    {
        printf("ОШИБКА: мантисса результата слишком длинная\n");
        return ERROR_RESULT_MANTISSA_LEN;
    }

    // printf("%d + %d = %d | %d\n", a.exponet, b.exponet, a.exponet + b.exponet, res.exponet);
    // debug_print(&res);
    // bignum_print(&res);
    if (abs(res.exponet) > MAX_RESULT_EXPONET_SIZE)
    {
        printf("ОШИБКА: экспонента результата слишком большая\n");
        return ERROR_RESULT_EXPONET_SIZE;
    }

    // debug_print(&res);
    printf("Результат: ");
    bignum_print(&res);

    printf("\n\n\n---------\n");

    return EXIT_SUCCESS;
}

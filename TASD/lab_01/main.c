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
    bignum_t a;
    printf("Enter first num:\n----1----2----3----4----5----6----7\n");
    int rc = bignum_scan(&a);
    if (rc != EXIT_SUCCESS)
    {
        printf("Error type in a scan: %d\n", rc);
        return rc;
    }

    if (a.mantissa_len > MAX_FIRST_MANTISSA_LEN)
        return ERROR_FIRST_MANTISSA_LEN;

    bignum_t b;
    printf("Enter second num:\n----1----2----3----4----5----6----7----8\n");
    rc = bignum_scan(&b);
    if (rc != EXIT_SUCCESS)
    {
        printf("Error type in b scan: %d\n", rc);
        return rc;
    }

    if (b.mantissa_len > MAX_SECOND_MANTISSA_LEN)
        return ERROR_SECOND_MANTISSA_LEN;

    //10
    //22
    // 0.0220E4
    //00000.01000

    // debug_print(&a);
    bignum_print(&a);
    // debug_print(&b);
    bignum_print(&b);

    bignum_t res;

    bignum_mul(&a, &b, &res);

    if (res.mantissa_len > MAX_RESULT_MANTISSA_LEN)
        return ERROR_RESULT_MANTISSA_LEN;

    if (res.mantissa_len > MAX_RESULT_EXPONET_SIZE)
        return ERROR_RESULT_EXPONET_SIZE;

    // debug_print(&res);
    bignum_print(&res);

    return EXIT_SUCCESS;
}

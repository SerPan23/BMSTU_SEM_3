#include "bignum.h"

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
    printf("Enter first num:\n----|----|----|----|----|----|----|\n");
    int rc = bignum_scan(&a);
    if (rc != EXIT_SUCCESS)
    {
        printf("Error type in a scan: %d\n", rc);
        return rc;
    }

    bignum_t b;
    printf("Enter second num:\n----|----|----|----|----|----|----|----|\n");
    rc = bignum_scan(&b);
    if (rc != EXIT_SUCCESS)
    {
        printf("Error type in b scan: %d\n", rc);
        return rc;
    }


    debug_print(&a);
    bignum_print(&a);
    debug_print(&b);
    bignum_print(&b);

    bignum_t res;

    bignum_mul(&a, &b, &res);

    debug_print(&res);
    bignum_print(&res);

    return EXIT_SUCCESS;
}

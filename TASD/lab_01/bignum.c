#include "bignum.h"

int bignum_print(bignum_t *a)
{
    char s[MAX_STR_LEN + 1];
    size_t l;

    bignum_to_str(s, &l, a);
    printf("%s\n", s);
    return EXIT_SUCCESS;
}
int bignum_scan(bignum_t *a)
{
   char tmp[MAX_STR_LEN + 1];
   if (fgets(tmp, MAX_STR_LEN + 1, stdin) == NULL)
       return ERROR_EMPTY_INPUT;

   tmp[strcspn(tmp, "\n")] = '\0';
   if (strlen(tmp) > MAX_STR_LEN || strlen(tmp) == 0)
       return ERROR_NUM_LEN;

   int rc = str_to_bignum(tmp, strlen(tmp), a);

   return rc;
}

int str_to_bignum(char s[], size_t len, bignum_t *a)
{
    a->is_negative = 0;
    a->mantissa_len = 0;
    a->exponet = 0;
    int is_dot = 0, is_E = 0;
    for (ptrdiff_t i = len - 1; i >= 0; i--)
    {
        if ( ((s[i] == '-' || s[i] == '+') && s[i - 1] == 'E' && !is_E) || (s[i] == 'E' && !is_E))
        {
            if (a->mantissa_len > 5)
                return ERROR_EXPONET_SIZE;
            else
            {
                int tmp = 0;
                for (ptrdiff_t j = a->mantissa_len - 1; j >= 0; j--)
                {
                    tmp *= 10;
                    tmp += a->mantissa[j];
                }
                a->exponet = tmp;
                if (s[i] == '-')
                    a->exponet *= -1;
                a->mantissa_len = 0;
            }
            is_E = 1;
            if (s[i] == '-' || s[i] == '+')
                i--;
        }
        else if (i == 0 && !isdigit(s[i]))
        {
            if (s[i] == '-')
                a->is_negative = 1;
            else if (s[i] != '+' && !isdigit(s[i]))
                return ERROR_INVALID_SYMBOL;
        }
        else if (isdigit(s[i]))
        {
            int digit = (int)(s[i] - '0');
            if (digit == 0 && (i == 0 || (i == 1 && (s[i - 1] == '-' || s[i - 1] == '+'))))
                continue;
            a->mantissa[a->mantissa_len++] = digit;
            if (is_dot)
                a->exponet++;
        }
        else if (s[i] == '.')
        {
            if (!is_dot)
                is_dot = 1;
            else
                return ERROR_INVALID_SYMBOL;
        }
        else
            return ERROR_INVALID_SYMBOL;
    }
    if (!is_dot)
         a->exponet += a->mantissa_len;
    return EXIT_SUCCESS;
}
int bignum_to_str(char s[], size_t *len, bignum_t *a)
{
    char tmp[MAX_STR_LEN + 1];
    int offset = 0;
    if (a->is_negative)
    {
        tmp[0] = '-';
        tmp[1] = '0';
        tmp[2] = '.';
        offset = 3;
    }
    else
    {
        tmp[0] = '0';
        tmp[1] = '.';
        offset = 2;
    }
    for (ptrdiff_t i = a->mantissa_len - 1; i >= 0; i--)
        offset += snprintf(tmp + offset, MAX_STR_LEN + 1 - offset, "%d", a->mantissa[i]);

    snprintf(tmp + offset, MAX_STR_LEN + 1 - offset, "E%d", a->exponet);
    strcpy(s, tmp);
    *len = strlen(s);
    return EXIT_SUCCESS;
}

int bignum_mul(bignum_t *a, bignum_t *b, bignum_t *result)
{
    int tmp[MAX_MANTISSA_LEN + 1];
    for (size_t i = 0; i < MAX_MANTISSA_LEN + 1; i++)
        tmp[i] = 0;

    result->exponet = a->exponet + b->exponet;
    result->is_negative = a->is_negative * b->is_negative;

    size_t i, j;
    for (i = 0; i < b->mantissa_len; i++)
        for (j = 0; j < a->mantissa_len; j++)
            tmp[j + i] += a->mantissa[j] * b->mantissa[i];
    int t = 0;
    size_t k;
    result->mantissa_len = i + j;
    for (k = 0; k < result->mantissa_len - 1; k++)
    {
        result->mantissa[k] = tmp[k] % 10 + t;
        t = tmp[k] / 10;
    }
    result->mantissa[k + 1] = t;
    return EXIT_SUCCESS;
}

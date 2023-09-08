#include "bignum.h"

int normalize_zeros(bignum_t *a)
{
    ptrdiff_t start_ind = a->mantissa_len - 1;
    for (ptrdiff_t i = start_ind; i >= 0; i--)
        if (a->mantissa[i] == 0)
        {
            a->mantissa_len--;
            a->exponet--;
        }
    return EXIT_SUCCESS;
}

int bignum_print(bignum_t *a)
{
    int rc = normalize_zeros(a);
    if (rc != EXIT_SUCCESS)
        return rc;
    
    char s[MAX_STR_LEN + 1];
    size_t l;

    rc = bignum_to_str(s, &l, a);
    if (rc != EXIT_SUCCESS)
        return rc;
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

int find_exponet(char str[], size_t len, int32_t *exponet, ptrdiff_t *e_ind)
{
    char *p;
    p = strstr(str, "E");
    if (p != NULL)
    {
        *e_ind = p - str;
        ptrdiff_t pt = *e_ind;

        int is_sign = 0;
        if (str[*e_ind + 1] == '-' || str[*e_ind + 1] == '+')
            is_sign = 1;
        
        if ((len - 1 - (*e_ind) > 5) || (is_sign && (len - 1 - (*e_ind) > 6)))
            return ERROR_EXPONET_SIZE;
        
        if (is_sign)
            pt++;

        int tmp = 0;
        for (size_t i = pt + 1; i < len; i++)
        {
            if (!isdigit(str[i]))
                return ERROR_INVALID_SYMBOL;
            tmp *= 10;
            tmp += (int)(str[i] - '0');
        }
        *exponet = tmp;
        if (str[*e_ind + 1] == '-')
            *exponet *= -1;
    }
    return EXIT_SUCCESS;
}

int find_no_zero_digit(char str[], size_t len, ptrdiff_t *no_0_ind)
{
    for (size_t i = 0; i < len; i++)
    {
        if (isdigit(str[i]) && str[i] != '0')
        {
            *no_0_ind = i;
            break;
        }
    }
    return EXIT_SUCCESS;
}

int find_dot(char str[], size_t len, ptrdiff_t *dot_ind)
{
    for (size_t i = 0; i < len; i++)
    {
         if (str[i] == '.')
        {
            *dot_ind = i;
            break;
        }
    }
    return EXIT_SUCCESS;
}

int str_to_bignum(char s[], size_t len, bignum_t *a)
{
    a->is_negative = 0;
    a->mantissa_len = 0;
    a->exponet = 0;

    ptrdiff_t e_ind = len, no_0_ind = 0, dot_ind = -1;

    int rc = find_exponet(s, len, &(a->exponet), &e_ind);

    if (rc != EXIT_SUCCESS)
        return rc;

    rc = find_no_zero_digit(s, len, &no_0_ind);

    if (rc != EXIT_SUCCESS)
        return rc;

    rc = find_dot(s, len, &dot_ind);

    if (rc != EXIT_SUCCESS)
        return rc;

    int is_start_num = 0;

    for (ptrdiff_t i = e_ind - 1; i >= 0; i--)
    {   
        if (i == 0 && !isdigit(s[i]))
        {
            if (s[i] == '-')
                a->is_negative = 1;
            else if (s[i] != '+' && !isdigit(s[i]))
                return ERROR_INVALID_SYMBOL;
        }
        else if (isdigit(s[i]))
        {
            if (i >= no_0_ind)
            {    
                int digit = (int)(s[i] - '0');
                // if (digit == 0 && (i == 0 || (i == 1 && (s[i - 1] == '-' || s[i - 1] == '+'))))
                //     continue;

                if (!is_start_num)
                {
                    if (digit)
                        is_start_num = 1;
                }

                if (is_start_num)
                    a->mantissa[a->mantissa_len++] = digit;
                if ((dot_ind != -1 && i < dot_ind) || dot_ind == -1)
                    a->exponet++;
            }
        }
        else if (s[i] == '.')
        {
            if (dot_ind != -1 && i != dot_ind)
                return ERROR_INVALID_SYMBOL;
            else
                continue;
        }
        else
            return ERROR_INVALID_SYMBOL;
    }
    // if (dot_ind == -1)
    //     a->exponet += a->mantissa_len;
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
    result->is_negative = (a->is_negative + b->is_negative) % 2;

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

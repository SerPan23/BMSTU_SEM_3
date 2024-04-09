#include "my_string.h"

int int_to_str(int num, int base, char *str, size_t *len, size_t max_len)
{
    int is_neg = num < 0 ? 1 : 0;
    char int_buf[MAX_INT_LEN];
    size_t buf_len = 0;

    do
    {
        int tmp = (num % base);
        if (is_neg)
            tmp *= -1;
        int_buf[buf_len++] = tmp + '0';
        num /= base;
    } while (buf_len < MAX_INT_LEN && num);

    if (is_neg)
        int_buf[buf_len++] = '-';

    
    if (max_len)
        for (size_t i = 0; i < buf_len && (*len) + i < max_len - 1; i++)
            str[(*len) + i] = int_buf[buf_len - 1 - i];

    *len += buf_len;

    if (*len > max_len)
        return ERROR_WRONG_STR_LEN;

    str[*len] = '\0';

    return EXIT_SUCCESS;
}

int int_to_oct_to_str(unsigned int num, char *str, size_t *len, size_t max_len)
{
    char int_buf[MAX_INT_LEN];
    size_t buf_len = 0;

    do
    {
        int tmp = (num % 8);
        int_buf[buf_len++] = tmp + '0';
        num /= 8;
    } while (buf_len < MAX_INT_LEN && num);

    if (max_len)
        for (size_t i = 0; i < buf_len && (*len) + i < max_len - 1; i++)
            str[(*len) + i] = int_buf[buf_len - 1 - i];

    *len += buf_len;

    if (*len > max_len)
        return ERROR_WRONG_STR_LEN;

    str[*len] = '\0';

    return EXIT_SUCCESS;
}

int parse_arg(const char *restrict format, size_t *ind, char *buf, size_t *len, size_t max_len, va_list args)
{
    if (*ind > my_strlen(format))
        return ERROR_PARSE_ARG;

    switch (format[*ind])
    {
        case 'd':
            int_to_str(va_arg(args, int), 10, buf, len, max_len);
            break;
        case 'o':
            int_to_oct_to_str(va_arg(args, int), buf, len, max_len);
            break;
        case '%':
            buf[(*len)++] = '%';
            // *ind = format[*ind] != '%' ? (*ind) - 1 : *ind;
            break;
        default:
            return ERROR_PARSE_ARG;
    }
    return EXIT_SUCCESS;
}

size_t my_strlen(const char *s)
{
    size_t len = 0;

    while (s[len] != '\0')
        len++;

    return len;
}

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    va_list args;
    va_start(args, format);
    size_t len = 0;
    size_t i = 0, format_len = my_strlen(format);

    while (i <= format_len)
    {
        if (format[i] == '%')
        {
            i++;
            int rc = parse_arg(format, &i, s, &len, n, args);
            if (rc != EXIT_SUCCESS)
            {
                if (len < n)
                    s[len] = '\0';
                else if (n > 0)
                    s[n - 1] = '\0';
                va_end(args);
                return -1;
            }
        }
        else
        {
            if (len < n)
                s[len++] = format[i];
            else
                len++;
        }

        i++;
    } 

    if (len < n)
        s[len] = '\0';
    else if (n > 0)
        s[n - 1] = '\0';

    va_end(args);

    return len - 1;
}
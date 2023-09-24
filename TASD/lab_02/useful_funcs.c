#include "useful_funcs.h"

int read_string(char *str, size_t *len, size_t max_len, FILE *input)
{
    char tmp[max_len + 2];

    if (fgets(tmp, max_len + 2, input) == NULL)
        return ERROR_EMPTY_INPUT;

    tmp[strcspn(tmp, "\n")] = '\0';

    if (strlen(tmp) && strlen(tmp) > max_len)
        return ERROR_STR_LEN;

    *len = strlen(tmp);

    strncpy(str, tmp, *len + 1);

    return EXIT_SUCCESS;
}

int is_int(char *s, size_t len)
{
    for (size_t i = 0; i < len; i++)
        if (!isdigit(s[i]))
            return 0;
    return 1;
}

int read_int(int *num, size_t max_len, FILE *input)
{
    char tmp[MAX_STR_LEN + 1];
    size_t tmp_l;
    int rc = read_string(tmp, &tmp_l, max_len, input);
    if (rc != EXIT_SUCCESS)
        return rc;
    if (!is_int(tmp, tmp_l))
        return ERROR_WRONG_NUM;
    if (sscanf(tmp, "%d", num) != 1)
        return ERROR_WRONG_NUM;
    return EXIT_SUCCESS;
}

//format numbers.numbers
int is_double(char *s, size_t len)
{
    int is_dot = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            if (s[i] == '.' && !is_dot && i > 0)
            {
                is_dot = 1;
                continue;
            }
            else
                return 0;
        }
    }
    return 1;
}

int read_double(double *num, size_t max_len, FILE *input)
{
    char tmp[MAX_STR_LEN + 1];
    size_t tmp_l;
    int rc = read_string(tmp, &tmp_l, max_len, input);
    if (rc != EXIT_SUCCESS)
        return rc;
    if (!is_double(tmp, tmp_l))
        return ERROR_WRONG_NUM;
    if (sscanf(tmp, "%lf", num) != 1)
        return ERROR_WRONG_NUM;
    return EXIT_SUCCESS;
}

void swap(void *a, void *b, size_t size)
{
    char *p = a, *q = b, tmp;
    for (size_t i = 0; i < size; i++)
    {
        tmp = *p;
        *p = *q;
        *q = tmp;
        p++;
        q++;
    }
}

unsigned long long cur_ms_gettimeofday(void)
{
    struct timeval timeval;
    gettimeofday(&timeval, NULL);

    return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

long delta_time(struct timespec mt1, struct timespec mt2)
{
    return 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
}

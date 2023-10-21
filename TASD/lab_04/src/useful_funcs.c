#include "useful_funcs.h"

long delta_time(struct timespec mt1, struct timespec mt2)
{
    return 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
}

int read_string(char *str, size_t *len, size_t max_len, FILE *input)
{
    char tmp[MAX_STR_LEN];

    if (fgets(tmp, MAX_STR_LEN, input) == NULL)
        return ERROR_EMPTY_INPUT;

    if (tmp[strlen(tmp) - 1] == '\n')
        tmp[strlen(tmp) - 1] = '\0';
    else
    {
        clean_stdin(); 
        return ERROR_STR_LEN;
    }

    if (strlen(tmp) && strlen(tmp) > max_len)
        return ERROR_STR_LEN;

    *len = strlen(tmp);

    strncpy(str, tmp, *len + 1);
    // strcpy(str, tmp);

    return EXIT_SUCCESS;
}

int is_int(char *s, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            if (i == 0 && (s[i] == '-' || s[i] == '+'))
                continue;
            return 0;
        }
    }
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

void clean_stdin(void)
{
    char c;
    while ((c = getchar()) != '\n');
}

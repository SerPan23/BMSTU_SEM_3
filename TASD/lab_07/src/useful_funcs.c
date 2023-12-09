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

char *del_repeats_from_str(char *str, size_t len)
{
    for (size_t i = 0; i < len - 1; i++)
    {
        if (!isalnum(str[i]))
            continue;
        
        size_t count = 0;
        for (size_t j = i + 1; j < len; j++)
        {
            if (str[i] == str[j])
                count++;
            else
                str[j - count] = str[j];
        }
    }

    return str;
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
    while ((c = getchar()) != '\n')
        ;
}

int is_double(char *s, size_t len)
{
    int is_dot = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            if (i == 0 && (s[i] == '-' || s[i] == '+'))
                continue;
            else if (s[i] == '.' && !is_dot && i > 0)
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

int is_alnum_str(char *str)
{
    if (!str)
        return 0;
    
    for (size_t i = 0; i < strlen(str); i++)
        if (!isalnum(str[i]))
            return 0;

    return 1;
}

int is_prime(int n)
{
    // Corner cases
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;

    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;

    return 1;
}

int get_next_prime(int cur_prime)
{
    if (cur_prime <= 1)
        return 2;

    int prime = cur_prime;
    int found = 0;

    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found)
    {
        prime++;

        if (is_prime(prime))
            found = 1;
    }

    return prime;
}

char read_symbol(char *msg)
{
    char s[MAX_STR_LEN];
    size_t str_len = 0;

    int rc = EXIT_SUCCESS;
    do
    {
        printf("%s\n", msg);
        rc = read_string(s, &str_len, 1, stdin);
        if (rc != EXIT_SUCCESS)
        {
            printf("ERROR: You need enter only one symbol!\n");
            continue;
        }
        if (str_len == 0)
        {
            printf("ERROR: You need enter only one symbol!\n");
            rc = EXIT_FAILURE;
            continue;
        }
    } while (rc != EXIT_SUCCESS);
    return s[0];
}

#include "polynomial.h"
#include "string.h"

#define ERROR_EMPTY_INPUT 10
#define ERROR_INCORRECT_COMMAND 11

int read_str(FILE *f, char **s, size_t *len)
{
    ssize_t read;

    char *tmp = NULL;

    if ((read = getline(&tmp, len, f)) == -1)
    {
        free(tmp);
        return ERROR_EMPTY_INPUT;
    }

    if (len == 0)
    {
        free(tmp);
        return ERROR_EMPTY_INPUT;
    }

    tmp[strcspn(tmp, "\n")] = '\0';
    *s = tmp;

    return EXIT_SUCCESS;
}

int main(void)
{
    int rc;
    char *command;
    size_t len;
    rc = read_str(stdin, &command, &len);
    if (rc != EXIT_SUCCESS)
        return rc;

    if (strcmp(command, "val") == 0)
    {
        polynomial_t polynomial = { NULL, 0 };
        rc = polynomial_scan(&polynomial);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial);
            return rc;
        }

        int a = 0;
        if (scanf("%d", &a) != 1)
        {
            free(command);
            polynomial_free(&polynomial);
            return ERROR_WRONG_INPUT;
        }

        int result = polynomial_val(&polynomial, a);
        printf("%d\n", result);

        polynomial_free(&polynomial);
    }
    else if (strcmp(command, "ddx") == 0)
    {
        polynomial_t polynomial = { NULL, 0 };
        rc = polynomial_scan(&polynomial);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial);
            return rc;
        }

        polynomial_ddx(&polynomial);

        rc = polynomial_print(&polynomial);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial);
            return rc;
        }

        polynomial_free(&polynomial);
    }
    else if (strcmp(command, "sum") == 0)
    {
        polynomial_t polynomial1 = { NULL, 0 };
        polynomial_t polynomial2 = { NULL, 0 };
        rc = polynomial_scan(&polynomial1);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial1);
            return rc;
        }
        rc = polynomial_scan(&polynomial2);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial2);
            polynomial_free(&polynomial1);
            return rc;
        }

        polynomial_sum(&polynomial1, &polynomial2);

        rc = polynomial_print(&polynomial1);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial1);
            polynomial_free(&polynomial2);
            return rc;
        }

        polynomial_free(&polynomial1);
        polynomial_free(&polynomial2);
    }
    else if (strcmp(command, "dvd") == 0)
    {
        polynomial_t polynomial = { NULL, 0 };
        rc = polynomial_scan(&polynomial);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial);
            return rc;
        }
        polynomial_t even = { NULL, 0 };
        polynomial_t odd = { NULL, 0 };
        rc = polynomial_dvd(&polynomial, &even, &odd);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial);
            polynomial_free(&even);
            polynomial_free(&odd);
            return rc;
        }

        rc = polynomial_print(&even);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial);
            polynomial_free(&even);
            polynomial_free(&odd);
            return rc;
        }
        rc = polynomial_print(&odd);
        if (rc != EXIT_SUCCESS)
        {
            free(command);
            polynomial_free(&polynomial);
            polynomial_free(&even);
            polynomial_free(&odd);
            return rc;
        }

        polynomial_free(&polynomial);
        polynomial_free(&even);
        polynomial_free(&odd);
    }
    else
    {
        free(command);
        return ERROR_INCORRECT_COMMAND;
    }

    free(command);

    return 0;
}

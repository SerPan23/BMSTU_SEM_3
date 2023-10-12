#include "vector.h"

int vector_alloc(vector_t *vec)
{
    vec->a = calloc(vec->len, sizeof(int));
    if (vec->a == NULL)
        return ERROR_MEMORY_ALLOC;

    vec->ia = calloc(vec->len, sizeof(size_t));
    if (vec->ia == NULL)
        return ERROR_MEMORY_ALLOC;

    return EXIT_SUCCESS;
}

void free_vector(vector_t *vec)
{
    free(vec->a);
    vec->a = NULL;
    free(vec->ia);
    vec->ia = NULL;
    vec->len = 0;
}

void vector_read_sizes(size_t *rows_count, size_t *len, FILE *in)
{
    int rc = EXIT_SUCCESS;
    int tmp = 0;
    do
    {
        if (in == stdin)
            printf("Enter rows count (num > 0):\n");
        if (read_int(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        {
            if (in == stdin)
                printf("ERROR: invalid number\n");
            rc = ERROR_INVALID_NUM;
            continue;
        }
        if (tmp < 0)
        {
            if (in == stdin)
                printf("ERROR: invalid row count, it must be > 0\n");
            rc = ERROR_INVALID_ROW_COUNT;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *rows_count = (size_t)tmp;

    tmp = 0;
    do
    {
        if (in == stdin)
            printf("Enter non-zero numbers count (0 < num < %zu):\n", *rows_count);
        if (read_int(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        {
            if (in == stdin)
                printf("ERROR: invalid number\n");
            rc = ERROR_INVALID_NUM;
            continue;
        }
        if (tmp < 1 || (size_t)tmp > *rows_count)
        {
            if (in == stdin)
                printf("ERROR: invalid non-zero numbers count, it must be from 1 to %zu\n", *rows_count);
            rc = ERROR_INVALID_ROW_COUNT;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *len = (size_t)tmp;
}

void vector_read_element(size_t *i, int *el, size_t n, FILE *in)
{
    int rc = EXIT_SUCCESS;
    int tmp = 0;
    do
    {
        if (in == stdin)
            printf("Enter row index (from 0 to %zu):\n", n - 1);
        if (read_int(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        {
            if (in == stdin)
                printf("ERROR: invalid number\n");
            rc = ERROR_INVALID_NUM;
            continue;
        }
        if (tmp < 0 || (size_t)tmp > n - 1)
        {
            if (in == stdin)
                printf("ERROR: invalid row index, it must be from 0 to %zu\n", n - 1);
            rc = ERROR_INVALID_ROW_COUNT;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *i = (size_t)tmp;

    do
    {
        if (in == stdin)
            printf("Enter value of element:\n");
        if (read_int(el, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        {
            if (in == stdin)
                printf("ERROR: invalid number\n");
            rc = ERROR_INVALID_NUM;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
}

void vector_fill(vector_t *vec, FILE *in)
{
    size_t i = 0;
    int el = 0;
    for (size_t k = 0; k < vec->len; k++)
    {
        if (in == stdin)
            printf("----------%zu/%zu----------\n", k + 1, vec->len);
        vector_read_element(&i, &el, vec->row_count, in);
        vec->a[k] = el;
        vec->ia[k] = i;
    }
}

void vector_random_fill(vector_t *vec)
{
    size_t i;
    for (size_t k = 0; k < vec->len; k++)
    {
        size_t max_limit = vec->row_count - (vec->len - k);
        if (k == 0)
            i = (size_t)get_random_int(0, max_limit);
        else
            i = (size_t)get_random_int(vec->ia[k - 1] + 1, max_limit);

        vec->a[k] = get_random_int(1, 1000);
        vec->ia[k] = i;
    }
}

int read_vector(vector_t *vec, int is_rand, FILE *in)
{
    vector_read_sizes(&vec->row_count, &vec->len, in);
    int rc = vector_alloc(vec);
    if (rc != EXIT_SUCCESS)
        return rc;

    if (!is_rand)
        vector_fill(vec, in);
    else
        vector_random_fill(vec);

    return EXIT_SUCCESS;
}

void print_vector(vector_t *vec, FILE *out)
{
    printf("Value array:\n");
    for (size_t i = 0; i < vec->len; i++)
        fprintf(out, "%d ", vec->a[i]);
    printf("\n");

    printf("Non-zero rows index:\n");
    for (size_t i = 0; i < vec->len; i++)
        fprintf(out, "%zu ", vec->ia[i]);
    printf("\n");
}

int get_element(vector_t *vec, size_t j)
{
    for (size_t i = 0; i < vec->len; i++)
        if (vec->ia[i] == j)
            return vec->a[i];
    return 0;
}

void vector_del_zero_els(vector_t *vec)
{
    size_t count = 0;
    for (size_t i = 0; i < vec->len; i++)
    {
        if (vec->a[i] == 0)
            ++count;
        else
        {
            vec->a[i - count] = vec->a[i];
            vec->ia[i - count] = vec->ia[i];
        }
    }
    vec->len -= count;
}

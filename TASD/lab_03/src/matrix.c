#include "matrix.h"

void matrix_read_sizes(size_t *n, size_t *m, size_t *nums_count, FILE *in)
{
    int rc = EXIT_SUCCESS;
    int tmp = 0;
    do
    {
        if (in == stdin)
            printf("Enter rows count:\n");
        if (read_int(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        {
            if (in == stdin)
                printf("ERROR: invalid number\n");
            rc = ERROR_INVALID_NUM;
            continue;
        }
        if (tmp < 1 || tmp > 10000)
        {
            if (in == stdin)
                printf("ERROR: invalid rows count, n must be from 1 to 10000\n");
            rc = ERROR_INVALID_ROW_COUNT;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *n = (size_t) tmp;

    do
    {
        if (in == stdin)
            printf("Enter columns count:\n");
        if (read_int(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        {
            if (in == stdin)
                printf("ERROR: invalid number\n");
            rc = ERROR_INVALID_NUM;
            continue;
        }
        if (tmp < 1 || tmp > 10000)
        {
            if (in == stdin)
                printf("ERROR: invalid columns count, m must be from 1 to 10000\n");
            rc = ERROR_INVALID_COL_COUNT;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);

    *m = (size_t)tmp;

    size_t max_nums_count = (*m) * (*n);
    do
    {
        if (in == stdin)
            printf("Enter non-zero numbers count:\n");
        if (read_int(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        {
            if (in == stdin)
                printf("ERROR: invalid number\n");
            rc = ERROR_INVALID_NUM;
            continue;
        }
        if (tmp < 1 || (size_t)tmp > max_nums_count)
        {
            if (in == stdin)
                printf("ERROR: invalid non-zero numbers count, it must be from 1 to %zu\n", max_nums_count);
            rc = ERROR_INVALID_NUMS_COUNT;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);

    *nums_count = (size_t)tmp;
}

int matrix_alloc(matrix_t *const matrix)
{
    matrix->matrix = calloc(matrix->n, sizeof(int *));

    if (matrix->matrix == NULL)
    {
        return ERROR_MEMORY_ALLOC;
    }

    for (size_t i = 0; i < matrix->n; i++)
    {
        *(matrix->matrix + i) = calloc(matrix->m, sizeof(int));

        if (*(matrix->matrix + i) == NULL)
        {
            return ERROR_MEMORY_ALLOC;
        }
    }

    return EXIT_SUCCESS;
}

void free_matrix(matrix_t *const matrix)
{
    for (size_t i = 0; i < matrix->n; i++)
    {
        free(matrix->matrix[i]);
        matrix->matrix[i] = NULL;
    }

    free(matrix->matrix);
    matrix->matrix = NULL;
}

void matrix_read_element(size_t *i, size_t *j, int *el, size_t n, size_t m, FILE *in)
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
    *i = (size_t) tmp;

    do
    {
        if (in == stdin)
            printf("Enter column index (from 0 to %zu):\n", m - 1);
        if (read_int(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        {
            if (in == stdin)
                printf("ERROR: invalid number\n");
            rc = ERROR_INVALID_NUM;
            continue;
        }
        if (tmp < 0 || (size_t)tmp > m - 1)
        {
            if (in == stdin)
                printf("ERROR: invalid column index, it must be from 0 to %zu\n", m - 1);
            rc = ERROR_INVALID_ROW_COUNT;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *j = (size_t)tmp;

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

void matrix_fill(matrix_t *mat, size_t *nums_count, FILE *in)
{
    size_t i = 0, j = 0;
    int el = 0;
    for (size_t k = 0; k < *nums_count; k++)
    {
        if (in == stdin)
            printf("----------%zu/%zu----------\n", k + 1, *nums_count);
        matrix_read_element(&i, &j, &el, mat->n, mat->m, in);
        mat->matrix[i][j] = el;
    }
}

void matrix_random_fill(matrix_t *mat, size_t *nums_count)
{
    size_t i = 0, j = 0;
    for (size_t k = 0; k < *nums_count; k++)
    {
        i = (size_t) get_random_int(0, mat->n - 1);
        j = (size_t) get_random_int(0, mat->m - 1);
        int el = get_random_int(1, 1000);
        // printf("%zu %zu %d\n", i, j, el);
        mat->matrix[i][j] = el;
    }
}

int read_matrix(matrix_t *mat, size_t *nums_count, int is_rand, FILE *in)
{
    matrix_read_sizes(&mat->n, &mat->m, nums_count, in);
    int rc = matrix_alloc(mat);
    if (rc != EXIT_SUCCESS)
        return rc;

    if (!is_rand)
        matrix_fill(mat, nums_count, in);
    else
        matrix_random_fill(mat, nums_count);

    return EXIT_SUCCESS;
}

void print_matrix(matrix_t *mat, FILE *out)
{
    for (size_t i = 0; i < mat->n; i++)
    {
        for (size_t j = 0; j < mat->m; j++)
            fprintf(out, "%5d", mat->matrix[i][j]);
        fprintf(out, "\n");
    }
}

int sparse_matrix_alloc(sparse_matrix_t *s_mat)
{
    s_mat->a = calloc(s_mat->nums_count, sizeof(int));
    if (s_mat->a == NULL)
        return ERROR_MEMORY_ALLOC;

    s_mat->ja = calloc(s_mat->nums_count, sizeof(size_t));
    if (s_mat->ja == NULL)
        return ERROR_MEMORY_ALLOC;

    s_mat->ia = calloc(s_mat->n + 1, sizeof(size_t));
    if (s_mat->ia == NULL)
        return ERROR_MEMORY_ALLOC;
    return EXIT_SUCCESS;
}

void free_sparse_matrix(sparse_matrix_t *s_mat)
{
    free(s_mat->a);
    s_mat->a = NULL;
    free(s_mat->ja);
    s_mat->ja = NULL;
    free(s_mat->ia);
    s_mat->ia = NULL;
}

int matrix_to_sparse_matrix(matrix_t *mat, sparse_matrix_t *s_mat, size_t *nums_count)
{
    s_mat->n = mat->n;
    s_mat->m = mat->m;
    s_mat->nums_count = *nums_count;

    sparse_matrix_alloc(s_mat);
    size_t k = 0, i;
    for (i = 0; i < mat->n; i++)
    {
        s_mat->ia[i] = k;
        for (size_t j = 0; j < mat->m; j++)
        {
            if (mat->matrix[i][j] != 0) 
            {
                s_mat->a[k] = mat->matrix[i][j];
                s_mat->ja[k] = j;
                ++k;
            }
        }
    }
    s_mat->ia[i] = k;
    return EXIT_SUCCESS;
}

void sparse_matrix_to_matrix(sparse_matrix_t *s_mat, matrix_t *mat)
{
    
    for (size_t i = 0; i < s_mat->n; i++)
        for (size_t j = 0; j < s_mat->m; j++)
            mat->matrix[i][j] = 0;

    for (size_t i = 0; i < s_mat->n; i++)
    {
        int len = s_mat->ia[i + 1] - s_mat->ia[i];
        if (len > 0)
            for (size_t k = s_mat->ia[i]; k < s_mat->ia[i + 1]; k++)
                mat->matrix[i][s_mat->ja[k]] = s_mat->a[k];
    }
}

void print_sparse_matrix(sparse_matrix_t *s_mat, FILE *out)
{
    printf("Value array:\n");
    for (size_t i = 0; i < s_mat->nums_count; i++)
        fprintf(out, "%d ", s_mat->a[i]);
    printf("\n");

    printf("Columns index:\n");
    for (size_t i = 0; i < s_mat->nums_count; i++)
        fprintf(out, "%zu ", s_mat->ja[i]);
    printf("\n");

    printf("Rows start index:\n");
    for (size_t i = 0; i <= s_mat->n; i++)
        fprintf(out, "%zu ", s_mat->ia[i]);
    printf("\n");
}

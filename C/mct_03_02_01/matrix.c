#include "matrix.h"

int matrix_alloc(matrix_t *mat, size_t n, size_t m)
{
    void *ptmp;
    ptmp = calloc(n, sizeof(int *));
    if (!ptmp)
        return ERROR_MEM_ALLOC;

    mat->data = ptmp;

    for (size_t i = 0; i < n; i++)
    {
        mat->data[i] = calloc(m, sizeof(int));
        if (!mat->data[i])
        {
            matrix_free(mat);
            return ERROR_MEM_ALLOC;
        }
    }
    mat->n = n;
    mat->m = m;
    return EXIT_SUCCESS;
}

void matrix_free(matrix_t *mat)
{
    for (size_t i = 0; i < mat->n; i++)
    {
        if (mat->data[i])
            free(mat->data[i]);
        mat->data[i] = NULL;
    }

    if (mat->data)
        free(mat->data);
    mat->data = NULL;
    mat->n = 0;
    mat->m = 0;
}

int matrix_col_realloc(matrix_t *mat, size_t new_m)
{
    void *ptmp;
    for (size_t i = 0; i < mat->n; i++)
    {
        ptmp = realloc(mat->data[i], new_m * sizeof(int));
        if (!ptmp)
        {
            matrix_free(mat);
            return ERROR_MEM_REALLOC;
        }
        mat->data[i] = ptmp;
    }
    mat->m = new_m;
    return EXIT_SUCCESS;
}

int matrix_fill(matrix_t *mat)
{
    for (size_t i = 0; i < mat->n; i++)
        for (size_t j = 0; j < mat->m; j++)
            if (scanf("%d", &mat->data[i][j]) != 1)
                return ERROR_INVALID_NUM;

    return EXIT_SUCCESS;
}

void matrix_print(matrix_t *mat)
{
    for (size_t i = 0; i < mat->n; i++)
    {
        for (size_t j = 0; j < mat->m; j++)
            printf("%d\t", mat->data[i][j]);
        printf("\n");
    }
}

int find_max_el(matrix_t *mat, size_t *row_ind, size_t *col_ind)
{
    size_t max_i = 0, max_j = 0;
    for (size_t i = 0; i < mat->n; i++)
        for (size_t j = 0; j < mat->m; j++)
        {
            if (mat->data[max_i][max_j] < mat->data[i][j])\
            {
                max_i = i;
                max_j = j;
            }
        }
    
    *row_ind = max_i;
    *col_ind = max_j;

    return EXIT_SUCCESS;
}

int del_col_with_max(matrix_t *mat)
{
    int rc;
    size_t max_i = 0, max_j = 0;
    rc = find_max_el(mat, &max_i, &max_j);
    if (rc != EXIT_SUCCESS)
        return rc;

    for (size_t i = 0; i < mat->n; i++)
    {
        for (size_t j = max_j + 1; j < mat->m; j++)
            mat->data[i][j - 1] = mat->data[i][j];
    }

    rc = matrix_col_realloc(mat, mat->m - 1);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}

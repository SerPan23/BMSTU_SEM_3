#include "my_matrix.h"

int matrix_alloc(matrix_t *matrix)
{
    matrix->matrix = calloc(matrix->n, sizeof(int *));
    if (!matrix->matrix)
        return ERROR_MEM_ALLOC;

    for (size_t i = 0; i < matrix->n; i++)
    {
        matrix->matrix[i] = calloc(matrix->m, sizeof(int));
        if (!matrix->matrix[i])
        {
            matrix_free(matrix);
            return ERROR_MEM_ALLOC;
        }
    }
    return EXIT_SUCCESS;
}

void matrix_free(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->n; i++)
    {
        if (matrix->matrix[i])
            free(matrix->matrix[i]);
        matrix->matrix[i] = NULL;
    }
    if (matrix->matrix)
        free(matrix->matrix);
    matrix->matrix = NULL;
    matrix->n = 0;
    matrix->m = 0;
}

int matrix_read(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->n; i++)
        for (size_t j = 0; j < matrix->m; j++)
            if (scanf("%d", &matrix->matrix[i][j]) != 1)
                return ERROR_INVALID_NUM;
    return EXIT_SUCCESS;
}

void matrix_print(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->n; i++)
    {
        for (size_t j = 0; j < matrix->m; j++)
            printf("%d ", matrix->matrix[i][j]);
        printf("\n");
    }
}

int matrix_copy(matrix_t *dst, matrix_t *src)
{
    if (dst->matrix)
        matrix_free(dst);
    dst->n = src->n;
    dst->m = src->m;
    int rc = matrix_alloc(dst);
    if (rc != EXIT_SUCCESS)
        return rc;

    for (size_t i = 0; i < src->n; i++)
        for (size_t j = 0; j < src->m; j++)
            dst->matrix[i][j] = src->matrix[i][j];

    return EXIT_SUCCESS;
}

int matrix_mul(matrix_t *mat1, matrix_t *mat2, matrix_t *dst)
{
    int rc;
    if (mat1->m != mat2->n)
        return ERROR_INVALID_MATRIX_SIZES;

    if (dst->matrix)
        matrix_free(dst);

    dst->n = mat1->n;
    dst->m = mat2->m;

    rc = matrix_alloc(dst);
    if (rc != EXIT_SUCCESS)
        return rc;

    for (size_t i = 0; i < dst->n; i++)
        for (size_t j = 0; j < dst->m; j++)
        {
            dst->matrix[i][j] = 0;
            for (size_t k = 0; k < mat1->m; k++)
                dst->matrix[i][j] += mat1->matrix[i][k] * mat2->matrix[k][j];
        }
    return EXIT_SUCCESS;
}

int matrix_realloc_row_count(matrix_t *matrix, size_t new_size)
{
    void *ptmp = realloc(matrix->matrix, new_size * sizeof(int *));
    if (!ptmp)
    {
        matrix_free(matrix);
        return ERROR_REALLOC;
    }
    matrix->matrix = ptmp;
    for (size_t i = matrix->n; i < new_size; i++)
        matrix->matrix[i] = NULL;
    matrix->n = new_size;
    return EXIT_SUCCESS;
}

int matrix_realloc_column_count(matrix_t *matrix, size_t new_size)
{
    for (size_t i = 0; i < matrix->n; i++)
    {
        void *ptmp = realloc(matrix->matrix[i], new_size * sizeof(int));
        if (!ptmp)
        {
            matrix_free(matrix);
            return ERROR_REALLOC;
        }
        matrix->matrix[i] = ptmp;
    }
    matrix->m = new_size;
    return EXIT_SUCCESS;
}


void get_min_el_cords(matrix_t *matrix, size_t *row_ind, size_t *col_ind)
{
    *row_ind = 0;
    *col_ind = 0;
    for (size_t i = 0; i < matrix->n; i++)
        for (size_t j = 0; j < matrix->m; j++)
        {
            if (matrix->matrix[i][j] <= matrix->matrix[*row_ind][*col_ind])
            {
                *row_ind = i;
                *col_ind = j;
            }
        }
}

int del_row_by_ind(matrix_t *matrix, size_t row_ind)
{
    free(matrix->matrix[row_ind]);
    matrix->matrix[row_ind] = NULL;

    for (size_t i = row_ind + 1; i < matrix->n; i++)
        matrix->matrix[i - 1] = matrix->matrix[i];

    matrix->matrix[matrix->n - 1] = NULL;

    int rc = matrix_realloc_row_count(matrix, matrix->n - 1);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}

int del_col_by_ind(matrix_t *matrix, size_t col_ind)
{
    for (size_t i = 0; i < matrix->n; i++)
        for (size_t j = col_ind + 1; j < matrix->m; j++)
            matrix->matrix[i][j - 1] = matrix->matrix[i][j];

    int rc = matrix_realloc_column_count(matrix, matrix->m - 1);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}

int matrix_to_square_form(matrix_t *matrix)
{
    size_t row_ind, col_ind;
    while (matrix->n != matrix->m)
    {
        get_min_el_cords(matrix, &row_ind, &col_ind);
        if (matrix->n > matrix->m)
            del_row_by_ind(matrix, row_ind);
        else if (matrix->n < matrix->m)
            del_col_by_ind(matrix, col_ind);
    }
    return EXIT_SUCCESS;
}

int calc_geometric_avg_in_col(matrix_t *matrix, size_t max_row_ind, size_t col_ind)
{
    int m = 1;
    for (size_t i = 0; i < max_row_ind; i++)
        m *= abs(matrix->matrix[i][col_ind]);

    return (int)floor(pow(m, 1.0 / max_row_ind));
}

int get_min_by_row(matrix_t *matrix, size_t row_ind, size_t max_col_ind)
{
    size_t min_m = 0;
    for (size_t j = 0; j < max_col_ind; j++)
        if (matrix->matrix[row_ind][j] < matrix->matrix[row_ind][min_m])
            min_m = j;
    return matrix->matrix[row_ind][min_m];
}

int matrix_to_new_size(matrix_t *matrix, size_t new_size)
{
    int rc;
    size_t old_size = matrix->n;
    rc = matrix_realloc_row_count(matrix, new_size);
    if (rc != EXIT_SUCCESS)
        return ERROR_REALLOC;
    for (size_t i = old_size; i < new_size; i++)
    {
        matrix->matrix[i] = calloc(matrix->m, sizeof(int));
        if (!matrix->matrix[i])
        {
            matrix_free(matrix);
            return ERROR_MEM_ALLOC;
        }
        for (size_t j = 0; j < matrix->m; j++)
            matrix->matrix[i][j] = calc_geometric_avg_in_col(matrix, i, j);
    }
    rc = matrix_realloc_column_count(matrix, new_size);
    if (rc != EXIT_SUCCESS)
        return ERROR_REALLOC;
    for (size_t i = 0; i < new_size; i++)
        for (size_t j = old_size; j < new_size; j++)
            matrix->matrix[i][j] = get_min_by_row(matrix, i, j);
    return EXIT_SUCCESS;
}

void matrix_zero_pow(matrix_t *dst)
{
    for (size_t i = 0; i < dst->n; i++)
        for (size_t j = 0; j < dst->m; j++)
        {
            dst->matrix[i][j] = 0;
            if (i == j)
                dst->matrix[i][j] = 1;
        }
}

int matrix_pow(matrix_t *matrix, size_t n)
{
    if (matrix->n != matrix->m)
        return ERROR_NOT_SQUARE_MATRIX;
    if (n == 0)
    {
        matrix_zero_pow(matrix);
        return EXIT_SUCCESS;
    }
    if (n == 1)
        return EXIT_SUCCESS;
    int rc;
    matrix_t mat_g = { NULL, 0, 0 }, tmp = { NULL, 0, 0 };
    rc = matrix_copy(&mat_g, matrix);
    if (rc != EXIT_SUCCESS)
        return rc;
    size_t k = 1;
    while (k * 2 <= n)
    {
        rc = matrix_mul(&mat_g, &mat_g, &tmp);
        if (rc != EXIT_SUCCESS)
        {
            matrix_free(&mat_g);
            matrix_free(&tmp);
            return rc;
        }
        rc = matrix_copy(&mat_g, &tmp);
        if (rc != EXIT_SUCCESS)
        {
            matrix_free(&mat_g);
            matrix_free(&tmp);
            return rc;
        }
        k *= 2;
    }
    size_t p = n - k;
    for (size_t i = 0; i < p; i++)
    {
        rc = matrix_mul(&mat_g, matrix, &tmp);
        if (rc != EXIT_SUCCESS)
        {
            matrix_free(&mat_g);
            matrix_free(&tmp);
            return rc;
        }
        rc = matrix_copy(&mat_g, &tmp);
        if (rc != EXIT_SUCCESS)
        {
            matrix_free(&mat_g);
            matrix_free(&tmp);
            return rc;
        }
    }
    rc = matrix_copy(matrix, &mat_g);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_g);
        matrix_free(&tmp);
        return rc;
    }
    matrix_free(&mat_g);
    matrix_free(&tmp);
    return EXIT_SUCCESS;
}

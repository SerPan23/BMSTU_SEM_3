#include "matrix_operations.h"

int matrix_mul_vec(matrix_t *mat, vector_t *vec, vector_t *dst)
{
    for (size_t i = 0; i < mat->n; i++)
        for (size_t j = 0; j < mat->m; j++)
        {
            dst->a[i] += mat->matrix[i][j] * get_element(vec, j);
            dst->ia[i] = i;
        }
    return EXIT_SUCCESS;
}

// void sparse_matrix_mul_vec(int *row_ptr, int *colind, MYTYPE *val, int N, MYTYPE *x, MYTYPE *y)
void sparse_matrix_mul_vec(sparse_matrix_t *mat, vector_t *vec, vector_t *vec_res)
{
    // int i, j;
    // MYTYPE temp;
    // for (i = 0; i < N; i++)
    // {
    //     temp = y[i];
    //     for (j = row_ptr[i]; j < row_ptr[i + 1]; j++)
    //     {
    //         temp += val[j] * x[colind[j]];
    //     }
    //     y[i] = temp;
    // }
    for (size_t i = 0; i < mat->n; i++)
    {
        for (size_t j = mat->ia[i]; j < mat->ia[i + 1]; j++)
            vec_res->a[i] += mat->a[j] * get_element(vec, mat->ja[j]);
        vec_res->ia[i] = i;
    }
}

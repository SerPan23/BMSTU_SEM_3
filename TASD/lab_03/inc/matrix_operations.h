#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.h"
#include "vector.h"

int matrix_mul_vec(matrix_t *mat1, vector_t *vec, vector_t *dst);
void sparse_matrix_mul_vec(sparse_matrix_t *mat, vector_t *vec, vector_t *vec_res);

#endif

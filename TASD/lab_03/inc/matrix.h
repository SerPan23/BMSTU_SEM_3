#ifndef MATRIX_H
#define MATRIX_H

#include "defines.h"
#include "useful_funcs.h"

typedef struct 
{
    size_t n;
    size_t m;
    size_t nums_count;

    int *a;
    size_t *ja;
    size_t *ia;
} sparse_matrix_t;

typedef struct std_matr
{
    int **matrix;
    size_t n;
    size_t m;
} matrix_t;

int read_matrix(matrix_t *mat, size_t *nums_count, int is_rand, FILE *in);
void print_matrix(matrix_t *mat, FILE *out);
void matrix_random_fill(matrix_t *mat, size_t *nums_count);

int matrix_alloc(matrix_t *const matrix);
void free_matrix(matrix_t *const matrix);

int matrix_to_sparse_matrix(matrix_t *mat, sparse_matrix_t *s_mat, size_t *nums_count);
void sparse_matrix_to_matrix(sparse_matrix_t *s_mat, matrix_t *mat);
void print_sparse_matrix(sparse_matrix_t *s_mat, FILE *out);

int sparse_matrix_alloc(sparse_matrix_t *s_mat);
void free_sparse_matrix(sparse_matrix_t *s_mat);

#endif

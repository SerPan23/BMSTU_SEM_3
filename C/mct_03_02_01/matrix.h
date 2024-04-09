#ifndef MATRIX_H
#define MATRIX_h

#include <stdio.h>
#include <stdlib.h>

#define ERROR_MEM_ALLOC 1
#define ERROR_MEM_REALLOC 2
#define ERROR_INVALID_NUM 3
#define ERROR_INVALID_ROW_COUNT 4
#define ERROR_INVALID_COL_COUNT 5

typedef struct matrix
{
    size_t n;
    size_t m;
    int **data;
} matrix_t;

int matrix_alloc(matrix_t *mat, size_t n, size_t m);
void matrix_free(matrix_t *mat);
int matrix_col_realloc(matrix_t *mat, size_t new_m);
int matrix_fill(matrix_t *mat);
void matrix_print(matrix_t *mat);

int find_max_el(matrix_t *mat, size_t *row_ind, size_t *col_ind);
int del_col_with_max(matrix_t *mat);

#endif
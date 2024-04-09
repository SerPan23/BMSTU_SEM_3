#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include "defines.h"

typedef struct 
{
    int **matrix; 
    size_t n;
    size_t m;
} matrix_t;

int matrix_alloc(matrix_t *matrix);
void matrix_free(matrix_t *matrix);
int matrix_read(matrix_t *matrix);
void matrix_print(matrix_t *matrix);
int matrix_copy(matrix_t *dst, matrix_t *src);

int matrix_to_square_form(matrix_t *matrix);
int matrix_to_new_size(matrix_t *matrix, size_t new_size);
int matrix_pow(matrix_t *matrix, size_t n);
int matrix_mul(matrix_t *mat1, matrix_t *mat2, matrix_t *dst);

#endif

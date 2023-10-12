#ifndef VECTOR_H
#define VECTOR_H

#include "defines.h"
#include "useful_funcs.h"

typedef struct 
{
    size_t row_count;
    int *a;
    size_t *ia;
    size_t len;
} vector_t;

int vector_alloc(vector_t *vec);
void free_vector(vector_t *vec);

int read_vector(vector_t *vec, int is_rand, FILE *in);
void print_vector(vector_t *vec, FILE *out);
void vector_random_fill(vector_t *vec);

int get_element(vector_t *vec, size_t i);
void vector_del_zero_els(vector_t *vec);

#endif

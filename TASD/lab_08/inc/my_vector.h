#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "defines.h"
#include "useful_funcs.h"

typedef struct vector
{
    int *data;
    int size;
    int size_alloc;
} vector_t;

int vector_init(vector_t **vec, int n);
void vector_free(vector_t **vec);
int vector_push(vector_t *vec, int el);
void vector_print(vector_t *vec, char sep, char end);
void vector_reverse(vector_t *vec);

#endif

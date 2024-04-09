#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR_NODE_ALLOC 1
#define ERROR_WRONG_INPUT 2
#define ERROR_LIST_EMPTY 3
#define ERROR_NO_ALLOC 4

typedef struct pnode pnode_t;

struct pnode
{
    int coefficient;
    pnode_t *next;
};

int pnode_alloc(pnode_t **pnode);
void pnode_free(pnode_t **pnode);
void pnode_print(pnode_t *pnode);
int pnode_scan(FILE *f, pnode_t **pnode);

typedef struct polynomial
{
    pnode_t *list_head;
    size_t size;
} polynomial_t;

void polynomial_free(polynomial_t *polynomial);
int polynomial_push(polynomial_t *polynomial, pnode_t *pnode);
int polynomial_print(polynomial_t *polynomial);
int polynomial_pop(polynomial_t *polynomial);
int polynomial_scan(polynomial_t *polynomial);
int pnode_create(pnode_t **pnode, int coefficient);
int polynomial_pop_front(polynomial_t *polynomial);

int polynomial_val(polynomial_t *polynomial, int a);
int polynomial_ddx(polynomial_t *polynomial);
int polynomial_sum(polynomial_t *src_1, polynomial_t *src_2);
int polynomial_dvd(polynomial_t *polynomial, polynomial_t *even, polynomial_t *odd);

#endif
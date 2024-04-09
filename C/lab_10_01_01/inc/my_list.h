#ifndef MY_LIST_H
#define MY_LIST_H

#include "stdio.h"
#include "stdlib.h"
#include "employee.h"

#define ERROR_NODE_ALLOC 1

typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
};


// My funcs
int node_init(node_t **node);
void node_free(node_t *node);
int list_push(node_t **head, void *data);
void list_print(node_t *head, void (*print)(FILE *f, void *), FILE *f);
void list_free(node_t **head);

// Task funcs

// 1 балл
node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));

// 1 балл
void *pop_front(node_t **head);

// 1 балл
void *pop_back(node_t **head);

// 1 балл
void append(node_t **head_a, node_t **head_b);

// 2 балла
void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *));

// 4 балла
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
void front_back_split(node_t *head, node_t **back);
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));
#endif

#ifndef MY_LIST_H
#define MY_LIST_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_MEM_ALLOC 1
#define ERROR_LIST_SIZE 2
#define ERROR_EMPTY_LIST 3
#define ERROR_INVALID_NODE 4
#define ERROR_NODE_NOT_FOUND 5

typedef struct node
{
    int data;
    struct node *next;
} node_t;

int node_init(node_t **head);
void node_free(node_t **head);
int list_push(node_t **head, int data);
void list_free(node_t **head);
void list_print(node_t *head);
size_t list_size(node_t *head);
int list_del_node(node_t **head, node_t *del_node);

node_t *find_n_min(node_t *head, size_t n);

#endif
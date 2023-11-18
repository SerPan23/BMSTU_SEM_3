#ifndef QUEUE_LIST_H
#define QUEUE_LIST_H

#include "task.h"
#include "defines.h"
#include "useful_funcs.h"

typedef struct list_node
{
    task_t task;
    struct list_node *next;
} list_node_t;

typedef struct queue_list
{
    list_node_t *head;
    list_node_t *tail;
    size_t size;
    int max_id;
    void **free_area;
    size_t free_area_size;
    size_t free_area_size_alloc;
} queue_list_t;

int list_node_init(list_node_t **node);
void list_node_free(list_node_t *node);
void list_node_copy(list_node_t *dst, list_node_t *src);

int queue_list_init(queue_list_t *queue);
int queue_list_push(queue_list_t *queue, list_node_t *node);
int queue_list_pop(queue_list_t *queue, task_t *task);
void queue_list_print(queue_list_t *queue);
void queue_list_free(queue_list_t *queue);

int init_free_area(queue_list_t *queue, size_t size);
int realloc_free_area(queue_list_t *queue, size_t new_size);
int add_free_area(queue_list_t *queue, void *ptr);
void free_free_area(queue_list_t *queue);
int check_if_mem_reused(queue_list_t *queue);

#endif

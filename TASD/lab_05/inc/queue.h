#ifndef QUEUE_H
#define QUEUE_H

#include "queue_array.h"
#include "queue_list.h"

typedef struct queue
{
    queue_array_t arr;
    queue_list_t list;
} queue_t;

int queue_init(queue_t *queue);
void queue_free(queue_t *queue);

size_t queue_len(queue_t *queue, int is_queue_list);
int queue_push(queue_t *queue, int is_queue_list, task_t task);
int queue_pop(queue_t *queue, int is_queue_list, task_t *task);

#endif

#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

#include "task.h"
#include "defines.h"
#include "useful_funcs.h"

typedef struct array_element
{
    task_t task;
} array_element_t;

typedef struct queue_array
{
    array_element_t data[MAX_QUEUE_LEN];
    size_t size;
    size_t pin;
    size_t pout;
    int max_id;
} queue_array_t;

void array_el_init(array_element_t *el);

void queue_array_init(queue_array_t *queue);
int queue_array_push(queue_array_t *queue, array_element_t *el);
int queue_array_pop(queue_array_t *queue, task_t *task);
void queue_array_print(queue_array_t *queue);

#endif

#include "queue_array.h"

void array_el_init(array_element_t *el)
{
    el->task.id = -1;
    el->task.count = 0;
    el->task.time_out = 0;
}

void queue_array_init(queue_array_t *queue)
{
    queue->pin = 0;
    queue->pout = 0;
    queue->size = 0;
    queue->max_id = 0;
}

int queue_array_push(queue_array_t *queue, array_element_t *el)
{

    if (queue->size + 1 > MAX_QUEUE_LEN)
        return ERROR_QUEUE_OVERFLOW;


    // printf("* %zu %d | Pin: %zu Pout: %zu\t", queue->size, queue->max_id, 
    //     queue->pin, queue->pout);

    if (queue->pin == MAX_QUEUE_LEN)
    {
        if (queue->pout > 0)
            queue->pin = 0;
        else
            return ERROR_QUEUE_OVERFLOW;
    }

    if (el->task.id == -1)
        el->task.id = queue->max_id++;

    queue->data[queue->pin++] = *el;
    queue->size++;

    return EXIT_SUCCESS;
}

int queue_array_pop(queue_array_t *queue, task_t *task)
{
    if (queue->size == 0)
        return ERROR_EMPTY_QUEUE;

    if (task)
        *task = queue->data[queue->pout].task;

    if (queue->pout < queue->pin)
    {
        queue->pout++;
    }
    else
    {
        if (queue->pout + 1 >= MAX_QUEUE_LEN)
            queue->pout = 0;
        else
            queue->pout++;
    }

    queue->size--;

    return EXIT_SUCCESS;
}

void queue_array_print(queue_array_t *queue)
{
    if (queue->size == 0)
    {
        printf("EMPTY QUEUE\n");
        return;
    }

    if (queue->pout < queue->pin)
        for (size_t i = queue->pout; i < queue->pin; i++)
            printf("%zu) id: %d\n", i, queue->data[i].task.id);
    else
    {
        size_t ind = 0;
        for (size_t i = queue->pout; i < MAX_QUEUE_LEN; i++, ind++)
            printf("%zu) id: %d\n", ind, queue->data[i].task.id);
        for (size_t i = 0; i < queue->pin; i++, ind++)
            printf("%zu) id: %d\n", ind, queue->data[i].task.id);
    }
}

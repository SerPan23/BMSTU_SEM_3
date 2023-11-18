#include "queue.h"

int queue_init(queue_t *queue)
{
    int rc = EXIT_SUCCESS;

    rc = queue_list_init(&queue->list);
    if (rc != EXIT_SUCCESS)
        return rc;

    queue_array_init(&queue->arr);

    return EXIT_SUCCESS;
}

void queue_free(queue_t *queue)
{
    queue_list_free(&queue->list);
}

size_t queue_len(queue_t *queue, int is_queue_list)
{
    return is_queue_list ? queue->list.size : queue->arr.size;
}

int queue_push(queue_t *queue, int is_queue_list, task_t task)
{
    int rc;
    if (is_queue_list)
    {
        list_node_t *tmp_list;
        list_node_init(&tmp_list);
        tmp_list->task = task;
        rc = queue_list_push(&queue->list, tmp_list);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    else
    {
        array_element_t tmp;
        array_el_init(&tmp);
        tmp.task = task;
        rc = queue_array_push(&queue->arr, &tmp);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    return EXIT_SUCCESS;
}

int queue_pop(queue_t *queue, int is_queue_list, task_t *task)
{
    if (is_queue_list)
    {
        queue_list_pop(&queue->list, task);
    }
    else
    {
        queue_array_pop(&queue->arr, task);
    }
    return EXIT_SUCCESS;
}

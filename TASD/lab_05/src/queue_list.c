#include "queue_list.h"

int list_node_init(list_node_t **node)
{
    *node = NULL;
    *node = malloc(sizeof(list_node_t));
    if (!(*node))
        return ERROR_MEMORY;

    (*node)->task.id = -1;
    (*node)->task.count = 0;
    (*node)->task.time_out = 0;
    (*node)->next = NULL;

    return EXIT_SUCCESS;
}

void list_node_free(list_node_t *node)
{
    free(node);
    node = NULL;
}

void list_node_copy(list_node_t *dst, list_node_t *src)
{
    *dst = *src;
    dst->next = NULL;
}

int queue_list_init(queue_list_t *queue)
{
    int rc = EXIT_SUCCESS;
    queue->size = 0;
    queue->max_id = 0;
    queue->head = NULL;
    queue->tail = NULL;
    rc = init_free_area(queue, MAX_QUEUE_LEN);
    return rc;
}

int queue_list_push(queue_list_t *queue, list_node_t *node)
{
    if (queue->size + 1 > MAX_QUEUE_LEN)
        return ERROR_QUEUE_OVERFLOW;

    if (node->task.id == -1)
        node->task.id = queue->max_id++;

    if (queue->size == 0)
    {
        queue->head = node;
        queue->tail = node;
    }
    else
    {
        // queue->tail->next = queue->tail;
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->size++;
    return EXIT_SUCCESS;
}

int queue_list_pop(queue_list_t *queue, task_t *task)
{

    if (queue->size == 0)
        return ERROR_EMPTY_QUEUE;

    list_node_t *tmp = queue->head;

    // printf("*%p %p\n", (void *)tmp, (void *)tmp->next);

    if (queue->size == 1)
    {
        queue->head = NULL;
        queue->tail = NULL;
    }
    else
        queue->head = tmp->next;

    queue->size--;

    if (task)
        // list_node_copy(node, tmp);
        *task = tmp->task;

    if (queue->free_area_size_alloc)
        add_free_area(queue, tmp);

    list_node_free(tmp);
    return EXIT_SUCCESS;
}

void queue_list_print(queue_list_t *queue)
{
    list_node_t *el = queue->head;
    if (el == NULL)
        printf("Queue is empty.\n");

    for (size_t i = 0; i < queue->size; i++, el = el->next)
        printf("%d id: %d  %p\n", (int)i, el->task.id, (void *)el);

    printf("\nFree area:\n");
    if (queue->free_area_size == 0)
        printf("No free areas.\n");
    else
    {
        for (size_t i = 0; i < queue->free_area_size; i++)
            printf("%p\n", queue->free_area[i]);
    }
}
void queue_list_free(queue_list_t *queue)
{
    while (queue->head)
    {
        int rc = queue_list_pop(queue, NULL);
        if (rc != EXIT_SUCCESS)
            break;
    }
    if (queue->free_area_size_alloc)
        free(queue->free_area);
    queue->free_area_size = 0;
    queue->free_area_size_alloc = 0;
}

int init_free_area(queue_list_t *queue, size_t size)
{
    queue->free_area = calloc(size, sizeof(void *));
    if (!queue->free_area)
        return ERROR_MEMORY;
    queue->free_area_size = 0;
    queue->free_area_size_alloc = size;
    return EXIT_SUCCESS;
}

int realloc_free_area(queue_list_t *queue, size_t new_size)
{
    void *ptmp = NULL;
    ptmp = realloc(ptmp, new_size * sizeof(void *));
    if (!ptmp)
        return ERROR_MEMORY;
    queue->free_area = ptmp;
    queue->free_area_size_alloc = new_size;
    return EXIT_SUCCESS;
}

int add_free_area(queue_list_t *queue, void *ptr)
{
    int rc = EXIT_SUCCESS;
    if (queue->free_area_size_alloc == 0)
        rc = init_free_area(queue, MAX_QUEUE_LEN);

    if (rc != EXIT_SUCCESS)
        return rc;

    if (queue->free_area_size + 1 > queue->free_area_size_alloc)
        rc = realloc_free_area(queue, queue->free_area_size_alloc + MAX_QUEUE_LEN);

    if (rc != EXIT_SUCCESS)
        return rc;

    queue->free_area[queue->free_area_size++] = ptr;
    return rc;
}

void free_free_area(queue_list_t *queue)
{
    free(queue->free_area);
    queue->free_area = NULL;
    queue->free_area_size = 0;
    queue->free_area_size_alloc = 0;
}

int check_if_mem_reused(queue_list_t *queue)
{
    void *last_added = (void *)queue->tail;
    int is_found = 0;

    for (size_t i = 0; i < queue->free_area_size; i++)
    {
        if (last_added == queue->free_area[i])
        {
            is_found = 1;
            for (size_t j = i; j < queue->free_area_size - 1; ++j)
            {
                void *tmp = queue->free_area[j];
                queue->free_area[j] = queue->free_area[j + 1];
                queue->free_area[j + 1] = tmp;
            }
        }
    }

    if (is_found)
        queue->free_area_size--;

    return is_found;
}

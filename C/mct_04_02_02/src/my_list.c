#include "my_list.h"

int node_init(node_t **node)
{
    (*node) = malloc(sizeof(node_t));
    if (!(*node))
        return ERROR_MEM_ALLOC;

    (*node)->data = 0;
    (*node)->next = NULL;

    return EXIT_SUCCESS;
}

void node_free(node_t **node)
{
    if (*node)
        free(*node);

    node = NULL;
}

int list_push(node_t **head, int data)
{
    node_t *new_node;
    int rc = node_init(&new_node);
    if (rc != EXIT_SUCCESS)
        return rc;

    new_node->data = data;

    if (*head == NULL)
        *head = new_node;
    else
    {
        node_t *tail = *head;
        for (; tail->next != NULL; tail = tail->next);
        tail->next = new_node;
    }

    return EXIT_SUCCESS;
}

void list_free(node_t **head)
{
    node_t *next = NULL;

    for (; *head != NULL; *head = next)
    {
        next = (*head)->next;
        node_free(head);
    }

    *head = NULL;
}

void list_print(node_t *head)
{
    for (node_t *cur = head; cur != NULL; cur = cur->next)
        printf("%d ", cur->data);

    printf("\n");
}

size_t list_size(node_t *head)
{
    size_t count = 0;
    for (node_t *cur = head; cur != NULL; cur = cur->next)
        count++;

    return count;
}

node_t *find_max(node_t *head)
{
    if (list_size(head) < 1)
        return NULL;

    node_t *maxx = NULL;


    for (node_t *cur = head; cur != NULL; cur = cur->next)
    {
        if (maxx == NULL || maxx->data < cur->data)
            maxx = cur;
    }

    return maxx;
}

int list_swap_second_and_el(node_t **head, node_t *el)
{
    if (list_size(*head) < 2)
        return ERROR_LIST_SIZE;

    node_t *second = (*head)->next;

    if (second == el)
        return EXIT_SUCCESS;

    if (*head == el)
    {
        node_t *after_second = second->next;
        second->next = *head;
        (*head)->next = after_second;

        *head = second;

        return EXIT_SUCCESS;
    }

    node_t *prev_el = *head;
    for (; prev_el->next != el; prev_el = prev_el->next);

    if (prev_el == second)
    {
        second->next = el->next;
        el->next = second;
        (*head)->next = el;
    }
    else
    {
        node_t *after_second = second->next;
        second->next = el->next;
        
        el->next = after_second;

        (*head)->next = el;

        prev_el->next = second;
    }

    return EXIT_SUCCESS;
}

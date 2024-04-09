#include "my_list.h"

int node_init(node_t **node)
{
    (*node) = malloc(sizeof(node_t));
    if (!(*node))
        return ERROR_NODE_ALLOC;

    (*node)->data = NULL;
    (*node)->next = NULL;

    return EXIT_SUCCESS;
}

void node_free(node_t *node)
{
    if (node)
        free(node);
}

int list_push(node_t **head, void *data)
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

void list_print(node_t *head, void (*print)(FILE *f, void *), FILE *f)
{
    for (node_t *cur = head; cur != NULL; cur = cur->next)
        print(f, cur->data);
}

void list_free(node_t **head)
{
    node_t *next = NULL;

    for (; *head != NULL; *head = next)
    {
        next = (*head)->next;
        node_free(*head);
    }    

    *head = NULL;
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    for (node_t *cur = head; cur != NULL; cur = cur->next)
        if (comparator(cur->data, data) == 0)
            return cur;

    return NULL;
}

void *pop_front(node_t **head)
{
    if (!head)
        return NULL;
    
    if (!(*head))
        return NULL;
    
    node_t *tmp = (*head);
    void *data = tmp->data;
    (*head) = tmp->next;

    node_free(tmp);

    return data;
}

void *pop_back(node_t **head)
{
    if (!head)
        return NULL;

    if (!(*head))
        return NULL;

    void *data;
    if ((*head)->next == NULL)
    {
        data = (*head)->data;
        node_free((*head));
        (*head) = NULL;
        return data;
    }
    node_t *prev = (*head), *cur = (*head)->next;
    while (cur->next != NULL)
    {
        prev = cur;
        cur = cur->next;
    }
    prev->next = NULL;

    data = cur->data;
    node_free(cur);

    return data;
}

void append(node_t **head_a, node_t **head_b)
{
    if (!(*head_a))
    {
        (*head_a) = (*head_b);
        *head_b = NULL;
    }
    else if (!(*head_b))
    {
        return;
    }
    else
    {
        node_t *tail_a = (*head_a);

        for (; tail_a->next != NULL; tail_a = tail_a->next);

        tail_a->next = (*head_b);
        *head_b = NULL;
    }
}

void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *))
{
    if (!comparator)
        return;

    if (*head == NULL || (*head)->next == NULL)
        return;

    for (node_t *i = (*head); i->next != NULL; i = i->next)
    {
        node_t *prev = i;
        for (node_t *j = i->next; j != NULL; j = j->next)
        {
            if (comparator(i->data, j->data) == 0)
            {
                prev->next = j->next;
                node_free(j);
                j = prev;
            }
            else
                prev = j;
        }
        if (prev == i)
            break;
    }
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (!head)
        return NULL;
    
    if (head->next == NULL)
        return head;

    node_t *left_part = head;
    node_t *right_part = NULL;

    front_back_split(left_part, &right_part);

    left_part = sort(left_part, comparator);
    right_part = sort(right_part, comparator);

    return sorted_merge(&left_part, &right_part, comparator);
}

void front_back_split(node_t *head, node_t **back)
{
    if (!head)
        return;

    if (!head->next)
        return;

    if (!back)
        return;

    size_t size = 1;
    node_t *tmp = head;

    for (; tmp->next; tmp = tmp->next)
        size++;

    size_t front_size = size / 2 + size % 2;

    node_t *mid = head;
    for (size_t i = 0; i < front_size - 1; i++)
        mid = mid->next;

    (*back) = mid->next;
    mid->next = NULL;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    if (!comparator)
        return NULL;

    node_t *result = NULL;

    if (!head_a || !(*head_a))
    {
        result = *head_b;
        *head_b = NULL;
        return result;
    }

    if (!head_b || !(*head_b))
    {
        result = *head_a;
        *head_a = NULL;
        return result;
    }

    if (comparator((*head_a)->data, (*head_b)->data) > 0)
    {
        result = *head_b;
        result->next = sorted_merge(head_a, &(*head_b)->next, comparator);
    }
    else
    {
        result = *head_a;
        result->next = sorted_merge(&(*head_a)->next, head_b, comparator);
    }

    *head_a = NULL;
    *head_b = NULL;

    return result;
}

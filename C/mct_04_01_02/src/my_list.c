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

int list_del_node(node_t **head, node_t *del_node)
{
    if (!del_node)
        return ERROR_INVALID_NODE;

    if (*head == del_node)
    {
        node_t *tmp = NULL;
        tmp = *head;
        *head = (*head)->next;
        node_free(&tmp);
    }
    else
    {
        node_t *prev = *head;
        for (; prev->next != del_node; prev = prev->next);
        prev->next = del_node->next;
        node_free(&del_node);
    }

    return EXIT_SUCCESS;
}


node_t *find_n_min(node_t *head, size_t n)
{
    if (list_size(head) < n)
        return NULL;

    node_t *mins[n];
    for (size_t i = 0; i < n; i++)
        mins[i] = NULL;


    for (node_t *cur = head; cur != NULL; cur = cur->next)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (mins[i] == NULL)
            {
                mins[i] = cur;
                break;
            }
            if (mins[i]->data > cur->data)
            {
                node_t *tmp = mins[i];
                mins[i] = cur;
                for (size_t j = i + 1; j < n; j++)
                {
                    if (mins[j])
                    {
                        node_t *t = mins[j];
                        mins[j] = tmp;
                        tmp = t;
                    }
                    else
                    {
                        mins[j] = tmp;
                        tmp = NULL;
                        break;
                    }
                }
                break;
            }
        }
    }

    return mins[n - 1];
}

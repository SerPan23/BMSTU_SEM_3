#include "my_list.h"

#define ERROR_INVALID_NUM 10

int main(void)
{
    int rc;
    long n = 0;

    printf("Enter el count:\n");
    if (scanf("%ld", &n) != 1)
        return ERROR_INVALID_NUM;

    node_t *head = NULL;

    for (size_t i = 0; i < (size_t) n; i++)
    {
        int tmp;
        printf("Enter next el:\n");
        if (scanf("%d", &tmp) != 1)
            return ERROR_INVALID_NUM;

        rc = list_push(&head, tmp);
        if (rc != EXIT_SUCCESS)
        {
            list_free(&head);
            return rc;
        }
    }

    node_t *maxx = find_max(head);

    if (!maxx)
    {
        list_free(&head);
        return ERROR_NODE_NOT_FOUND;
    }

    rc = list_swap_second_and_el(&head, maxx);
    if (rc != EXIT_SUCCESS)
    {
        list_free(&head);
        return rc;
    }

    list_print(head);

    list_free(&head);

    return 0;
}

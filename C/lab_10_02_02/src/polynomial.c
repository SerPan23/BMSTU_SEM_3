#include "polynomial.h"

int pnode_alloc(pnode_t **pnode)
{
    (*pnode) = malloc(sizeof(pnode_t));
    if (!(*pnode))
        return ERROR_NODE_ALLOC;

    (*pnode)->coefficient = 0;
    (*pnode)->next = NULL;

    return EXIT_SUCCESS;
}

void pnode_free(pnode_t **pnode)
{
    if (!pnode)
        return;

    if (!(*pnode))
        return;
    
    free(*pnode);
    *pnode = NULL;
}

void pnode_print(pnode_t *pnode)
{
    printf("%d ", pnode->coefficient);
}

int pnode_create(pnode_t **pnode, int coefficient)
{
    int rc = pnode_alloc(pnode);
    if (rc != EXIT_SUCCESS)
        return rc;
    (*pnode)->coefficient = coefficient;
    (*pnode)->next = NULL;
    return EXIT_SUCCESS;
}

int pnode_scan(FILE *f, pnode_t **pnode)
{
    int tmp;
    if (fscanf(f, "%d", &tmp) != 1)
    {
        return ERROR_WRONG_INPUT;
    }
    return pnode_create(pnode, tmp);
}

void polynomial_free(polynomial_t *polynomial)
{
    if (polynomial->size == 0)
        return;
    
    pnode_t *next = NULL;

    for (; polynomial->list_head != NULL; polynomial->list_head = next)
    {
        next = polynomial->list_head->next;
        pnode_free(&polynomial->list_head);
    }

    polynomial->size = 0;
}

int polynomial_push(polynomial_t *polynomial, pnode_t *new_node)
{
    if (polynomial->list_head == NULL)
    {
        polynomial->list_head = new_node;
        polynomial->size++;
    }
    else
    {
        pnode_t *tail = polynomial->list_head;
        for (; tail->next != NULL; tail = tail->next);
        tail->next = new_node;
        polynomial->size++;
    }
    return EXIT_SUCCESS;
}

int polynomial_print(polynomial_t *polynomial)
{
    if (polynomial->size == 0)
        return ERROR_LIST_EMPTY;
    
    for (pnode_t *cur = polynomial->list_head; cur != NULL; cur = cur->next)
        pnode_print(cur);
    printf("L\n");
    
    return EXIT_SUCCESS;
}

int polynomial_pop_front(polynomial_t *polynomial)
{
    if (polynomial->list_head == NULL)
        return ERROR_LIST_EMPTY;

    pnode_t *cur = polynomial->list_head;
    polynomial->list_head = cur->next;

    int data = cur->coefficient;
    pnode_free(&cur);
    polynomial->size--;
    return data;
}

int polynomial_pop(polynomial_t *polynomial)
{
    if (polynomial->list_head == NULL)
        return ERROR_LIST_EMPTY;

    int data;
    if (polynomial->list_head->next == NULL)
    {
        data = polynomial->list_head->coefficient;
        polynomial->list_head = NULL;
        polynomial->size--;
        return data;
    }
    pnode_t *prev = polynomial->list_head, *cur = polynomial->list_head->next;
    while (cur->next != NULL)
    {
        prev = cur;
        cur = cur->next;
    }
    prev->next = NULL;

    data = cur->coefficient;
    pnode_free(&cur);
    polynomial->size--;
    return data;
}

int polynomial_scan(polynomial_t *polynomial)
{
    long tmp;
    if (scanf("%ld", &tmp) != 1 || tmp < 0)
    {
        return ERROR_WRONG_INPUT;
    }
    polynomial->size = 0;

    int rc;
    for (size_t i = 0; i < (size_t)tmp; i++)
    {
        pnode_t *new_node = NULL;
        rc = pnode_scan(stdin, &new_node);
        if (rc != EXIT_SUCCESS)
        {
            pnode_free(&new_node);
            return rc;
        }
        rc = polynomial_push(polynomial, new_node);
        if (rc != EXIT_SUCCESS)
        {
            pnode_free(&new_node);
            return rc;
        }
    }

    return EXIT_SUCCESS;
}

int polynomial_val(polynomial_t *polynomial, int a)
{
    size_t i = 0;
    int result = 0;
    for (pnode_t *cur = polynomial->list_head; cur != NULL; cur = cur->next)
    {
        result += cur->coefficient * (int) pow(a, polynomial->size - 1 - i);
        i++;
    }
    return result;
}

int polynomial_ddx(polynomial_t *polynomial)
{
    size_t i = 0;
    for (pnode_t *cur = polynomial->list_head; cur != NULL; cur = cur->next)
    {
        cur->coefficient = cur->coefficient * (polynomial->size - 1 - i);
        i++;
    }
    polynomial_pop(polynomial);
    return EXIT_SUCCESS;
}

int polynomial_sum(polynomial_t *src_1, polynomial_t *src_2)
{
    if (src_1->size < src_2->size)
    {
        polynomial_t *tmp = src_1;
        src_1 = src_2;
        src_2 = tmp;
    }

    size_t i = 0;
    pnode_t *cur_1 = src_1->list_head;
    pnode_t *cur_2 = src_2->list_head;
    for (; cur_1 != NULL || cur_2 != NULL; cur_1 = cur_1->next)
    {
        if (src_1->size - i == src_2->size)
        {
            cur_1->coefficient = cur_1->coefficient + cur_2->coefficient;
            cur_2 = cur_2->next;
        }
        if (src_1->size - i > src_2->size)
            i++;
    }
    return EXIT_SUCCESS;
}

int polynomial_dvd(polynomial_t *polynomial, polynomial_t *even, polynomial_t *odd)
{
    if (!even || !odd)
        return ERROR_NO_ALLOC;

    int rc;
    int i = polynomial->size - 1;
    for (; i >= 0; i--)
    {
        int data = polynomial_pop_front(polynomial);
        pnode_t *new_node = NULL;
        rc = pnode_create(&new_node, data);
        if (rc != EXIT_SUCCESS)
            return rc; 
        
        if (i % 2 == 0)
        {
            rc = polynomial_push(even, new_node);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
        else
        {
            rc = polynomial_push(odd, new_node);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
    }
    return EXIT_SUCCESS;
}

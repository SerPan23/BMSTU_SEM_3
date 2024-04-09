#include "my_list.h"
#include "employee.h"

#define ERROR_INCORECT_ARGC 100

int create_list(employees_t *data, node_t **head)
{
    int rc;
    for (size_t i = 0; i < data->size; i++)
    {
        rc = list_push(head, (void *)data->data[i]);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    return EXIT_SUCCESS;
}

int separate_list(node_t **src, node_t **list_1, node_t **list_2, node_t **list_3)
{
    int rc;
    while (*src != NULL)
    {
        employee_t *el;
        el = pop_back(src);
        if (el->kpi > 85)
        {
            rc = list_push(list_1, (void *)el);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
        else if (el->kpi < 30)
        {
            rc = list_push(list_2, (void *)el);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
        else
        {
            rc = list_push(list_3, (void *)el);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
        el = pop_front(src);
        if (!el)
            break;
        if (el->kpi > 85)
        {
            rc = list_push(list_1, (void *)el);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
        else if (el->kpi < 30)
        {
            rc = list_push(list_2, (void *)el);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
        else
        {
            rc = list_push(list_3, (void *)el);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
    }
    return EXIT_SUCCESS;
}

void final_salary_calc_list_1(node_t *list)
{
    for (node_t *cur = list; cur != NULL; cur = cur->next)
    {
        employee_t *tmp = cur->data;
        tmp->final_salary += tmp->salary;
        if (tmp->kpi == 100)
            tmp->final_salary += tmp->salary / 10;
    }
}

void final_salary_calc_list_3(node_t *list)
{
    for (node_t *cur = list; cur != NULL; cur = cur->next)
    {
        employee_t *tmp = cur->data;
        tmp->final_salary += tmp->salary / 100 * tmp->kpi;
    }
}

int main(int argc, char **argv)
{
    int rc;

    if (argc != 3)
        return ERROR_INCORECT_ARGC;

    employees_t data;
    employees_alloc(&data);

    rc = employees_read(argv[1], &data);
    if (rc != EXIT_SUCCESS)
    {
        employees_free(&data);
        return rc;
    }

    node_t *head = NULL;
    rc = create_list(&data, &head);
    if (rc != EXIT_SUCCESS)
    {
        list_free(&head);
        employees_free(&data);
        return rc;
    }

    head = sort(head, employee_cmp_by_kpi_rev);
    remove_duplicates(&head, employee_cmp_by_id);

    node_t *list_1 = NULL;
    node_t *list_2 = NULL;
    node_t *list_3 = NULL;
    rc = separate_list(&head, &list_1, &list_2, &list_3);
    if (rc != EXIT_SUCCESS)
    {
        list_free(&head);
        list_free(&list_1);
        list_free(&list_2);
        list_free(&list_3);
        employees_free(&data);
    }
    head = NULL;

    final_salary_calc_list_1(list_1);
    final_salary_calc_list_3(list_3);

    append(&list_1, &list_2);
    append(&list_1, &list_3);
    head = list_1;
    list_1 = NULL;

    head = sort(head, employee_cmp_fsal_rev);

    FILE *out;
    out = fopen(argv[2], "w");
    if (out == NULL)
    {
        list_free(&head);
        employees_free(&data);
        return ERROR_WRONG_FILEPATH;
    }

    list_print(head, employee_print, out);


    fclose(out);

    // list_print(head, employee_print, stdout);

    list_free(&head);

    employees_free(&data);

    return 0;
}

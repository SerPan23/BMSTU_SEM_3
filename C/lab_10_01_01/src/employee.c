#include "employee.h"

int employee_alloc(employee_t **employee)
{
    (*employee) = malloc(sizeof(employee_t));
    if (!(*employee))
        return ERROR_MEM_ALLOC;

    return EXIT_SUCCESS;
}

void employee_free(employee_t **employee)
{
    if (!(*employee))
        free(*employee);

    *employee = NULL;
}

void employee_print(FILE *f, void *data)
{
    employee_t *employee = data;
    fprintf(f, "%zu\n", employee->id);
    fprintf(f, "%s\n", employee->name);
    fprintf(f, "%d\n", employee->kpi);
    fprintf(f, "%d\n", employee->salary);
    fprintf(f, "%d\n", employee->final_salary);
}

int employee_cmp_by_id(const void *va, const void *vb)
{
    const employee_t *a = va;
    const employee_t *b = vb;
    return (long)a->id - (long)b->id;
}

int employee_cmp_by_kpi_rev(const void *va, const void *vb)
{
    const employee_t *a = va;
    const employee_t *b = vb;
    return b->kpi - a->kpi;
}

int employee_cmp_fsal_rev(const void *va, const void *vb)
{
    const employee_t *a = va;
    const employee_t *b = vb;
    return b->final_salary - a->final_salary;
}

int read_str(FILE *f, char **s, size_t *len)
{
    ssize_t read;

    char *tmp = NULL;

    if ((read = getline(&tmp, len, f)) == -1)
    {
        free(tmp);
        return ERROR_EMPTY_INPUT;
    }

    if (len == 0)
    {
        free(tmp);
        return ERROR_EMPTY_INPUT;
    }

    tmp[strcspn(tmp, "\n")] = '\0';
    *s = tmp;

    return EXIT_SUCCESS;
}

int employee_fill(employee_t **employee, size_t id, char *s, int kpi, int salary)
{
    int rc = employee_alloc(employee);
    if (rc != EXIT_SUCCESS)
        return rc;

    (*employee)->id = id;
    (*employee)->name = s;
    if (s)
        (*employee)->name_len = strlen(s);
    (*employee)->kpi = kpi;
    (*employee)->salary = salary;
    (*employee)->final_salary = salary;

    return EXIT_SUCCESS;
}

int employee_scan(FILE *f, employee_t **employee)
{
    long id = 0;
    if (fscanf(f, "%ld\n", &id) != 1)
    {
        return ERROR_WRONG_INPUT;
    }

    char *tmp_s = NULL;
    size_t len = 0;
    int rc = read_str(f, &tmp_s, &len);

    if (rc != EXIT_SUCCESS)
        return rc;

    int kpi = 0, salary = 0;

    if (fscanf(f, "%d\n", &kpi) != 1)
    {
        free(tmp_s);
        return ERROR_WRONG_INPUT;
    }

    if (fscanf(f, "%d\n", &salary) != 1)
    {
        free(tmp_s);
        return ERROR_WRONG_INPUT;
    }

    if (id < 0 || kpi <= 0 || kpi > 100 || salary <= 0)
    {
        free(tmp_s);
        return ERROR_INCORRECT_NUM_VALUE;
    }

    rc = employee_fill(employee, (size_t) id, tmp_s, kpi, salary);
    if (rc != EXIT_SUCCESS)
    {
        free(tmp_s);
        return rc;
    }

    return EXIT_SUCCESS;
}

int employees_alloc(employees_t *employees)
{
    employees->data = malloc(EMPLOYEES_CAPACITY_SIZE * sizeof(employee_t *));
    if (!employees->data)
        return ERROR_MEM_ALLOC;

    employees->size = 0;
    employees->size_alloc = EMPLOYEES_CAPACITY_SIZE;

    return EXIT_SUCCESS;
}

void employees_free(employees_t *employees)
{
    if (employees->size_alloc == 0)
        return;
    
    for (size_t i = 0; i < employees->size; i++)
        employee_free(&employees->data[i]);

    employees->size_alloc = 0;
    employees->size = 0;
    employees->data = NULL;
}

int employees_realloc(employees_t *employees, size_t new_size)
{
    void *tmp = realloc(employees->data, new_size * sizeof(employee_t *));
    if (!tmp)
        return ERROR_MEM_ALLOC;

    employees->data = tmp;

    employees->size_alloc = new_size;

    return EXIT_SUCCESS;
}

int employees_push(employees_t *employees, employee_t *employee)
{
    int rc;
    if (employees->size + 1 > employees->size_alloc)
    {
        rc = employees_realloc(employees, employees->size_alloc + EMPLOYEES_CAPACITY_SIZE);
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    employees->data[employees->size++] = employee; 

    return EXIT_SUCCESS;
}

void employees_print(employees_t *employees)
{
    for (size_t i = 0; i < employees->size; i++)
        employee_print(stdout, employees->data[i]);
}

int employees_read(char *filepath, employees_t *employees)
{
    FILE *f;
    f = fopen(filepath, "r");
    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    employee_t *tmp = NULL;
    int rc;
    while ((rc = employee_scan(f, &tmp)) == EXIT_SUCCESS)
    {
        rc = employees_push(employees, tmp);
        if (rc != EXIT_SUCCESS)
        {
            employee_free(&tmp);
            fclose(f);
            return rc;
        }
        tmp = NULL;
    }

    if (employees->size == 0)
    {
        fclose(f);
        return ERROR_EMPTY_FILE;
    }
    if (rc != ERROR_EMPTY_INPUT && rc != EXIT_SUCCESS && !feof(f))
    {
        fclose(f);
        return rc;
    }
    fclose(f);
    return EXIT_SUCCESS;
}

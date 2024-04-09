#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define _GNU_SOURCE

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define EMPLOYEES_CAPACITY_SIZE 20

#define ERROR_MEM_ALLOC 10
#define ERROR_EMPTY_INPUT 11
#define ERROR_WRONG_INPUT 12
#define ERROR_INCORRECT_NUM_VALUE 13
#define ERROR_WRONG_FILEPATH 14
#define ERROR_EMPTY_FILE 15

typedef struct employee
{
    size_t id;
    char *name;
    size_t name_len;
    int kpi;
    int salary;
    int final_salary;
} employee_t;

int employee_alloc(employee_t **employee);
void employee_free(employee_t **employee);
void employee_print(FILE *f, void *);
int employee_scan(FILE *f, employee_t **employee);
int employee_fill(employee_t **employee, size_t id, char *s, int kpi, int salary);

int employee_cmp_by_id(const void *, const void *);
int employee_cmp_by_kpi_rev(const void *va, const void *vb);
int employee_cmp_fsal_rev(const void *va, const void *vb);

typedef struct employees
{
    employee_t **data;
    size_t size;
    size_t size_alloc;
} employees_t;

int employees_alloc(employees_t *employees);
void employees_free(employees_t *employees);
int employees_realloc(employees_t *employees, size_t new_size);
int employees_push(employees_t *employees, employee_t *employee);
void employees_print(employees_t *employees);
void employees_print_file(char *filepath, employees_t *employees);
int employees_read(char *filepath, employees_t *employees);


#endif
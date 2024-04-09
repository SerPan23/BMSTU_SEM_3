#include "item.h"

int read_name(FILE *f, char **s, size_t *len)
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

int item_fill(item_t **item, char *s, double *weight, double *volume)
{
    int rc = item_create(item);
    if (rc != EXIT_SUCCESS)
        return rc;

    // printf("%s %d\n", s, (int)strlen(s));
    (*item)->name = s;
    if (s)
        (*item)->name_len = strlen(s);
    (*item)->weight = *weight;
    (*item)->volume = *volume;

    return EXIT_SUCCESS;
}

int item_scan(FILE *f, item_t **item)
{
    char *tmp_s = NULL;
    size_t len = 0;
    int rc = read_name(f, &tmp_s, &len);

    if (rc != EXIT_SUCCESS)
        return rc;

    double tmp_weight = 0, tmp_volume = 0;

    if (fscanf(f, "%lf\n", &tmp_weight) != 1)
    {
        free(tmp_s);
        return ERROR_WRONG_INPUT;
    }

    if (fscanf(f, "%lf\n", &tmp_volume) != 1)
    {
        free(tmp_s);
        return ERROR_WRONG_INPUT;
    }

    if (tmp_weight <= 0 || tmp_volume <= 0)
    {
        free(tmp_s);
        return ERROR_INCORRECT_NUM_VALUE;
    }

    // strncpy(item->name, s, MAX_NAME_LEN + 1);

    rc = item_fill(item, tmp_s, &tmp_weight, &tmp_volume);
    if (rc != EXIT_SUCCESS)
    {
        free(tmp_s);
        return rc;
    }

    // printf("%lf %lf\n", item->weight, item->volume);
    return EXIT_SUCCESS;
}

void item_print(item_t *item)
{
    printf("%s\n%.6lf\n%.6lf\n", item->name, item->weight, item->volume);
}

int item_create(item_t **item)
{
    *item = calloc(1, sizeof(item_t));

    if (!item)
        return ERROR_MEM_ALLOC;

    (*item)->name = NULL;
    (*item)->name_len = 0;
    (*item)->weight = 0;
    (*item)->volume = 0;

    return EXIT_SUCCESS;
}

void item_free(item_t *item)
{
    if (item->name_len != 0)
        free(item->name);
    item->name = NULL;
    free(item);
}

int item_cmp_by_density(item_t *it1, item_t *it2)
{
    double t1 = it1->weight / it1->volume;
    double t2 = it2->weight / it2->volume;

    double t = t1 - t2;

    if (t < 0)
        return -1;

    if (t > EPS)
        return 1;

    return 0;
}

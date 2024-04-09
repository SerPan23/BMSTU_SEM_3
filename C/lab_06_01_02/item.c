#include "item.h"

int read_name(FILE *f, char *s)
{
    char tmp_string[MAX_NAME_LEN + 2];

    if (fgets(tmp_string, MAX_NAME_LEN + 2, f) == NULL)
        return ERROR_EMPTY_INPUT;

    tmp_string[strcspn(tmp_string, "\n")] = '\0';

    if (strlen(tmp_string) > MAX_NAME_LEN || strlen(tmp_string) == 0)
        return ERROR_NAME_LEN;

    strncpy(s, tmp_string, MAX_NAME_LEN + 1);

    return EXIT_SUCCESS;
}

int scan_item(FILE *f, item_t *item)
{
    char s[MAX_NAME_LEN + 1];
    int rc = read_name(f, s);

    if (rc != EXIT_SUCCESS)
        return rc;

    double tmp_weight, tmp_volume;

    if (fscanf(f, "%lf\n", &tmp_weight) != 1)
        return ERROR_WRONG_INPUT;

    if (fscanf(f, "%lf\n", &tmp_volume) != 1)
        return ERROR_WRONG_INPUT;

    if (tmp_weight <= 0 || tmp_volume <= 0)
        return ERROR_INCORRECT_NUM_VALUE;

    strncpy(item->name, s, MAX_NAME_LEN + 1);
    item->weight = tmp_weight;
    item->volume = tmp_volume;

    return EXIT_SUCCESS;
}

void print_item(item_t item)
{
    printf("%s\n%.6lf\n%.6lf\n", item.name, item.weight, item.volume);
}

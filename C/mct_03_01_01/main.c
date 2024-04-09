#include "array.h"

int main(void)
{
    int rc;

    int size = 0;

    printf("Enter array size:\n");
    if (scanf("%d", &size) != 1 || size < 0)
        return ERROR_INVALID_SIZE;

    array_t arr;
    rc = array_alloc(&arr, (size_t)size);
    if (rc != EXIT_SUCCESS)
        return rc;

    printf("Enter array data:\n");
    rc = array_fill(&arr);
    if (rc != EXIT_SUCCESS)
    {
        array_free(&arr);
        return rc;
    }

    rc = del_nums_dels_on_3(&arr);
    if (rc != EXIT_SUCCESS)
    {
        array_free(&arr);
        return rc;
    }

    array_print(&arr);
    printf("\n");

    array_free(&arr);

    return 0;
}

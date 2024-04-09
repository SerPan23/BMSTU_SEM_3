#include "matrix.h"

int main(void)
{
    int rc;
    int n, m;

    printf("Enter matrix row count:\n");
    if (scanf("%d", &n) != 1 || n < 0)
        return ERROR_INVALID_ROW_COUNT;

    printf("Enter matrix col count:\n");
    if (scanf("%d", &m) != 1 || m < 0)
        return ERROR_INVALID_COL_COUNT;

    matrix_t mat;

    rc = matrix_alloc(&mat, (size_t)n, (size_t)m);
    if (rc != EXIT_SUCCESS)
        return rc;

    printf("Enter matrix elements:\n");
    rc = matrix_fill(&mat);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat);
        return rc;
    }

    rc = del_col_with_max(&mat);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat);
        return rc;
    }

    matrix_print(&mat);

    matrix_free(&mat);

    return 0;
}

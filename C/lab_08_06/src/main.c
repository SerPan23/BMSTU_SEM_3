#include "my_matrix.h"

int main(void)
{
    int rc = EXIT_SUCCESS;

    matrix_t mat_a = { NULL, 0, 0 };

    printf("Enter matrix A row count:\n");
    if (scanf("%zu", &mat_a.n) != 1 || mat_a.n < 1)
        return ERROR_READ_N;

    printf("Enter matrix A column count:\n");
    if (scanf("%zu", &mat_a.m) != 1 || mat_a.m < 1)
        return ERROR_READ_M;

    rc = matrix_alloc(&mat_a);
    if (rc != EXIT_SUCCESS)
        return rc;

    printf("Enter matrix A elements:\n");
    rc = matrix_read(&mat_a);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        return rc;
    }

    matrix_t mat_b = { NULL, 0, 0 };

    printf("Enter matrix B row count:\n");
    if (scanf("%zu", &mat_b.n) != 1 || mat_b.n < 1)
    {
        matrix_free(&mat_a);
        return ERROR_READ_P;
    }

    printf("Enter matrix B column count:\n");
    if (scanf("%zu", &mat_b.m) != 1 || mat_b.m < 1)
    {
        matrix_free(&mat_a);
        return ERROR_READ_Q;
    }

    rc = matrix_alloc(&mat_b);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        return rc;
    }

    printf("Enter matrix B elements:\n");
    rc = matrix_read(&mat_b);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return rc;
    }

    size_t r, g;

    printf("Enter A power:\n");
    if (scanf("%zu", &r) != 1)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return ERROR_READ_R;
    }

    printf("Enter B power:\n");
    if (scanf("%zu", &g) != 1)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return ERROR_READ_G;
    }

    rc = matrix_to_square_form(&mat_a);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return rc;
    }
    rc = matrix_to_square_form(&mat_b);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return rc;
    }

    size_t max_size;
    if (mat_a.n > mat_b.n)
        max_size = mat_a.n;
    else
        max_size = mat_b.n;
    
    rc = matrix_to_new_size(&mat_a, max_size);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return rc;
    }
    rc = matrix_to_new_size(&mat_b, max_size);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return rc;
    }

    rc = matrix_pow(&mat_a, r);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return rc;
    }
    rc = matrix_pow(&mat_b, g);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return rc;
    }

    matrix_t result = { NULL, 0, 0 };
    rc = matrix_mul(&mat_a, &mat_b, &result);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&mat_a);
        matrix_free(&mat_b);
        return rc;
    }

    // matrix_print(&mat_a);
    // printf("\n");
    // matrix_print(&mat_b);
    // printf("\n");
    matrix_print(&result);

    matrix_free(&mat_a);
    matrix_free(&mat_b);
    matrix_free(&result);
    return rc;
}

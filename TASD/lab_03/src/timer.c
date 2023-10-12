#include "time.h"
#include "matrix.h"
#include "vector.h"
#include "matrix_operations.h"

char *header = "┌───────────┬───────────────┬─────────────────────────┬────────────────────┬─────────────────────────┐\n";
char *sep    = "├───────────┼───────────────┼─────────────────────────┼────────────────────┼─────────────────────────┤\n";
char *footer = "└───────────┴───────────────┴─────────────────────────┴────────────────────┴─────────────────────────┘\n";

void print_table_header(void)
{
    printf("%s", header);
    printf("│%11s│%15s│%25s│%20s│%25s│\n", "Size", "matrix time(ns)", 
        "sparse matrix time(ns)", "matrix size(bytes)", "sparse matrix size(bytes)");
    printf("%s", sep);
}
void print_table_footer(void)
{
    printf("%s", footer);
}

int print_time(size_t n, size_t nums_count)
{
    vector_t vec, vec_res;
    vec.row_count = n;
    vec.len = n;
    int rc = vector_alloc(&vec);
    if (rc != EXIT_SUCCESS)
    {
        printf("ERROR: MEM ALLOC");
        return rc;
    }
    vector_random_fill(&vec);

    matrix_t mat;
    sparse_matrix_t s_mat;
    mat.n = n;
    mat.m = n;
    rc = matrix_alloc(&mat);
    if (rc != EXIT_SUCCESS)
    {
        free_vector(&vec);
        printf("ERROR: MEM ALLOC");
        return rc;
    }

    matrix_random_fill(&mat, &nums_count);
    s_mat.n = n;
    s_mat.m = n;
    s_mat.nums_count = nums_count;
    matrix_to_sparse_matrix(&mat, &s_mat, &nums_count);

    long time1, time2;
    long sum1 = 0, sum2 = 0;

    struct timespec begin, end;

    vec_res.len = n;
    vec_res.row_count = n;
    rc = vector_alloc(&vec_res);
    if (rc != EXIT_SUCCESS)
    {
        free_vector(&vec);
        free_matrix(&mat);
        free_sparse_matrix(&s_mat);
        printf("ERROR: MEM ALLOC");
        return rc;
    }

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);
        matrix_mul_vec(&mat, &vec, &vec_res);
        clock_gettime(CLOCK_REALTIME, &end);
        sum1 += delta_time(begin, end);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    free_vector(&vec_res);
    vec_res.len = n;
    vec_res.row_count = n;
    rc = vector_alloc(&vec_res);
    if (rc != EXIT_SUCCESS)
    {
        printf("ERROR: MEM ALLOC");
        return rc;
    }

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);
        sparse_matrix_mul_vec(&s_mat, &vec, &vec_res);
        clock_gettime(CLOCK_REALTIME, &end);
        sum2 += delta_time(begin, end);
    }
    time2 = sum2 / ITER_COUNT_TIME;

    size_t size1 = mat.n * mat.m * sizeof(int);
    size_t size2 = s_mat.nums_count * sizeof(int) + s_mat.nums_count * sizeof(size_t) + (s_mat.n + 1) * sizeof(size_t);
    printf("│%5zux%-5zu", n, n);
    printf("│%15lu│%25lu│", time1, time2);
    printf("%20zu│%25zu│\n", size1, size2);

    free_vector(&vec);
    free_vector(&vec_res);
    free_matrix(&mat);
    free_sparse_matrix(&s_mat);
    return EXIT_SUCCESS;
}

void print_time_measurements(void)
{
    size_t sizes[] = {10, 100, 500};
    size_t sizes_len = sizeof(sizes) / sizeof(sizes[0]);

    size_t per_filing[] = {10, 25, 50, 85, 100};
    size_t per_filing_len = sizeof(per_filing) / sizeof(per_filing[0]);

    for (size_t j = 0; j < per_filing_len; j++)
    {
        printf("%zu%% FILLING\n", per_filing[j]);
        printf("\n");
        print_table_header();
        for (size_t i = 0; i < sizes_len; i++)
        {
            // n*n - 100
            // x - per
            // x = n*n*per / 100
            size_t nums = (sizes[i] * sizes[i] * per_filing[j]) / 100;
            print_time(sizes[i], nums);
        }
        print_table_footer();
        printf("\n");
    }
}

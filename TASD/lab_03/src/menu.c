#include "menu.h"
#include "matrix.h"
#include "matrix_operations.h"

#define MENU_ITEMS_COUNT 6

void print_menu(void)
{
    printf("------------------\n");
    printf("Menu:\n\
    1) Read matrix\n\
    2) Read vector\n\
    3) Print matrix\n\
    4) Print vector\n\
    5) Multiplication matrix and vector\n\
    6) Print results of multiplication using various matrix types\n\
    0) Quit program\n");
    printf("------------------\n");
}

int choose_menu_item(int *command)
{
    printf("Choose menu item (0-%d):\n", MENU_ITEMS_COUNT);
    if (read_int(command, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        return ERROR_WRONG_MENU_ITEM;
    if (*command < 0 || *command > MENU_ITEMS_COUNT)
        return ERROR_WRONG_MENU_ITEM;
    return EXIT_SUCCESS;
}

int menu(void)
{
    int command = -1, is_mat_read = 0, is_vec_read = 0, is_vec_res = 0;
    matrix_t mat;
    sparse_matrix_t s_mat;
    size_t nums_count = 0;

    vector_t vec, vec_res;
    while (command != 0)
    {
        print_menu();
        int rc = choose_menu_item(&command);
        if (rc != EXIT_SUCCESS)
        {
            printf("ERROR: wrong choose, you need enter numbers from 0 to %d\n", MENU_ITEMS_COUNT);
            continue;
        }
        if (command == 0)
            break;
        else if (command == 1 || command == 2 || command == 6)
        {
            if (command == 1)
            {
                int c = -1;
                rc = EXIT_SUCCESS;
                do {
                    printf("Choose fill method:\n"
                           "1) Console fill\n"
                           "2) Random fill\n");
                    if (read_int(&c, MAX_STR_LEN, stdin) != EXIT_SUCCESS || c < 1 || c > 2)
                    {
                        printf("ERROR: wrong choose, you need enter numbers from 1 to 2\n");
                        rc =  ERROR_INVALID_NUM;
                        continue;
                    }
                    rc = EXIT_SUCCESS;
                } while (rc != EXIT_SUCCESS);
                read_matrix(&mat, &nums_count, c - 1, stdin);
                matrix_to_sparse_matrix(&mat, &s_mat, &nums_count);
                is_mat_read = 1;
            }
            else if (command == 2)
            {
                int c = -1;
                rc = EXIT_SUCCESS;
                do
                {
                    printf("Choose fill method:\n"
                           "1) Console fill\n"
                           "2) Random fill\n");
                    if (read_int(&c, MAX_STR_LEN, stdin) != EXIT_SUCCESS || c < 1 || c > 2)
                    {
                        printf("ERROR: wrong choose, you need enter numbers from 1 to 2\n");
                        rc = ERROR_INVALID_NUM;
                        continue;
                    }
                    rc = EXIT_SUCCESS;
                } while (rc != EXIT_SUCCESS);
                read_vector(&vec, c - 1, stdin);
                is_vec_read = 1;
            }
            else if (command == 6)
            {
                print_time_measurements();
            }
        }
        else if (is_mat_read || is_vec_read)
        {
            if (command == 3)
            {
                if (!is_mat_read)
                {
                    printf("ERROR: you need read matrix before this command!\n");
                    continue;
                }
                if (s_mat.n <= MAX_PRINT_MAT &&s_mat.m <= MAX_PRINT_MAT)
                {
                    print_matrix(&mat, stdout);
                    printf("\n");
                }
                print_sparse_matrix(&s_mat, stdout);
            }
            else if (command == 4)
            {
                if (!is_vec_read)
                {
                    printf("ERROR: you need read matrix before this command!\n");
                    continue;
                }
                print_vector(&vec, stdout);
            }

            if (command == 5)
            {
                if (!is_mat_read || !is_vec_read)
                {
                    printf("ERROR: you need read matrix and vector before this command!\n");
                    continue;
                }
                if (s_mat.m != vec.row_count)
                {
                    printf("ERROR: it is necessary that matrix number of columns coincides\n\
                    with the number of rows of the vector!\n");
                    printf("You need change vector or matrix\n");
                    continue;
                }
                vec_res.len = s_mat.n;
                vec_res.row_count = s_mat.n;
                rc = vector_alloc(&vec_res);
                is_vec_res = 1;
                if (rc != EXIT_SUCCESS)
                {
                    free_sparse_matrix(&s_mat);
                    free_matrix(&mat);
                    free_vector(&vec);
                    return rc;
                }

                sparse_matrix_mul_vec(&s_mat, &vec, &vec_res);

                vector_del_zero_els(&vec_res);

                printf("\n------multiplication result------\n");
                print_vector(&vec_res, stdout);
            }
        }
        else
            printf("ERROR: you need read matrix or vector before also commands!\n");
    }

    if (is_mat_read)
    {
        free_sparse_matrix(&s_mat);
        free_matrix(&mat);
    }
    if (is_vec_read)
        free_vector(&vec);
    if (is_vec_res)
        free_vector(&vec_res);

    // matrix_t mat;
    // sparse_matrix_t s_mat;
    // size_t nums_count = 0;

    // vector_t vec, vec_res, vec_res_2;

    // printf("menu\n");
    
    // read_matrix(&mat, &nums_count, stdin);

    // matrix_to_sparse_matrix(&mat, &s_mat, &nums_count);

    // read_vector(&vec, stdin);

    // printf("\n-------------\n");
    // print_matrix(&mat, stdout);

    // printf("\n-------------\n");
    // print_sparse_matrix(&s_mat, stdout);

    // printf("\n-------------\n");
    // print_vector(&vec, stdout);

    // if (mat.m != vec.row_count)
    //     return ERROR_SIZE_COHERENCE;
    // vec_res.len = mat.n;
    // vec_res.row_count = mat.n;
    // int rc = vector_alloc(&vec_res);
    // if (rc != EXIT_SUCCESS)
    //     return rc;

    // matrix_mul_vec(&mat, &vec, &vec_res);

    // printf("\n------result_tmp------\n");
    // print_vector(&vec_res, stdout);

    // vector_del_zero_els(&vec_res);

    // printf("\n------result------\n");
    // print_vector(&vec_res, stdout);



    // if (s_mat.m != vec.row_count)
    //     return ERROR_SIZE_COHERENCE;
    // vec_res_2.len = s_mat.n;
    // vec_res_2.row_count = s_mat.n;
    // rc = vector_alloc(&vec_res_2);
    // if (rc != EXIT_SUCCESS)
    //     return rc;

    // sparse_matrix_mul_vec(&s_mat, &vec, &vec_res_2);

    // printf("\n------result2_tmp------\n");
    // print_vector(&vec_res_2, stdout);

    // vector_del_zero_els(&vec_res_2);

    // printf("\n------result2------\n");
    // print_vector(&vec_res_2, stdout);

    // matrix_t mat2;
    // mat2.n = s_mat->n;
    // mat2.m = s_mat->m;
    // matrix_alloc(&mat2);
    // sparse_matrix_to_matrix(s_mat, &mat2);
    // printf("\n-------------\n");
    // print_matrix(&mat2, stdout);
    // free_matrix(&mat2);
    return EXIT_SUCCESS;
}

#include "filter_lib.h"

#define ERROR_FEW_ARGS 1
#define ERROR_A_LOT_ARGS 2
#define ERROR_INVALID_ARG 3
#define ERROR_WRONG_IN_FILEPATH 4
#define ERROR_WRONG_OUT_FILEPATH 5
#define ERROR_CREATE_ARR 7
#define ERROR_EMPTY_FILE 10

int main(int argc, char **argv)
{
    if (argc < 3)
        return ERROR_FEW_ARGS;
    if (argc > 4)
        return ERROR_A_LOT_ARGS;

    if (argc == 4 && strcmp(argv[3], "f") != 0)
        return ERROR_INVALID_ARG;

    FILE *f_in = fopen(argv[1], "r");

    if (f_in == NULL)
        return ERROR_WRONG_IN_FILEPATH;

    FILE *f_out = fopen(argv[2], "w");

    if (f_out == NULL)
    {
        fclose(f_in);
        return ERROR_WRONG_OUT_FILEPATH;
    }

    size_t n = 0;

    int rc = find_file_len(f_in, &n);

    if (rc != EXIT_SUCCESS)
    {
        fclose(f_in);
        fclose(f_out);
        return rc;
    }

    if (n == 0)
    {
        fclose(f_in);
        fclose(f_out);
        return ERROR_EMPTY_FILE;
    }

    int *pb = NULL, *pe = NULL;
    pb = calloc(n, sizeof(int));
    if (!pb)
    {
        fclose(f_in);
        fclose(f_out);
        return ERROR_CREATE_ARR;
    }
    pe = pb + n;

    rc = read_file(f_in, pb, pe);
    if (rc != EXIT_SUCCESS)
    {
        fclose(f_in);
        fclose(f_out);
        free(pb);
        return rc;
    }

    int *pb_new = NULL;
    int *pe_new = NULL;

    if (argc == 4)
    {
        size_t new_nmemb = find_new_arr_len(pb, pe);

        if (new_nmemb == 0)
            return ERROR_EMPTY_RESULT;
        
        pb_new = calloc(new_nmemb, sizeof(int));
        if (!pb_new)
            return ERROR_CREATE_ARR;
        pe_new = pb_new + new_nmemb;

        rc = key(pb, pe, &pb_new, &pe_new);
        if (rc != EXIT_SUCCESS)
        {
            fclose(f_in);
            fclose(f_out);
            free(pb);
            free(pb_new);
            return rc;
        }
        mysort(pb_new, pe_new - pb_new, sizeof(int), cmp_int);
        print_arr(f_out, pb_new, pe_new);
    }
    else
    {
        mysort(pb, pe - pb, sizeof(int), cmp_int);
        print_arr(f_out, pb, pe);
    }

    fclose(f_in);
    fclose(f_out);
    free(pb);
    free(pb_new);

    return 0;
}

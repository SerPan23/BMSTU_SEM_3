#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#define ERROR_FEW_ARGS 1
#define ERROR_A_LOT_ARGS 2
#define ERROR_INVALID_ARG 3
#define ERROR_WRONG_IN_FILEPATH 4
#define ERROR_WRONG_OUT_FILEPATH 5
#define ERROR_EMPTY_RESULT 6
#define ERROR_CREATE_ARR 7
#define ERROR_EMPTY_FILE 10
#define ERROR_OPEN_LIB 100
#define ERROR_LOAD_FUNC 101

typedef int (*fn_cmp_t)(const void *, const void *);
typedef int (*fn_file_len_t)(FILE *, size_t *);
typedef int (*fn_read_file_t)(FILE *, const int *, const int *);
typedef size_t (*fn_find_new_arr_len_t)(const int *, const int *);

typedef void (*fn_sort_t)(void *, size_t , size_t , int (*compar)(const void *, const void *));
typedef int (*fn_key_t)(const int *, const int *, int **, int **);
typedef void (*fn_print_arr_t)(FILE *, const int *, const int *);

int main(int argc, char **argv)
{
    void *hlib;

    hlib = dlopen("./lib/libfilter.so", RTLD_NOW);
    if (!hlib)
    {
        printf("Cannot open library. %s\n", dlerror());

        return ERROR_OPEN_LIB;
    }

    fn_cmp_t cmp = dlsym(hlib, "cmp_int");
    fn_file_len_t find_len = dlsym(hlib, "find_file_len");
    fn_read_file_t read = dlsym(hlib, "read_file");
    fn_find_new_arr_len_t find_new_len = dlsym(hlib, "find_new_arr_len");
    fn_sort_t sort = dlsym(hlib, "mysort");
    fn_key_t key = dlsym(hlib, "key");
    fn_print_arr_t print = dlsym(hlib, "print_arr");
    if (!cmp || !find_len || !read || !find_new_len || !key || !print)
    {
        dlclose(hlib);
        return ERROR_LOAD_FUNC;
    }

    if (argc < 3)
    {
        dlclose(hlib);
        return ERROR_FEW_ARGS;
    }
    if (argc > 4)
    {
        dlclose(hlib);
        return ERROR_A_LOT_ARGS;
    }

    if (argc == 4 && strcmp(argv[3], "f") != 0)
    {
        dlclose(hlib);
        return ERROR_INVALID_ARG;
    }

    FILE *f_in = fopen(argv[1], "r");

    if (f_in == NULL)
    {
        dlclose(hlib);
        return ERROR_WRONG_IN_FILEPATH;
    }

    FILE *f_out = fopen(argv[2], "w");

    if (f_out == NULL)
    {
        fclose(f_in);
        dlclose(hlib);
        return ERROR_WRONG_OUT_FILEPATH;
    }

    size_t n = 0;

    int rc = find_len(f_in, &n);

    if (rc != EXIT_SUCCESS)
    {
        fclose(f_in);
        fclose(f_out);
        dlclose(hlib);
        return rc;
    }

    if (n == 0)
    {
        fclose(f_in);
        fclose(f_out);
        dlclose(hlib);
        return ERROR_EMPTY_FILE;
    }

    int *pb = NULL, *pe = NULL;
    pb = calloc(n, sizeof(int));
    if (!pb)
    {
        fclose(f_in);
        fclose(f_out);
        dlclose(hlib);
        return ERROR_CREATE_ARR;
    }
    pe = pb + n;

    rc = read(f_in, pb, pe);
    if (rc != EXIT_SUCCESS)
    {
        fclose(f_in);
        fclose(f_out);
        free(pb);
        dlclose(hlib);
        return rc;
    }

    int *pb_new = NULL;
    int *pe_new = NULL;

    if (argc == 4)
    {
        size_t new_nmemb = find_new_len(pb, pe);

        if (new_nmemb == 0)
        {
            fclose(f_in);
            fclose(f_out);
            free(pb);
            dlclose(hlib);
            return ERROR_EMPTY_RESULT;
        }

        pb_new = calloc(new_nmemb, sizeof(int));
        if (!pb_new)
        {
            fclose(f_in);
            fclose(f_out);
            free(pb);
            dlclose(hlib);
            return ERROR_CREATE_ARR;
        }
        pe_new = pb_new + new_nmemb;

        rc = key(pb, pe, &pb_new, &pe_new);
        if (rc != EXIT_SUCCESS)
        {
            fclose(f_in);
            fclose(f_out);
            free(pb);
            free(pb_new);
            dlclose(hlib);
            return rc;
        }
        sort(pb_new, pe_new - pb_new, sizeof(int), cmp);
        print(f_out, pb_new, pe_new);
    }
    else
    {
        sort(pb, pe - pb, sizeof(int), cmp);
        print(f_out, pb, pe);
    }

    fclose(f_in);
    fclose(f_out);
    free(pb);
    free(pb_new);
    dlclose(hlib);

    return 0;
}

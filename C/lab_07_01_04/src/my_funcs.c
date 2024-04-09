#include "my_funcs.h"

void swap(void *a, void *b, size_t size)
{
    char *p = a, *q = b, tmp;
    for (size_t i = 0; i < size; i++)
    {
        tmp = *p;
        *p = *q;
        *q = tmp;
        p++;
        q++;
    }
}

int cmp_int(const void *p, const void *q)
{
    const int *a = p;
    const int *b = q;
    return *a - *b;
}

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    char *pb = base;
    char *pe = pb + size * nmemb;
    char *pl = pb, *pr = pe - size;
    size_t i = 0;
    for (char *p = pb; p < pe; p += size, i++)
    {
        if (i % 2 != 0)
        {
            for (char *j = pl; j < pr; j += size)
            {
                char *p1 = j;
                char *p2 = p1 + size;
                if (compar(p1, p2) > 0)
                    swap(p1, p2, size);
            }
            pr -= size;
        }
        else
        {
            for (char *j = pr; j > pl; j -= size)
            {
                char *p1 = j;
                char *p2 = p1 - size;
                if (compar(p1, p2) < 0)
                    swap(p1, p2, size);
            }
            pl += size;
        }
    }
}

int calc_avg(const int *pb, const int *pe, double *avg)
{
    size_t nmemb = pe - pb;
    if (nmemb == 0)
        return ERROR_NO_ELEMETS;

    double sum = 0;
    for (int *p = (int *)pb; p < pe; p++)
        sum += *p;

    *avg = sum / nmemb;

    return EXIT_SUCCESS;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    double avg;
    int rc = calc_avg(pb_src, pe_src, &avg);
    if (rc != EXIT_SUCCESS)
        return rc;

    size_t new_nmemb = 0;
    for (int *p = (int *)pb_src; p < pe_src; p++)
        if (*p > avg)
            new_nmemb++;
    
    if (new_nmemb == 0)
        return ERROR_EMPTY_RESULT;

    *pb_dst = calloc(new_nmemb, sizeof(int));
    if (!(*pb_dst))
        return ERROR_CREATE_ARR;
    *pe_dst = *pb_dst + new_nmemb;

    int *p_dst = *pb_dst;
    for (int *p = (int *)pb_src; p < pe_src; p++)
        if (*p > avg)
        {
            *p_dst = *p;
            p_dst++;
        }

    return EXIT_SUCCESS;
}

int find_file_len(FILE *f, size_t *n)
{
    rewind(f);
    *n = 0;
    int tmp;
    while (fscanf(f, "%d", &tmp) == 1)
        ++(*n);
    if (!feof(f))
        return ERROR_INVALID_FILE;
    return EXIT_SUCCESS;
}

int read_file(FILE *f, const int *pb, const int *pe)
{
    rewind(f);
    int tmp;
    for (int *p = (int *)pb; p < pe; p++)
    {
        fscanf(f, "%d", &tmp);
        *p = tmp;
    }
    return EXIT_SUCCESS;
}

void print_arr(FILE *out, const int *pb, const int *pe)
{
    for (int *p = (int *)pb; p < pe; p++)
        fprintf(out, "%d ", *p);
}

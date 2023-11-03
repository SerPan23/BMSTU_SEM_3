#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#ifndef N
#error NMAX is not defined
#endif

#ifndef IS_SORTED
#error is_sorted is not defined
#endif

typedef int arr_t[N];

unsigned long long milliseconds_now()
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
    {
        return (unsigned long long)-1;
    }
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

void init_sorted(arr_t a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        a[i] = i;
}

void init(arr_t a, size_t n)
{
    srand(time(NULL));

    for (size_t i = 0; i < n; i++)
        a[i] = rand();
}

int cmp_int(const void *p, const void *q)
{
    const int *a = p;
    const int *b = q;
    return *a - *b;
}

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

int main(void)
{
    arr_t a;
    size_t n = N;

    int is_sorted = IS_SORTED;

    if (is_sorted)
        init_sorted(a, n);
    else
        init(a, n);

    unsigned long long begin, end;

    begin = milliseconds_now();

    mysort(a, n, sizeof(a[0]), cmp_int);

    end = milliseconds_now();

    a[0] = a[1];
    a[1] = 1234;

    printf("%llu\n", end - begin);

    return 0;
}

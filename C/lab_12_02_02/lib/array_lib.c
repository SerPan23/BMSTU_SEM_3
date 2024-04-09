#include "array_lib.h"

int arr_fill_fibonacci(int *arr, int size, int n)
{
    int count = 0;

    if (arr)
    {
        if (n == 1 && size > 1)
            arr[0] = 0;
        if (size > 2 && n >= 2)
        {
            arr[0] = 0;
            arr[1] = 1;
        }
    }

    if (n >= 2)
        count += 2;
    else
        count += n;

    for (int i = 2; i < n; i++)
    {
        if (arr && size > 2 && i < size)
            arr[i] = arr[i - 1] + arr[i - 2];
        count++;
    }

    return count;
}

int arr_copy_unique(int *src, int src_size, int *dst, int dst_size)
{
    int count = 0;
    int dst_i = 0;

    for (int i = 0; i < src_size; i++)
    {
        int flag = 1;
        for (int j = 0; j < i; j++)
            if (src[i] == src[j])
                flag = 0;

        if (flag)
        {
            count++;
            if (dst && dst_i < dst_size)
                dst[dst_i++] = src[i];
        }
    }

    return count;
}

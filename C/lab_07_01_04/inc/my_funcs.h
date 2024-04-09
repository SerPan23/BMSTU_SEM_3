#ifndef MY_FUNCS_H
#define MY_FUNCS_H

#include "constants.h"

void swap(void *a, void *b, size_t size);
int cmp_int(const void *p, const void *q);

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

int find_file_len(FILE *f, size_t *n);
int read_file(FILE *f, const int *pb, const int *pe);
void print_arr(FILE *out, const int *pb, const int *pe);

#endif

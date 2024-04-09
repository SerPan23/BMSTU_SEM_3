#ifndef FILTER_LIB_H
#define FILTER_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define ERROR_NO_ELEMETS 1
#define ERROR_INVALID_FILE 2
#define ERROR_EMPTY_RESULT 3


void swap(void *a, void *b, size_t size);
int cmp_int(const void *p, const void *q);

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

size_t find_new_arr_len(const int *pb_src, const int *pe_src);

int find_file_len(FILE *f, size_t *n);
int read_file(FILE *f, const int *pb, const int *pe);
void print_arr(FILE *out, const int *pb, const int *pe);

#endif
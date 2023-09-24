#ifndef FUNCS_H
#define FUNCS_H

#include "defines.h"

int is_int(char *s, size_t len);
int is_double(char *s, size_t len);

int read_int(int *num, size_t max_len, FILE *input);
int read_double(double *num, size_t max_len, FILE *input);
int read_string(char *str, size_t *len, size_t max_len, FILE *input);

void swap(void *a, void *b, size_t size);

unsigned long long cur_ms_gettimeofday(void);
long delta_time(struct timespec mt1, struct timespec mt2);

#endif

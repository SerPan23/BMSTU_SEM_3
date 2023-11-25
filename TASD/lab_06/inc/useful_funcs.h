#ifndef USEFUL_FUNCS_H
#define USEFUL_FUNCS_H

#include "defines.h"

long delta_time(struct timespec mt1, struct timespec mt2);
int read_string(char *str, size_t *len, size_t max_len, FILE *input);
char *del_repeats_from_str(char *str, size_t len);
int read_int(int *num, size_t max_len, FILE *input);
int read_double(double *num, size_t max_len, FILE *input);
void clean_stdin(void);

#endif

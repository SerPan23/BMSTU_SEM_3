#ifndef USEFUL_FUNCS_H
#define USEFUL_FUNCS_H

#include "defines.h"

int get_random_int(int min, int max);
long delta_time(struct timespec mt1, struct timespec mt2);
int read_int(int *num, size_t max_len, FILE *input);

#endif

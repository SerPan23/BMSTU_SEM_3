#ifndef FILE_H
#define FILE_H

#include "item.h"

int read_items(char *filepath, items_t items, size_t *n);
int sort_and_print(char *filepath);
int print_all(char *filepath);
int print_substr_start(char *filepath, char *substr);

#endif

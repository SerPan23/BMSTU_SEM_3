#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FEW_ARGS 1
#define ERROR_A_LOT_ARGS 2
#define ERROR_EMPTY_FILE 3
#define ERROR_WRONG_INPUT 4
#define ERROR_EMPTY_INPUT 5
#define ERROR_NAME_LEN 6
#define ERROR_EMPTY_PRINT 7
#define ERROR_INCORRECT_NUM_VALUE 8
#define ERROR_WRONG_ITEMS_COUNT 9
#define ERROR_WRONG_FILEPATH 10

#define MAX_NAME_LEN 25
#define MAX_ITEMS 15

typedef struct
{
    char name[MAX_NAME_LEN + 1];
    double weight;
    double volume;
} item_t;

typedef item_t items_t[MAX_ITEMS];

int scan_item(FILE *f, item_t *item);
void print_item(item_t item);

#endif

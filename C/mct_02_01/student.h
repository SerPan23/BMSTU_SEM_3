#ifndef STUDENT_H
#define PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>

#define NAME_LEN 5

typedef struct
{
    char surname[NAME_LEN + 1];
    int32_t height;
} student_t;

#endif

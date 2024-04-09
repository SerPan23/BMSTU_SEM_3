#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c -O3 main.c file.c item.c
gcc main.o file.o item.o -o app.exe -lm 
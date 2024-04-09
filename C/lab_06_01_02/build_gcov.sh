#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c -O0 -g3 -coverage main.c file.c item.c
clang main.o file.o item.o -o app.exe -coverage -lm
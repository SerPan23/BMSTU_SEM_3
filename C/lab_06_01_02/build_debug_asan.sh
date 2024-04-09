#!/bin/bash

gcc -std=c99 -fsanitize=address -fno-omit-frame-pointer -g -c main.c file.c item.c
gcc main.o file.o item.o -o app.exe -lm
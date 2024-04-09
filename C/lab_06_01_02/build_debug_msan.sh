#!/bin/bash

clang -std=c99 -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g -c main.c file.c item.c
clang main.o file.o item.o -o app.exe -lm
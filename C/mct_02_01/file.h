#ifndef FILE_H
#define FILE_H

#include "student.h"

#define ERROR_ARGS 53
#define ERROR_WRONG_FILEPATH 1
#define ERROR_EMPTY_FILE 3
#define ERROR_FILE_WORK 4
#define ERROR_FILE_READ 5
#define ERROR_WRONG_POS 6
#define ERROR_EMPTY_INPUT 7
#define ERROR_STR_LEN 8
#define ERROR_INPUT_HEIGHT 9

int file_size(FILE *f, long *size);
int get_one_by_pos(FILE *f, long pos, student_t *s);
int put_one_by_pos(FILE *f, long pos, student_t s);
int print_student(student_t s);
int print_students(char *filepath);
int read_student(student_t *s);
int add_student(char *filepath);
int calc_height_avg(char *filepath, double *avg);
int del_studs_height_lt_avg(char *filepath);

#endif

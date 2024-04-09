#include "file.h"

int file_size(FILE *f, long *size)
{
    long sz;

    if (fseek(f, 0L, SEEK_END))
        return ERROR_FILE_WORK;

    sz = ftell(f);
    if (sz < 0)
        return ERROR_FILE_WORK;

    *size = sz;

    return fseek(f, 0L, SEEK_SET);
}

int get_one_by_pos(FILE *f, long pos, student_t *s)
{
    fseek(f, pos * sizeof(student_t), SEEK_SET);
    fread(s, sizeof(student_t), 1, f);
    return EXIT_SUCCESS;
}

int put_one_by_pos(FILE *f, long pos, student_t s)
{
    fseek(f, pos * sizeof(student_t), SEEK_SET);
    fwrite(&s, sizeof(student_t), 1, f);
    return EXIT_SUCCESS;
}

int print_student(student_t s)
{
    printf("%s\n%" PRId32 "\n", s.surname, s.height);
    return EXIT_SUCCESS;
}

int print_students(char *filepath)
{
    FILE *f = fopen(filepath, "rb");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    long size;
    int rc = file_size(f, &size);

    if (size == 0)
    {
        fclose(f);
        return ERROR_EMPTY_FILE;
    }

    if (rc != 0)
    {
        fclose(f);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(student_t);

    for (long i = 0; i < size; i++)
    {
        student_t s;
        get_one_by_pos(f, i, &s);
        print_student(s);
    }
    fclose(f);
    return EXIT_SUCCESS;
}

int read_student(student_t *s)
{
    char tmp_name[NAME_LEN + 2];
    if (fgets(tmp_name, NAME_LEN + 2, stdin) == NULL)
        return ERROR_EMPTY_INPUT;

    tmp_name[strcspn(tmp_name, "\n")] = '\0';

    if (strlen(tmp_name) && strlen(tmp_name) > NAME_LEN)
        return ERROR_STR_LEN;

    strcpy(s->surname, tmp_name);

    int32_t t;
    if (scanf("%" SCNd32, &t) != 1)
        return ERROR_INPUT_HEIGHT;
    
    s->height = t;

    return EXIT_SUCCESS;
}

int add_student(char *filepath)
{
    FILE *f = fopen(filepath, "r+b");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    long size;
    int rc = file_size(f, &size);

    if (size == 0)
    {
        fclose(f);
        return ERROR_EMPTY_FILE;
    }

    if (rc != 0)
    {
        fclose(f);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(student_t);

    student_t s;
    rc = read_student(&s);

    if (rc != EXIT_SUCCESS)
    {
        fclose(f);
        return rc;
    }

    put_one_by_pos(f, size, s);
    fclose(f);
    return EXIT_SUCCESS;
}

int calc_height_avg(char *filepath, double *avg)
{
    FILE *f = fopen(filepath, "rb");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    long size;
    int rc = file_size(f, &size);

    if (size == 0)
    {
        fclose(f);
        return ERROR_EMPTY_FILE;
    }

    if (rc != 0)
    {
        fclose(f);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(student_t);

    double sum = 0;

    for (long i = 0; i < size; i++)
    {
        student_t s;
        get_one_by_pos(f, i, &s);
        sum += s.height;
    }

    *avg = sum / size;

    fclose(f);
    return EXIT_SUCCESS;
}

int del_studs_height_lt_avg(char *filepath)
{
    FILE *f = fopen(filepath, "r+b");

    if (f == NULL)
        return ERROR_WRONG_FILEPATH;

    long size;
    int rc = file_size(f, &size);

    if (size == 0)
    {
        fclose(f);
        return ERROR_EMPTY_FILE;
    }

    if (rc != 0)
    {
        fclose(f);
        return ERROR_FILE_WORK;
    }

    size /= sizeof(student_t);

    double avg;
    rc = calc_height_avg(filepath, &avg);

    if (rc != EXIT_SUCCESS)
        return rc;

    long count = 0;

    for (long i = 0; i < size; i++)
    {
        student_t s;
        get_one_by_pos(f, i, &s);

        if (s.height < avg)
            count++;
        else
            put_one_by_pos(f, i - count, s);
    }

    fclose(f);

    truncate(filepath, (size - count) * sizeof(student_t));

    return EXIT_SUCCESS;
}

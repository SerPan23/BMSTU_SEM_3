#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../student.h"

int file_size(FILE *f, long *size)
{
    long sz;

    if (fseek(f, 0L, SEEK_END))
        return 2;

    sz = ftell(f);
    if (sz < 0)
        return 3;

    *size = sz;

    return fseek(f, 0L, SEEK_SET);
}

int get_one_by_pos(FILE *f, long pos, student_t *s)
{
    fseek(f, pos * sizeof(student_t), SEEK_SET);
    fread(s, sizeof(student_t), 1, f);
    return 0;
}

int fprint_student(student_t s, FILE *f)
{
    fprintf(f, "%s\n%" PRId32 "\n", s.surname, s.height);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    FILE *in;
    in = fopen(argv[1], "rb");

    FILE *out;
    char tmp[1024];

    size_t path_len = strlen(argv[1]);

    if (path_len > 4 && argv[1][path_len - 4] == '.')
        strncpy(tmp, argv[1], path_len - 4);
    else
        strcpy(tmp, argv[1]);

    tmp[path_len - 4] = '\0';

    strcat(tmp, "_b.txt");
    out = fopen(tmp, "w");

    if (out == NULL)
        printf("out NULL (%s)\n", tmp);

    long size;
    int rc = file_size(in, &size);

    if (rc != 0)
    {
        fclose(in);
        return rc;
    }

    size /= sizeof(student_t);

    student_t t;

    for (long i = 0; i < size; i++)
    {
        get_one_by_pos(in, i, &t);
        fprint_student(t, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}
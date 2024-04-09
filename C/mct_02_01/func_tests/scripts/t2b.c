#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../student.h"

int read_student(FILE *f, student_t *s)
{
    char tmp[1024];

    fgets(tmp, 1024, f);
    tmp[strcspn(tmp, "\n")] = '\0';

    if (strlen(tmp) && strlen(tmp) > NAME_LEN)
        return 3;

    strcpy(s->surname, tmp);

    int32_t t;
    fgets(tmp, 1024, f);
    tmp[strcspn(tmp, "\n")] = '\0';
    t = strtol(tmp, NULL, 0);
    s->height = t;

    return EXIT_SUCCESS;
}

int find_file_len(FILE *f, long *n)
{
    rewind(f);
    *n = 0;
    student_t tmp;
    while (!feof(f))
    {
        int rc = read_student(f, &tmp);
        if (rc == EXIT_SUCCESS)
            ++(*n);
        else
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    FILE *in;
    in = fopen(argv[1], "r");

    FILE *out;

    char tmp[1024];

    size_t path_len = strlen(argv[1]);

    if (path_len > 4 && argv[1][path_len - 4] == '.')
        strncpy(tmp, argv[1], path_len - 4);
    else
        strcpy(tmp, argv[1]);

    tmp[path_len - 4] = '\0';

    strcat(tmp, ".bin");
    out = fopen(tmp, "wb");

    if (out == NULL)
        printf("out NULL (%s)\n", tmp);

    long n;

    find_file_len(in, &n);

    student_t t;

    rewind(in);
    for (long i = 0; i < n; i++)
    {
        int rc = read_student(in, &t);
        if (rc == EXIT_SUCCESS)
        {
            fseek(out, 0, SEEK_END);
            fwrite(&t, sizeof(student_t), 1, out);
        }
        // printf("* %d\n", rc);
    }


    fclose(in);
    fclose(out);
    return 0;
}
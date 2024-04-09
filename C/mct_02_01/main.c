#include "file.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return ERROR_ARGS;
    if (argc > 3)
        return ERROR_ARGS;

    int rc = EXIT_SUCCESS;

    if (strcmp(argv[1], "db") == 0 && argc == 3)
        rc = del_studs_height_lt_avg(argv[2]);
    else if (strcmp(argv[1], "fb") == 0 && argc == 3)
        rc = print_students(argv[2]);
    else if (strcmp(argv[1], "ab") == 0 && argc == 3)
        rc = add_student(argv[2]);
    else
        rc = ERROR_ARGS;

    return rc;
}

#include "file.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return ERROR_FEW_ARGS;
    if (argc > 3)
        return ERROR_A_LOT_ARGS;

    int rc = EXIT_SUCCESS;
    if (argc == 2)
        rc = sort_and_print(argv[1]);
    else if (strcmp(argv[2], "ALL") == 0)
        rc = print_all(argv[1]);
    else
        rc = print_substr_start(argv[1], argv[2]);

    return rc;
}

#include "my_menu.h"

void print_menu(void)
{
    printf("------------------\n");
    printf("Menu:\n\
    1) Сomparison of queue implementations\n\
    2) View simulation parameters\n\
    3) Simulation settings\n\
    4) Start simulation\n\
    0) Quit program\n");
    printf("------------------\n");
}

int choose_menu_item(int *command)
{
    printf("Choose menu item (0-%d):\n", MENU_ITEMS_COUNT);
    if (read_int(command, MAX_STR_LEN, stdin) != EXIT_SUCCESS)
        return ERROR_WRONG_MENU_ITEM;
    if (*command < 0 || *command > MENU_ITEMS_COUNT)
        return ERROR_WRONG_MENU_ITEM;
    return EXIT_SUCCESS;
}

void start_simulation(double *t1_start, double *t1_end, double *t2_start, double *t2_end)
{
    printf("\n-----------START SIMULATION-----------\n\n");

    printf("\n\n-----------END SIMULATION-----------\n");
}

void edit_times(double *t1_start, double *t1_end, double *t2_start, double *t2_end)
{
    printf("Simulation parametrs edit:\n");

    int rc = EXIT_SUCCESS;
    double tmp;
    do
    {
        printf("Enter T1 from:\n");
        if (read_double(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS || tmp < 0)
        {
            printf("ERROR: wrong time, it's must be bigger than 0\n");
            rc = EXIT_FAILURE;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *t1_start = tmp;

    do
    {
        printf("Enter T1 to:\n");
        if (read_double(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS || tmp < 0 || tmp <= *t1_start)
        {
            printf("ERROR: wrong time, it's must be bigger than 0 and than %.2lf\n", *t1_start);
            rc = EXIT_FAILURE;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *t1_end = tmp;

    do
    {
        printf("Enter T2 from:\n");
        if (read_double(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS || tmp < 0)
        {
            printf("ERROR: wrong time, it's must be bigger than 0\n");
            rc = EXIT_FAILURE;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *t2_start = tmp;

    do
    {
        printf("Enter T2 to:\n");
        if (read_double(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS || tmp < 0 || tmp <= *t2_start)
        {
            printf("ERROR: wrong time, it's must be bigger than 0 and than %.2lf\n", *t2_start);
            rc = EXIT_FAILURE;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *t2_end = tmp;
}

int menu(void)
{
    int command = -1, rc;
    double t1_start = 0, t1_end = 6;
    double t2_start = 0, t2_end = 1;

    while (command != 0)
    {
        print_menu();
        rc = choose_menu_item(&command);
        if (rc != EXIT_SUCCESS)
        {
            printf("ERROR: wrong choose, you need enter numbers from 0 to %d\n", MENU_ITEMS_COUNT);
            continue;
        }
        if (command == 0)
            break;
        else if (command == 1)
        {
            print_time_measurements();
        }
        else if (command == 2)
        {
            printf("Simulation parametrs:\n");
            printf("T1 from %.2lf to %.2lf:\n", t1_start, t1_end);
            printf("T2 from %.2lf to %.2lf:\n", t2_start, t2_end);
        }
        else if (command == 3)
        {
            edit_times(&t1_start, &t1_end, &t2_start, &t2_end);
        }
        else if (command == 4)
        {
            start_simulation(&t1_start, &t1_end, &t2_start, &t2_end);
        }
    }

    return EXIT_SUCCESS;
}

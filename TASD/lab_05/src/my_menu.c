#include "my_menu.h"

void print_menu(void)
{
    printf("------------------\n");
    printf("Menu:\n\
    1) Push in queue list\n\
    2) Pop from queue list\n\
    3) Print queue list\n\
    4) Push in queue array\n\
    5) Pop from queue array\n\
    6) Print queue array\n\
    7) Сomparison of queue implementations\n\
    8) View simulation parameters\n\
    9) Simulation settings\n\
    10) Start simulation\n\
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

void start_simulation(double t1_start, double t1_end, double t2_start, double t2_end, int repeats)
{
    int queue_type = 1, rc = EXIT_SUCCESS;
    do
    {
        printf("Choose queue type for simulation:\n0) Queue by array\n1) Queue by list\n");
        if (read_int(&queue_type, MAX_STR_LEN, stdin) != EXIT_SUCCESS || queue_type < 0 || queue_type > 1)
        {
            printf("ERROR: wrong queue type, it's must be 0 or 1\n");
            rc = EXIT_FAILURE;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);

    queue_t queue;
    queue_init(&queue);
    printf("\n-----------START SIMULATION-----------\n\n");
    queue_simulation_work(&queue, queue_type, t1_start, t1_end, t2_start, t2_end, repeats);
    printf("\n\n-----------END SIMULATION-----------\n");
}

void edit_sim_settings(double *t1_start, double *t1_end, double *t2_start, double *t2_end, int *repeats)
{
    printf("Simulation parametrs edit:\n");

    int rc = EXIT_SUCCESS;
    double tmp;
    do
    {
        printf("Enter T1 from:\n");
        if (read_double(&tmp, MAX_STR_LEN, stdin) != EXIT_SUCCESS || tmp < 0)
        {
            printf("ERROR: wrong time, it's must be >= that 0\n");
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
            printf("ERROR: wrong time, it's must be >= that 0 and that %.2lf\n", *t1_start);
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
            printf("ERROR: wrong time, it's must be >= that 0\n");
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
            printf("ERROR: wrong time, it's must be >= that 0 and that %.2lf\n", *t2_start);
            rc = EXIT_FAILURE;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *t2_end = tmp;


    int t;
    do
    {
        printf("Enter repeats count:\n");
        if (read_int(&t, MAX_STR_LEN, stdin) != EXIT_SUCCESS || t <= 0)
        {
            printf("ERROR: wrong repeats count, it's must be bigger that 0\n");
            rc = EXIT_FAILURE;
            continue;
        }
        rc = EXIT_SUCCESS;
    } while (rc != EXIT_SUCCESS);
    *repeats = t;
}

int menu(void)
{
    int command = -1, rc;
    double t1_start = 0, t1_end = 6;
    double t2_start = 0, t2_end = 1;
    int repeats = 5;

    queue_list_t queue_list;
    rc = queue_list_init(&queue_list);
    if (rc != EXIT_SUCCESS)
    {
        printf("ERROR: err num is %d\n", rc);
        return rc;
    }

    queue_array_t queue_arr;
    queue_array_init(&queue_arr);

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
        {
            queue_list_free(&queue_list);
            break;
        }
        else if (command == 1)
        {
            list_node_t *tmp;
            list_node_init(&tmp);
            rc = queue_list_push(&queue_list, tmp);
            if (rc != EXIT_SUCCESS)
                printf("ERROR PUSH: list is full\n");
            else
                printf("Pushed to queue list\n");
            int flag = check_if_mem_reused(&queue_list);
            if (flag)
                printf("This element reused memory (reused address: %p)\n", (void *)queue_list.tail);
        }
        else if (command == 2)
        {
            rc = queue_list_pop(&queue_list, NULL);
            if (rc != EXIT_SUCCESS)
                printf("ERROR POP: list is empty\n");
            else
                printf("Poped from queue list\n");
        }
        else if (command == 3)
        {
            queue_list_print(&queue_list);
        }
        else if (command == 4)
        {
            array_element_t tmp;
            array_el_init(&tmp);
            rc = queue_array_push(&queue_arr, &tmp);
            if (rc != EXIT_SUCCESS)
                printf("ERROR PUSH: array is full\n");
            else
                printf("Pushed to queue array\n");
        }
        else if (command == 5)
        {
            rc = queue_array_pop(&queue_arr, NULL);
            if (rc != EXIT_SUCCESS)
                printf("ERROR POP: array is empty\n");
            else
                printf("Poped from queue array\n");
        }
        else if (command == 6)
        {
            queue_array_print(&queue_arr);
        }
        else if (command == 7)
        {
            print_time_measurements();
        }
        else if (command == 8)
        {
            printf("Simulation parametrs:\n");
            printf("T1 from %.2lf to %.2lf:\n", t1_start, t1_end);
            printf("T2 from %.2lf to %.2lf:\n", t2_start, t2_end);
            printf("Repeats count: %d\n", repeats);
        }
        else if (command == 9)
        {
            edit_sim_settings(&t1_start, &t1_end, &t2_start, &t2_end, &repeats);
        }
        else if (command == 10) 
        {
            start_simulation(t1_start, t1_end, t2_start, t2_end, repeats);
        }
    }
    
    return EXIT_SUCCESS;
}

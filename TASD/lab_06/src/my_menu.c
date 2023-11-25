#include "my_menu.h"

void print_menu(void)
{
    printf("------------------\n");
    printf("Menu:\n\
    1) Process string\n\
    2) Сomparison of delete types\n\
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

int string_processing(void)
{
    int rc = EXIT_SUCCESS;
    tree_node_t *tree = NULL;

    // char *str = "B216345576897";
    char str[MAX_STR_LEN + 1];
    size_t tmp_l;
    
    do
    {
        printf("Enter string:\n");
        rc = read_string(str, &tmp_l, MAX_STR_LEN, stdin);
        if (rc != EXIT_SUCCESS || tmp_l == 0)
        {
            printf("ERROR: incorrect string\n");
            rc = EXIT_FAILURE;
            continue;
        }
    } while (rc != EXIT_SUCCESS);
    

    const size_t n = tmp_l;

    tree = tree_create_from_str(str, n);

    rc = open_tree_img("src", tree);
    if (rc != EXIT_SUCCESS)
        return rc;

    tree_del_not_unique_nodes(&tree);

    rc = open_tree_img("result", tree);
    if (rc != EXIT_SUCCESS)
        return rc;

    tree_print_post_order(tree);
    tree_free(&tree);
    return EXIT_SUCCESS;
}

int menu(void)
{
    int command = -1, rc;

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
            rc = string_processing();
            if (rc != EXIT_SUCCESS)
            {
                printf("ERROR: Something went wrong (error code: %d)\n", rc);
            }
        }
        else if (command == 2)
        {
            print_time_measurements();
        }
    }

    return EXIT_SUCCESS;
}

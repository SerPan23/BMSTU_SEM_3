#include "my_menu.h"

void print_menu(void)
{
    printf("------------------\n");
    printf("Menu:\n\
    1) Add in hash table (opened)\n\
    2) Print hash table (opened)\n\
    3) Restruct hash table (opened)\n\
    4) Add in hash table (closed)\n\
    5) Print hash table (closed)\n\
    6) Restruct hash table (closed)\n\
    7) Process string\n\
    8) Сomparison of search types\n\
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
        if (rc != EXIT_SUCCESS || tmp_l == 0 || !is_alnum_str(str))
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

    tree_node_t *balanced_tree =  tree_balance_BST(tree);

    rc = open_tree_img("result_balanced", balanced_tree);
    if (rc != EXIT_SUCCESS)
        return rc;

    tree_node_t *avl_tree = AVL_tree_from_tree(tree);

    rc = open_tree_img("result_avl", avl_tree);
    if (rc != EXIT_SUCCESS)
        return rc;

    hash_table_t *table;
    // table = table_init(OPENED);
    table = table_init(CLOSED);

    table_create_from_str(&table, str);

    table_print(table);

    tree_free(&tree);
    tree_free(&balanced_tree);
    table_free(table);
    return EXIT_SUCCESS;
}

int menu(void)
{
    int command = -1, rc;

    hash_table_t *table_opened;
    table_opened = table_init(OPENED);

    hash_table_t *table_closed;
    table_closed = table_init(CLOSED);

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
            char tmp;
            int flag = 0;
            while (!flag)
            {
                tmp = read_symbol("Enter symbol:");
                if (isalnum(tmp))
                    flag = 1;
                else
                    printf("ERROR: NOT ALNUM\n");
            }
            table_add_with_debug(&table_opened, tmp);
        }
        else if (command == 2)
        {
            int tmp = table_is_need_restruct(table_opened);
            if (tmp)
                printf("YOUR TABLE NEED RESTRUCT\n");

            table_print(table_opened);
        }
        else if (command == 3)
        {
            int new_hash = 0;
            rc = EXIT_FAILURE;
            while (rc != EXIT_SUCCESS)
            {
                printf("Enter new hash:\n");
                rc = read_int(&new_hash, MAX_STR_LEN, stdin);
                if (rc != EXIT_SUCCESS || new_hash < 1)
                {
                    printf("ERROR: wrong hash\n");
                    rc = EXIT_FAILURE;
                }
            }

            table_restruct(&table_opened, new_hash);
        }
        else if (command == 4)
        {
            char tmp;
            int flag = 0;
            while (!flag)
            {
                tmp = read_symbol("Enter symbol:");
                if (isalnum(tmp))
                    flag = 1;
                else
                    printf("ERROR: NOT ALNUM\n");
            }
            table_add_with_debug(&table_closed, tmp);
        }
        else if (command == 5)
        {
            int tmp = table_is_need_restruct(table_closed);
            if (tmp)
                printf("YOUR TABLE NEED RESTRUCT\n");
            
            table_print(table_closed);
        }
        else if (command == 6)
        {
            int new_hash = 0;
            rc = EXIT_FAILURE;
            while (rc != EXIT_SUCCESS)
            {
                printf("Enter new hash:\n");
                rc = read_int(&new_hash, MAX_STR_LEN, stdin);
                if (rc != EXIT_SUCCESS || new_hash < 1)
                {
                    printf("ERROR: wrong hash\n");
                    rc = EXIT_FAILURE;
                }
            }

            table_restruct(&table_closed, new_hash);
        }
        else if (command == 7)
        {
            rc = string_processing();
            if (rc != EXIT_SUCCESS)
            {
                printf("ERROR: Something went wrong (error code: %d)\n", rc);
            }
        }
        else if (command == 8)
        {
            print_time_measurements();
        }
    }

    table_free(table_opened);
    table_free(table_closed);

    return EXIT_SUCCESS;
}

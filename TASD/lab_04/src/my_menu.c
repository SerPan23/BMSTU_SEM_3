#include "my_menu.h"

char stack_array_data[MAX_STACK_LEN];

void print_menu(void)
{
    printf("------------------\n");
    printf("Menu:\n\
    1) Push array stack\n\
    2) Pop array stack\n\
    3) Print array stack\n\
    4) Push list stack\n\
    5) Pop list stack\n\
    6) Print list stack\n\
    7) Check brackets sequence\n\
    8) Print stacks compare\n\
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

char read_symbol(char *s, size_t *str_len, char *msg)
{
    int rc = EXIT_SUCCESS;
    do 
    {
        printf("%s\n", msg);
        rc = read_string(s, str_len, 1, stdin);
        if (rc != EXIT_SUCCESS)
        {
            printf("ERROR: You need enter only one symbol!\n");
            continue;
        }
        if (*str_len == 0)
        {
            printf("ERROR: You need enter only one symbol!\n");
            rc = EXIT_FAILURE;
            continue;
        }
    } while(rc != EXIT_SUCCESS);
    return s[0];
}

int check_brackets_sequence_mitem(char *s, size_t *str_len)
{
    read_string(s, str_len, MAX_STR_LEN, stdin);
    stack_list_t tmp_stack;
    tmp_stack.ptr = NULL;
    tmp_stack.size = 0;
    tmp_stack.free_area_size_alloc = 0;
    int flag = is_bracket_seq(s, *str_len, 1, &tmp_stack, NULL, 0, NULL);
    stack_list_free(&tmp_stack);
    return flag;
}

int menu(void)
{
    int command = -1, rc;

    stack_list_t stack_list;
    stack_list.ptr = NULL;
    stack_list.size = 0;
    stack_list.free_area_size_alloc = 0;
    init_free_area(&stack_list, MAX_STACK_LEN * 2);

    stack_array_t stack_array;
    stack_array.data = stack_array_data;
    stack_array.size = 0;

    char s[MAX_STR_LEN];
    size_t str_len = 0;

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
            char c = read_symbol(s, &str_len, "Enter one symbol for push it in array stack:");
            rc = stack_array_push(&stack_array, c);
            if (rc != EXIT_SUCCESS)
                printf("ERROR: you can't add more elements!\n");
        }
        else if (command == 2)
        {
            rc = stack_array_pop(&stack_array);
            if (rc != EXIT_SUCCESS)
                printf("ERROR: stack is empty!\n");
        }
        else if (command == 3)
        {
            printf("STACK BY ARRAY\n");
            stack_array_print(&stack_array);
        }
        else if (command == 4)
        {
            char c = read_symbol(s, &str_len, "Enter one symbol for push it in list stack:");
            rc = stack_list_push(&stack_list, c);
            if (rc != EXIT_SUCCESS)
                printf("ERROR: you can't add more elements!\n");
        }
        else if (command == 5)
        {
            rc = stack_list_pop(&stack_list);
            if (rc != EXIT_SUCCESS)
                printf("ERROR: stack is empty!\n");
        }
        else if (command == 6)
        {
            printf("STACK BY LIST\n");
            stack_list_print(&stack_list);
        }
        else if (command == 7)
        {
            printf("Enter string that you want check for brackets sequence:\n");
            int flag = check_brackets_sequence_mitem(s, &str_len);
            printf("This is brackets sequence: %s\n", flag ? "Yes" : "No");
        }
        else if (command == 8)
        {
            print_time_measurements();
        }
    }
    stack_list_free(&stack_list);
    return EXIT_SUCCESS;
}

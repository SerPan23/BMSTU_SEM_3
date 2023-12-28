#include "my_menu.h"

void print_menu(void)
{
    printf("------------------\n");
    printf("Menu:\n\
    1) Init graph\n\
    2) Add edge\n\
    3) Show graph\n\
    4) Is graph connected\n\
    5) Change start node\n\
    6) Find nodes, that path len from start node <= a\n\
    7) Print paths to n node from start node\n\
    8) Build minimum cost spanning trees\n\
    9) Time comparation\n\
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

void read_file(graph_t **g)
{
    FILE *file;
    char tmp[MAX_STR_LEN + 1];
    size_t tmp_len;
    int rc;
    do
    {
        printf("Enter path to file with data:\n");
        rc = read_string(tmp, &tmp_len, MAX_STR_LEN, stdin);
        if (rc != EXIT_SUCCESS)
        {
            printf("ERROR: Invalid path\n");
            continue;
        }
        file = fopen(tmp, "r");
        if (file == NULL)
        {
            printf("ERROR: wrong path or file\n");
            rc = ERROR_WRONG_FILEPATH;
            continue;
        }
        rc = graph_read_from_file(g, file);
        if (rc != EXIT_SUCCESS)
        {
            printf("ERROR: wrong file\n");
            continue;
        }
    } while (rc != EXIT_SUCCESS);
    fclose(file);
    printf("FILE LOADED SUCCESS!\n");
}

int menu(void)
{
    int command = -1, rc;
    int is_graph_init = 0;
    int is_path_init = 0;

    graph_t *g = NULL;
    path_t *path = NULL;
    int start_node = 1;
    int a = 3;

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
            int flag = 1;

            do
            {
                printf("Load from file:\n1) Yes\n0) No\n");
                rc = read_int(&flag, MAX_STR_LEN, stdin);
                if (rc != EXIT_SUCCESS || flag < 0 || flag > 1)
                {
                    rc = EXIT_FAILURE;
                    printf("ERROR: Wrong number, it must be from 0 to 1\n");
                }
            } while (rc != EXIT_SUCCESS);

            if (flag)
            {
                read_file(&g);
            }
            else
            {
                int n = 0;
                do
                {
                    printf("Enter nodes count:\n");
                    rc = read_int(&n, MAX_STR_LEN, stdin);
                    if (rc != EXIT_SUCCESS || n < 1)
                    {
                        rc = EXIT_FAILURE;
                        printf("ERROR: Wrong count, it must be from 1\n");
                    }
                } while (rc != EXIT_SUCCESS);
                graph_init(&g, n);
            }
            is_graph_init = 1;
        }
        else if (command == 2 && is_graph_init)
        {
            // int data[5][5] =
            //     {
            //         {0, 1, 1, 0, 0},
            //         {0, 0, 1, 1, 1},
            //         {0, 0, 0, 0, 1},
            //         {0, 1, 1, 0, 1},
            //         {0, 1, 1, 0, 0},
            //     };

            // for (int i = 0; i < 5; i++)
            //     for (int j = 0; j < 5; j++)
            //         graph_add_edge(g, i, j, data[i][j]);

            int v, u, len;
            read_edge(g->n, &v, &u, &len);

            int flag = 1;

            if (is_edge_init(g, v - 1, u - 1))
            {
                do
                {
                    printf("Replace edge len:\n1) Yes\n0) No\n");
                    rc = read_int(&flag, MAX_STR_LEN, stdin);
                    if (rc != EXIT_SUCCESS || flag < 0 || flag > 1)
                    {
                        rc = EXIT_FAILURE;
                        printf("ERROR: Wrong number, it must be from 0 to 1\n");
                    }
                } while (rc != EXIT_SUCCESS);
            }

            if (flag)
                graph_add_edge(g, v - 1, u - 1, len);
        }
        else if (command == 3 && is_graph_init)
        {
            graph_open_img("graph", g);
        }
        else if (command == 4 && is_graph_init)
        {
            if (is_graph_connected(g))
                printf("Your graph is connected\n");
            else
                printf("Your graph is not connected\n");
        }
        else if (command == 5 && is_graph_init)
        {
            do
            {
                printf("Enter start node number (1-%d):\n", g->n);
                rc = read_int(&start_node, MAX_STR_LEN, stdin);
                if (rc != EXIT_SUCCESS || start_node < 1 || start_node > g->n)
                {
                    rc = EXIT_FAILURE;
                    printf("ERROR: Wrong start node number, it must be from 1 to %d\n", g->n);
                }
            } while (rc != EXIT_SUCCESS);
        }
        else if (command == 6 && is_graph_init)
        {
            do
            {
                printf("Enter max len number (> 0):\n");
                rc = read_int(&a, MAX_STR_LEN, stdin);
                if (rc != EXIT_SUCCESS || a < 1)
                {
                    rc = EXIT_FAILURE;
                    printf("ERROR: Wrong number, it must be from 1\n");
                }
            } while (rc != EXIT_SUCCESS);

            dijkstra(g, &path, start_node - 1);            

            vector_t *res_nodes = NULL;
            res_nodes = get_nodes_len_le_a(path, a);

            printf("Nodes that path len from %d <= %d\n", start_node, a);
            
            if (res_nodes->size)
                vector_print(res_nodes, ' ', '\n');
            else
                printf("No nodes\n");

            vector_free(&res_nodes);
            is_path_init = 1;
        }
        else if (command == 7 && is_path_init && is_graph_init)
        {
            int n = 0;

            do
            {
                printf("Enter nodes number (1-%d):\n", g->n);
                rc = read_int(&n, MAX_STR_LEN, stdin);
                if (rc != EXIT_SUCCESS || n < 1 || n > g->n)
                { 
                    rc = EXIT_FAILURE;
                    printf("ERROR: Wrong node number, it must be from 1 to %d\n", g->n);
                }
            } while (rc != EXIT_SUCCESS);

            vector_t *path_to_n = get_path_to_t(path, n);

            printf("Path from %d to %d\n", start_node, n);

            if (path_to_n && path_to_n->size)
                vector_print(path_to_n, ' ', '\n');
            else 
                printf("No path\n");

            if (path_to_n)
                vector_free(&path_to_n);
        }
        else if (command == 8 && is_graph_init)
        {
            if (is_graph_connected(g))
                minimum_spanning_tree(g);
            else
                printf("Your graph is not connected and can't build spanning tree\n");
        }
        else if (command == 9)
        {
            print_time_measurements();
        }
        else
        {
            printf("You need init graph before doing something!\n");
        }
    }

    if (g)
        graph_free(&g);
    
    if (path)
        path_free(&path);

    return EXIT_SUCCESS;
}

#include "my_menu.h"

int main(void)
{
    int rc = menu();
    return rc;

    /*
        graph_t *g = NULL;
    graph_init(&g, 5);

    int data[5][5] =
    {
        {0, 1, 1, 0, 0},
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 0, 1},
        {0, 1, 1, 0, 0},
    };

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            g->paths[i][j] = data[i][j];

    graph_open_img("src", g);

    path_t *path = NULL;
    int start_node = 0;

    dijkstra(g, &path, start_node);

    printf("lens:\n");
    for (int i = 0; i < g->n; i++)
        printf("%d) %d\n", i + 1, path->lens[i]);

    printf("nodes_marked:\n");
    for (int i = 0; i < g->n; i++)
        printf("%d) %d\n", i + 1, path->nodes_marked[i]);

    printf("path:\n");
    for (int i = 0; i < g->n; i++)
        printf("%d) %d\n", i + 1, path->path[i]);


    int a = 3;

    vector_t *res = get_nodes_len_le_a(path, a);

    vector_print(res, ' ', '\n');

    vector_t *path_to_5 = get_path_to_t(path, 5);

    vector_print(path_to_5, ' ', '\n');

    graph_free(&g);
    path_free(&path);

    vector_free(&res);
    vector_free(&path_to_5);

    */
}

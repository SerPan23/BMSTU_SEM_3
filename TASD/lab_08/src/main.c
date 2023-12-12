// #include "my_menu.h"

#include "defines.h"
#include "useful_funcs.h"
#include "my_graph.h"

int main(void)
{
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


    int a = 1;

    vector_t *res = get_nodes_len_le_a(path, a);

    vector_print(res, ' ', '\n');

    graph_free(&g);
    vector_free(&res);

    // int rc = menu();
    // return rc;
}

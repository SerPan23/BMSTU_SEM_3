#include "my_graph.h"

int path_init(path_t **path, int n)
{
    *path = malloc(sizeof(path_t));
    if (!(*path))
        return ERROR_MEMMORY_ALLOC;

    (*path)->n = n;
    (*path)->start_node = -1;

    (*path)->lens = calloc(n, sizeof(int));
    if (!(*path)->lens)
        return ERROR_MEMMORY_ALLOC;

    for (int i = 0; i < n; i++)
        (*path)->lens[i] = INF;

    (*path)->nodes_marked = calloc(n, sizeof(int));
    if (!(*path)->nodes_marked)
        return ERROR_MEMMORY_ALLOC;

    (*path)->path = calloc(n, sizeof(int));
    if (!(*path)->path)
        return ERROR_MEMMORY_ALLOC;

    return EXIT_SUCCESS;
}

void path_free(path_t **path)
{
    free((*path)->lens);
    free((*path)->nodes_marked);
    free((*path)->path);
    free((*path));
    path = NULL;
}

int graph_init(graph_t **g, int n)
{
    *g = malloc(sizeof(graph_t));
    if (!(*g))
        return ERROR_MEMMORY_ALLOC;

    (*g)->n = n;

    (*g)->paths = calloc(n, sizeof(int *));
    if (!(*g)->paths)
        return ERROR_MEMMORY_ALLOC;

    for (int i = 0; i < n; i++)
    {
        (*g)->paths[i] = calloc(n, sizeof(int));
        if (!(*g)->paths[i])
            return ERROR_MEMMORY_ALLOC;
        
        for (int j = 0; j < n; j++)
            (*g)->paths[i][j] = 0;
    }

    return EXIT_SUCCESS;
}

void graph_free(graph_t **g)
{
    for (int i = 0; i < (*g)->n; i++)
    {
        free((*g)->paths[i]);
    }

    free(*g);
    g = NULL;
}

int graph_add_node(graph_t *g, int v, int u, int len)
{
    g->paths[v][u] = len;
    return EXIT_SUCCESS;
}

void graph_to_dot(FILE *f, const char *graph_name, graph_t *g)
{
    fprintf(f, "digraph %s {\n", graph_name);

    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < g->n; j++)
        {
            if (g->paths[i][j] != 0)
                fprintf(f, "%d -> %d [weight = %d];\n", i + 1, j + 1, g->paths[i][j]);
        }
    }
    
    fprintf(f, "}\n");
}

int graph_open_img(char *filename, graph_t *g)
{
    char *path = malloc(sizeof(char) * strlen(filename) + 30);
    if (!path)
        return ERROR_MEMMORY_ALLOC;

    sprintf(path, "./img/%s.dot", filename);

    FILE *out_img = fopen(path, "w");
    if (!out_img)
        return ERROR_MAKE_IMG;
    graph_to_dot(out_img, "test", g);
    fclose(out_img);

    char *command = malloc(sizeof(char) * (strlen(filename) * 2 + 100));
    if (!command)
        return ERROR_MEMMORY_ALLOC;

    sprintf(command,
            "dot -Tpng %s -o ./img/output_%s.png && open ./img/output_%s.png", path, filename, filename);

    system(command);

    return EXIT_SUCCESS;
}

int dijkstra(graph_t *g, path_t **path, int start_node)
{
    int rc = path_init(path, g->n);
    if (rc != EXIT_SUCCESS)
        return rc;

    (*path)->lens[start_node] = 0;

    for (int i = 0; i < g->n; i++)
    {
        int v = -1;
        for (int j = 0; j < g->n; j++)
            if (!(*path)->nodes_marked[j] && (v == -1 || (*path)->lens[j] < (*path)->lens[v]))
                v = j;
        if ((*path)->lens[v] == INF)
            break;
        
        (*path)->nodes_marked[v] = 1;

        for (int j = 0; j < g->n; j++)
        {
            if (g->paths[v][j] == 0)
                continue;

            int to = j,
                len = g->paths[v][j];

            if ((*path)->lens[v] + len < (*path)->lens[to])
            {
                (*path)->lens[to] = (*path)->lens[v] + len;
                (*path)->path[to] = v;
            }
        }
    }

    return EXIT_SUCCESS;
}

vector_t *get_nodes_len_le_a(path_t *path, int a)
{
    vector_t *dst = NULL;
    int rc = vector_init(&dst, path->n);
    if (rc != EXIT_SUCCESS)
        return NULL;

    for (int i = 0; i < path->n; i++)
        if (path->lens[i] <= a)
            vector_push(dst, i + 1);

    return dst;
}

vector_t *get_path_to_t(path_t *path, int t)
{
    vector_t *dst = NULL;
    int rc = vector_init(&dst, path->n);
    if (rc != EXIT_SUCCESS)
        return NULL;

    for (int v = t; v != path->start_node; v = path->path[v])
        vector_push(dst, v);

    vector_push(dst, path->start_node);
    vector_reverse(dst);

    return dst;
}

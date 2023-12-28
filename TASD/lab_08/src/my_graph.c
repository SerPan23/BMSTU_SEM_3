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

    (*g)->edge_count = 0;

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

int graph_add_edge(graph_t *g, int v, int u, int len)
{
    if (len < 1)
        return EXIT_FAILURE;

    // printf("%d %d %d\n", v, u, len);
    // if (v <= u)
    //     g->paths[v][u] = len;
    // else
    //     g->paths[u][v] = len;
    g->paths[v][u] = len;
    g->paths[u][v] = len;
    g->edge_count++;
    return EXIT_SUCCESS;
}

int is_edge_init(graph_t *g, int v, int u)
{
    return (g->paths[v][u] || g->paths[u][v]);
}

void read_edge(int n, int *v, int *u, int *len)
{
    int tmp = 0, rc = EXIT_SUCCESS;

    do
    {
        printf("Enter from node number (1-%d):\n", n);
        rc = read_int(&tmp, MAX_STR_LEN, stdin);
        if (rc != EXIT_SUCCESS || tmp < 1 || tmp > n)
        {
            rc = EXIT_FAILURE;
            printf("ERROR: Wrong node number, it must be from 1 to %d\n", n);
        }
    } while (rc != EXIT_SUCCESS);
    *v = tmp;

    do
    {
        printf("Enter to node number (1-%d):\n", n);
        rc = read_int(&tmp, MAX_STR_LEN, stdin);
        if (rc != EXIT_SUCCESS || tmp < 1 || tmp > n)
        {
            rc = EXIT_FAILURE;
            printf("ERROR: Wrong node number, it must be from 1 to %d\n", n);
        }
    } while (rc != EXIT_SUCCESS);
    *u = tmp;

    do
    {
        printf("Enter edge len (> 0):\n");
        rc = read_int(&tmp, MAX_STR_LEN, stdin);
        if (rc != EXIT_SUCCESS || tmp < 1)
        {
            rc = EXIT_FAILURE;
            printf("ERROR: Wrong lem, it must be from 1\n");
        }
    } while (rc != EXIT_SUCCESS);
    *len = tmp;
}

void graph_to_dot(FILE *f, const char *graph_name, graph_t *g)
{
    fprintf(f, "graph %s {\n", graph_name);

    for (int i = 0; i < g->n; i++)
    {
        for (int j = i + 1; j < g->n; j++)
        {
            if (g->paths[i][j] != 0)
                fprintf(f, "%d -- %d [weight = %d; label = %d];\n",
                        i + 1, j + 1, g->paths[i][j], g->paths[i][j]);
        }
    }
    
    fprintf(f, "}\n");
}

int graph_open_img(char *filename, graph_t *g)
{
    // for (int i = 0; i < g->n; i++)
    // {
    //     for (int j = 0; j < g->n; j++)
    //     {
    //         printf("%d\t", g->paths[i][j]);
    //     }
    //     printf("\n");
    // }

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
    (*path)->start_node = start_node;

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
        if (path->lens[i] && path->lens[i] <= a)
            vector_push(dst, i + 1);

    return dst;
}

vector_t *get_path_to_t(path_t *path, int to)
{
    vector_t *dst = NULL;
    int rc = vector_init(&dst, path->n);
    if (rc != EXIT_SUCCESS)
        return NULL;

    int t = to - 1;

    for (int v = t; v != path->start_node; v = path->path[v])
        vector_push(dst, v + 1);

    vector_push(dst, path->start_node + 1);

    vector_reverse(dst);

    if (dst->size == 1)
    {
        vector_free(&dst);
        return NULL;
    }

    if (dst->size == 2 && path->lens[dst->data[1]] == INF)
    {
        vector_free(&dst);
        return NULL;
    }

    return dst;
}

int graph_read_from_file(graph_t **g, FILE *file)
{
    int rc = EXIT_SUCCESS; 
    int n = 0;
    if (fscanf(file, "%d", &n) != 1)
        return ERROR_INVALID_NUM;
    
    rc = graph_init(g, n);
    if (rc != EXIT_SUCCESS)
        return rc;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int tmp;
            if (fscanf(file, "%d", &tmp) != 1)
                return ERROR_INVALID_NUM;
            graph_add_edge(*g, i, j, tmp);
        }
    }

    return EXIT_SUCCESS;
}

int is_graph_connected(graph_t *g)
{
    int visited[g->n], queue[g->n];
    int i, front = -1, rear = -1, count = 1, current_node;

    for (i = 0; i < g->n; i++)
        visited[i] = 0;

    visited[0] = 1;
    queue[++rear] = 0;

    while (front != rear)
    {
        current_node = queue[++front];

        for (i = 0; i < g->n; i++)
        {
            if (g->paths[current_node][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                queue[++rear] = i;
                count++;
            }
        }
    }

    if (count == g->n)
        return 1;

    return 0;
}

int findMinVertex(int cost[], int visited[], int vertices)
{
    int minCost = INF, minVertex = -1;
    int i;

    for (i = 0; i < vertices; i++)
    {
        if (visited[i] == 0 && cost[i] < minCost)
        {
            minCost = cost[i];
            minVertex = i;
        }
    }

    return minVertex;
}

void print_spanning_tree_dot(graph_t *g, int *parent)
{
    char *filepath = "./img/graph.dot";
    FILE *fp;
    fp = fopen(filepath, "w");

    fprintf(fp, "graph G {\n");

    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < g->n; j++)
        {
            if (g->paths[i][j] != 0 && parent[j] == i)
            {
                fprintf(fp, "%d -- %d [label=\"%d\"];\n", i + 1, j + 1, g->paths[i][j]);
            }
        }
    }

    fprintf(fp, "}\n");

    fclose(fp);

    char *command = malloc(sizeof(char) * (strlen("graph") * 2 + 100));

    sprintf(command,
            "dot -Tpng %s -o ./img/%s.png && open ./img/%s.png", filepath, "graph", "graph");

    system(command);
}

void minimum_spanning_tree(graph_t *g)
{
    int parent[g->n];
    int cost[g->n];
    int visited[g->n];
    int i, j, count, current_node;
    int minCost = 0;

    for (i = 0; i < g->n; i++)
    {
        cost[i] = INF;
        visited[i] = 0;
    }

    parent[0] = -1;
    cost[0] = 0;

    for (count = 0; count < g->n - 1; count++)
    {
        current_node = findMinVertex(cost, visited, g->n);
        visited[current_node] = 1;

        for (j = 0; j < g->n; j++)
        {
            if (g->paths[current_node][j] != 0 && visited[j] == 0 && g->paths[current_node][j] < cost[j])
            {
                parent[j] = current_node;
                cost[j] = g->paths[current_node][j];
            }
        }
    }

    // // Выводим остовное дерево
    // printf("Остовное дерево минимальной стоимости:\n");
    // printf("Ребро   Вес\n");

    for (i = 1; i < g->n; i++)
    {
        // printf("%d - %d   %d\n", parent[i], i, cost[i]);
        minCost += cost[i];
    }

    printf("Общая стоимость остовного дерева: %d\n", minCost);

    print_spanning_tree_dot(g, parent);
}


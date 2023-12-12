#ifndef MY_GRAPH_H
#define MY_GRAPH_H

#include "defines.h"
#include "useful_funcs.h"
#include "my_vector.h"

typedef struct path
{
    int n;
    int start_node;
    int *lens;
    int *nodes_marked;
    int *path;
} path_t;

int path_init(path_t **path, int n);
void path_free(path_t **path);

typedef struct graph
{
    int n;
    int **paths;
} graph_t;

int graph_init(graph_t **g, int n);
void graph_free(graph_t **g);
int graph_add_node(graph_t *g, int v, int u, int len);
void graph_to_dot(FILE *f, const char *graph_name, graph_t *g);
int graph_open_img(char *filename, graph_t *g);

int dijkstra(graph_t *g, path_t **path, int start_node);
vector_t *get_nodes_len_le_a(path_t *path, int a);
vector_t *get_path_to_t(path_t *path, int t);

#endif

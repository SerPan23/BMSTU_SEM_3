#ifndef MY_TREE_H
#define MY_TREE_H

#include "defines.h"
#include "useful_funcs.h"

typedef struct tree_node
{  
    char value;
    size_t count;
    struct tree_node *parent;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

int node_init(tree_node_t *node);
void node_free(tree_node_t *node);

void tree_free(tree_node_t **tree);

int tree_add_el(tree_node_t **tree, char value);
void tree_print_like_tree(tree_node_t *tree);
void tree_print_post_order(tree_node_t *tree);
int tree_del_not_unique_nodes(tree_node_t **tree);

#endif

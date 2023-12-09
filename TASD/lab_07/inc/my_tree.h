#ifndef MY_TREE_H
#define MY_TREE_H

#include "defines.h"
#include "useful_funcs.h"
#include "dynamic_array.h"

typedef struct tree_node
{  
    char value;
    size_t count;
    struct tree_node *parent;
    struct tree_node *left;
    struct tree_node *right;
    int height;
} tree_node_t;

int node_init(tree_node_t **node, char value);
void node_free(tree_node_t *node);

void tree_free(tree_node_t **tree);

tree_node_t *tree_create_from_str(char *str, size_t len);
int tree_add_el(tree_node_t **tree, char value);
void tree_search(tree_node_t **tree, tree_node_t **node, char value, int *finded, int *cmp_count);
void tree_search_in_sorted(tree_node_t **tree, tree_node_t **node, char value, int *finded, int *cmp_count);
void tree_print_post_order(tree_node_t *tree);
void tree_del_not_unique_nodes(tree_node_t **tree);
int tree_count_nodes(tree_node_t *tree);

void tree_apply_pre(tree_node_t *tree, void (*f)(tree_node_t *, void *), void *arg);
void tree_export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree);
int open_tree_img(char *filename, tree_node_t *tree);

tree_node_t *tree_balance_BST(tree_node_t *tree);

tree_node_t *AVL_tree_from_tree(tree_node_t *tree);

#endif

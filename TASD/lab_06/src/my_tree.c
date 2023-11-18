#include "my_tree.h"

int node_init(tree_node_t *node)
{
    (node) = malloc(sizeof(tree_node_t));
    if (!(node))
        return ERROR_MEMMORY_ALLOC;
    (node)->count = 0;
    (node)->value = '0';
    (node)->parent = NULL;
    (node)->left = NULL;
    (node)->right = NULL;
    return EXIT_SUCCESS;
}

void node_free(tree_node_t *node)
{
    if (node)
        free(node);
}

void tree_free(tree_node_t **tree)
{
    if (tree == NULL)
        return;

    tree_free(&(*tree)->left);
    tree_free(&(*tree)->right);
    node_free((*tree));
    tree = NULL;
}

tree_node_t *find_el_pos(tree_node_t *tree, char value)
{ 
    if (tree == NULL)
        return NULL;

    printf("*%c\n", tree->value);

    tree_node_t *parent = tree;

    while (tree != NULL)
    {
        if (tree->value == value)
            return parent;
        else if (tree->value > value)
        {
            parent = tree;
            tree = tree->left;
        }
        else
        {
            parent = tree;
            tree = tree->right;
        }
    }

    return parent;
}

int tree_add_el(tree_node_t **tree, char value)
{
    tree_node_t *tmp = NULL;
    if ((*tree))
        tmp = find_el_pos((*tree), value);

    if (!tmp)
    {
        tree_node_t node;
        int rc = node_init(&node);
        if (rc != EXIT_SUCCESS)
            return rc;
        (*tree) = &node;
    }
    else if (tmp->value == value)
        tmp->count++;
    else
    {
        tree_node_t node;
        int rc = node_init(&node);
        if (rc != EXIT_SUCCESS)
            return rc;
        node.value = value;
        node.parent = tmp;
        
        if (tmp->value > node.value)
            tmp->left = &node;
        else
            tmp->right = &node;
    }
    return EXIT_SUCCESS;
}

void tree_print_like_tree(tree_node_t *tree)
{
    tree->count++;
} 

void tree_print_post_order(tree_node_t *tree)
{
    if (tree == NULL)
        return;

    tree_print_post_order(tree->left);
    tree_print_post_order(tree->right);
    printf("%c\n", tree->value);
}

int tree_del_not_unique_nodes(tree_node_t **tree)
{
    (*tree)->count++;
    return EXIT_SUCCESS;
}

#include "my_tree.h"

int node_init(tree_node_t **node, char value)
{
    (*node) = malloc(sizeof(tree_node_t));
    if (!(node))
        return ERROR_MEMMORY_ALLOC;
    (*node)->count = 1;
    (*node)->value = value;
    (*node)->parent = NULL;
    (*node)->left = NULL;
    (*node)->right = NULL;
    return EXIT_SUCCESS;
}

void node_free(tree_node_t *node)
{
    if (node)
        free(node);
}

void tree_free(tree_node_t **tree)
{
    if (!(*tree))
        return;

    tree_free(&(*tree)->left);
    tree_free(&(*tree)->right);
    node_free((*tree));
    *tree = NULL;
}

tree_node_t *find_el_pos(tree_node_t *tree, char value)
{ 
    if (!tree)
        return NULL;

    // printf("#%c (%c)\n", value, tree->value);

    tree_node_t *parent = tree;

    while (tree)
    {
        // printf("NODE: %c %zu %p %p %p\n", tree->value, tree->count,
        //        (void *)tree->parent, (void *)tree->left, (void *)tree->right);
        if (tree->value == value)
        {
            // printf("*1\n");
            return tree;
        }
        else if (tree->value > value)
        {
            // printf("*2\n");
            parent = tree;
            if (!tree)
                break;
            tree = tree->left;
        }
        else
        {
            // printf("*3\n");
            parent = tree;
            if (!tree)
                break;
            tree = tree->right;
        }
    }

    return parent;
}

int tree_add_el(tree_node_t **tree, char value)
{
    // printf("#%c\n", value);
    tree_node_t *pos = find_el_pos((*tree), value);
    // printf("\t%p\n", (void *)pos);

    if (pos && pos->value == value)
    {
        // printf("NODE: %c %zu %p %p %p\n", pos->value, pos->count,
        //        (void *)pos->parent, (void *)pos->left, (void *)pos->right);
        pos->count++;
    }
    else
    {
        tree_node_t *node = NULL;
        int rc = node_init(&node, value);
        if (rc != EXIT_SUCCESS)
            return rc;

        if (!pos)
        {
            node->parent = NULL;
            (*tree) = node;
        }
        else
        {
            node->parent = pos;

            if (pos->value > node->value)
                pos->left = node;
            else
                pos->right = node;
        }
    }

    return EXIT_SUCCESS;
}

tree_node_t *tree_create_from_str(char *str, size_t len)
{
    tree_node_t *tree = NULL;
    for (size_t i = 0; i < len; i++)
        if (isalnum(str[i]))
            tree_add_el(&tree, str[i]);

    return tree;
}

void tree_print_post_order(tree_node_t *tree)
{
    if (tree == NULL)
        return;

    tree_print_post_order(tree->left);
    tree_print_post_order(tree->right);
    // printf("%c (%zu)\n", tree->value, tree->count);
    printf("%c\n", tree->value);
}

tree_node_t *tree_min_node(tree_node_t *tree)
{
    while (tree->left)
        tree = tree->left;
    return tree;
}

tree_node_t *deleteNode(tree_node_t *root, tree_node_t *nodeToDelete)
{
    if (!root)
        return root;

    if (nodeToDelete->value < root->value)
        root->left = deleteNode(root->left, nodeToDelete);
    else if (nodeToDelete->value > root->value)
        root->right = deleteNode(root->right, nodeToDelete);
    else
    {
        if (!root->left && !root->right)
        {   if (root->parent)
            {
                if (root == root->parent->left)
                    root->parent->left = NULL;
                else
                    root->parent->right = NULL;
            }
            node_free(root);
            root = NULL;
        }
        else if (!root->left)
        {
            tree_node_t *tmp = root;
            root = root->right;
            root->parent = tmp->parent;
            node_free(tmp);
        }
        else if (!root->right)
        {
            tree_node_t *tmp = root;
            root = root->left;
            root->parent = tmp->parent;
            node_free(tmp);
        }
        else
        {
            tree_node_t *tmp = tree_min_node(root->right);
            root->value = tmp->value;
            root->count = tmp->count;
            root->right = deleteNode(root->right, tmp);
        }
    }
    return root;
}

void tree_search_not_unique_node(tree_node_t **tree, tree_node_t **node)
{
    if (!(*tree))
        return;

    tree_search_not_unique_node(&(*tree)->left, node);
    tree_search_not_unique_node(&(*tree)->right, node);

    if ((*tree)->count > 1)
        *node = *tree;
}

void tree_del_not_unique_nodes(tree_node_t **tree)
{
    tree_node_t *tmp = NULL;

    tree_search_not_unique_node(tree, &tmp);

    // size_t i = 0;
    while(tmp && tree)
    {
        
        // char s[MAX_STR_LEN + 1];
        // sprintf(s, "%zu", i);
        // open_tree_img(strcat(s, "test"), *tree);

        *tree = deleteNode(*tree, tmp);
        tmp = NULL;

        tree_search_not_unique_node(tree, &tmp);

        // i++;
    }
}

void tree_apply_pre(tree_node_t *tree, void (*f)(tree_node_t *, void *), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    tree_apply_pre(tree->left, f, arg);
    tree_apply_pre(tree->right, f, arg);
}

void to_dot(tree_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%c -> %c;\n", tree->value, tree->left->value);

    if (tree->right)
        fprintf(f, "%c -> %c;\n", tree->value, tree->right->value);
}

void to_color_node(tree_node_t *tree, void *param)
{
    FILE *f = param;
    if (tree->count > 1)
        fprintf(f, "%c [color=red];\n", tree->value);
    else
        fprintf(f, "%c;\n", tree->value);
}

void tree_export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree)
{
    fprintf(f, "digraph %s {\n\
    node [shape=circle, fontname=\"Arial\", fontsize=12];\
    edge [fontsize=10];", tree_name);

    tree_apply_pre(tree, to_color_node, f);

    tree_apply_pre(tree, to_dot, f);

    fprintf(f, "}\n");
}

int open_tree_img(char *filename, tree_node_t *tree)
{
    char *path = malloc(sizeof(char) * strlen(filename) + 30);
    if (!path)
        return ERROR_MEMMORY_ALLOC;

    sprintf(path, "./img/%s.dot", filename);

    FILE *out_img = fopen(path, "w");
    if (!out_img)
        return ERROR_MAKE_IMG;
    tree_export_to_dot(out_img, "test", tree);
    fclose(out_img);

    char *command = malloc(sizeof(char) * (strlen(filename) * 2 + 100));
    if (!command)
        return ERROR_MEMMORY_ALLOC;

    sprintf(command,
            "dot -Tpng %s -o ./img/output_%s.png && open ./img/output_%s.png", path, filename, filename);

    system(command);

    return EXIT_SUCCESS;
}

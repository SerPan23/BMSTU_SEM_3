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
    (*node)->height = 1;
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

void tree_search(tree_node_t **tree, tree_node_t **node, char value, int *finded, int *cmp_count)
{
    if (!(*tree))
        return;

    if (*finded)
        return;

    if (cmp_count != NULL && !(*finded))
        ++(*cmp_count);
    
    if ((*tree)->value == value)
    {
        *node = *tree;
        *finded = 1;
        return;
    }
    tree_search(&(*tree)->left, node, value, finded, cmp_count);
    tree_search(&(*tree)->right, node, value, finded, cmp_count);
}

void tree_search_in_sorted(tree_node_t **tree, tree_node_t **node, char value, int *finded, int *cmp_count)
{    
    if (!(*tree))
        return;

    if (*finded)
        return;

    if (cmp_count != NULL && !(*finded))
        ++(*cmp_count);
    
    if ((*tree)->value == value)
    {
        *node = *tree;
        *finded = 1;
        return;
    }
    else if ((*tree)->value > value)
    {
        tree_search(&(*tree)->left, node, value, finded, cmp_count);
    }
    else if((*tree)->value < value)
    {
        tree_search(&(*tree)->right, node, value, finded, cmp_count);
    }
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

tree_node_t *buildBalancedTree(dynamic_array_t *arr, int start, int end, tree_node_t *parent)
{
    if (start > end)
    {
        return NULL;
    }

    int mid = (start + end) / 2;

    tree_node_t *root = NULL;
    char *p_value = (char *)arr->data[mid];
    int rc = node_init(&root, *p_value);
    if (rc != EXIT_SUCCESS)
        return NULL;

    root->parent = parent;

    root->left = buildBalancedTree(arr, start, mid - 1, root);
    root->right = buildBalancedTree(arr, mid + 1, end, root);

    return root;
}

void tree_to_array(tree_node_t *node, dynamic_array_t *arr)
{
    if (node == NULL)
    {
        return;
    }

    // dynamic_arr_push(arr, (void *)(&node->value));
    tree_to_array(node->left, arr);
    dynamic_arr_push(arr, (void *)(&node->value));
    tree_to_array(node->right, arr);
    // dynamic_arr_push(arr, (void *)(&node->value));
}

tree_node_t *tree_balance_BST(tree_node_t *tree)
{
    dynamic_array_t arr;
    dynamic_arr_init(&arr);

    tree_to_array(tree, &arr);

    tree_node_t *balancedRoot = buildBalancedTree(&arr, 0, arr.size - 1, NULL);

    dynamic_arr_destroy(&arr);

    return balancedRoot;
}

int tree_count_nodes(tree_node_t *tree)
{
    if (tree == NULL)
        return 0;

    return tree_count_nodes(tree->left) + tree_count_nodes(tree->right) + 1;
}


// AVL TREE

int max(char a, char b)
{
    return (a > b) ? a : b;
}

int node_get_height(tree_node_t *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

tree_node_t *AVL_tree_right_rotate(tree_node_t *y)
{
    tree_node_t *x = y->left;
    tree_node_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(node_get_height(y->left), node_get_height(y->right)) + 1;
    x->height = max(node_get_height(x->left), node_get_height(x->right)) + 1;

    if (T2 != NULL)
        T2->parent = y;
    x->parent = y->parent;
    y->parent = x;

    return x;
}

tree_node_t *AVL_tree_left_rotate(tree_node_t *x)
{
    tree_node_t *y = x->right;
    tree_node_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(node_get_height(x->left), node_get_height(x->right)) + 1;
    y->height = max(node_get_height(y->left), node_get_height(y->right)) + 1;

    if (T2 != NULL)
        T2->parent = x;
    y->parent = x->parent;
    x->parent = y;

    return y;
}

int get_balance(tree_node_t *node)
{
    if (node == NULL)
        return 0;

    return node_get_height(node->left) - node_get_height(node->right);
}

tree_node_t *AVL_tree_insert(tree_node_t *node, char value)
{
    if (node == NULL)
    {
        tree_node_t *new_node = NULL;
        int rc = node_init(&new_node, value);
        if (rc != EXIT_SUCCESS)
            return NULL;

        return new_node;
    }

    if (value < node->value)
    {
        tree_node_t *left_child = AVL_tree_insert(node->left, value);
        node->left = left_child;
        left_child->parent = node;
    }
    else if (value > node->value)
    {
        tree_node_t *right_child = AVL_tree_insert(node->right, value);
        node->right = right_child;
        right_child->parent = node;
    }
    else
        return node;

    node->height = 1 + max(node_get_height(node->left), node_get_height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && value < node->left->value)
        return AVL_tree_right_rotate(node);

    if (balance < -1 && value > node->right->value)
        return AVL_tree_left_rotate(node);

    if (balance > 1 && value > node->left->value)
    {
        node->left = AVL_tree_left_rotate(node->left);
        return AVL_tree_right_rotate(node);
    }

    if (balance < -1 && value < node->right->value)
    {
        node->right = AVL_tree_right_rotate(node->right);
        return AVL_tree_left_rotate(node);
    }

    return node;
}


tree_node_t *AVL_tree_from_tree(tree_node_t *tree)
{
    dynamic_array_t arr;
    dynamic_arr_init(&arr);

    tree_to_array(tree, &arr);

    tree_node_t *avl_tree = NULL;

    for (size_t i = 0; i < arr.size; i++)
    {
        char *t = arr.data[i];
        avl_tree = AVL_tree_insert(avl_tree, *t);
    }

    dynamic_arr_destroy(&arr);

    return avl_tree;
}

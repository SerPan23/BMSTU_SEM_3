#include "my_tree.h"

int main(void)
{
    tree_node_t *tree = NULL;
    // node_init(tree);

    const size_t n = 5;
    char els[n] = { '1', '2', '3', '4', '5' };

    for (size_t i = 0; i < n; i++)
        tree_add_el(&tree, els[i]);
    
    tree_print_post_order(tree);
    tree_free(&tree);

    return 0;
}

#include "libft/CPP_class/class_nullptr.hpp"
#include "treeNode.hpp"

TreeNode **ft_return_main_treeNode(void)
{
    static TreeNode *treenode = ft_nullptr;
    if (!treenode)
        treenode = tree_node_new();
    return (&treenode);
}

void ft_cleanup_treeNode(void)
{
    TreeNode **node = ft_return_main_treeNode();
    tree_node_delete(*node);
    *node = ft_nullptr;
    return ;
}

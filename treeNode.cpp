#include "treeNode.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Libft/libft.hpp"
#include <csignal>
#include <cassert>

TreeNode *tree_node_new(void)
{
    TreeNode *node = static_cast<TreeNode *>(cma_malloc(sizeof(TreeNode)));
    if (!node)
        return (ft_nullptr);
    new (&node->_children) ft_unord_map<char, TreeNode*>();
    node->_data  = ft_nullptr;
    node->_error = 0;
    return (node);
}

void tree_node_delete(TreeNode *node)
{
    if (!node)
        return ;
    auto it = node->_children.begin();
    while (it != node->_children.end())
    {
        tree_node_delete(it->second);
        ++it;
    }
    node->_children.~ft_unord_map<char, TreeNode*>();
    if (node->_data)
        cma_free(node->_data);
    cma_free(node);
    return ;
}

static int tree_node_insert_helper(TreeNode *node, const char *key, int unset_value,
                              int *int_val, char **str_val, char ***dbl_val)
{
    if (node->_error)
        return (1);
    size_t length = ft_strlen_size_t(key);
    TreeNode *current = node;
    const char *ptr = key;
    while (*ptr)
    {
        char ch = *ptr++;
        if (!current->_children[ch])
        {
            TreeNode *child = tree_node_new();
            if (!child)
            {
                node->_error = 1;
                return (1);
            }
            current->_children[ch] = child;
        }
        current = current->_children[ch];
    }
    if (!current->_data)
    {
        current->_data = static_cast<t_treeNode_value *>(cma_malloc(sizeof(t_treeNode_value)));
        if (!current->_data)
        {
            node->_error = 1;
            return (1);
        }
    }
    ft_bzero(current->_data, sizeof(t_treeNode_value));
    current->_data->_unset_value           = unset_value;
    current->_data->_key_length            = length;
    current->_data->_return_field_integer  = int_val;
    current->_data->_return_field_string   = str_val;
    current->_data->_return_field_double   = dbl_val;
    return (0);
}

int tree_node_insert(TreeNode *node, const char *key, int *value, int unset_value)
{
    return (tree_node_insert_helper(node, key, unset_value, value, ft_nullptr, ft_nullptr));
}

int tree_node_insert(TreeNode *node, const char *key, char **value)
{
    return (tree_node_insert_helper(node, key, 0, ft_nullptr, value, ft_nullptr));
}

int tree_node_insert(TreeNode *node, const char *key, char ***value)
{
    return (tree_node_insert_helper(node, key, 0, ft_nullptr, ft_nullptr, value));
}

const t_treeNode_value *tree_node_search(const TreeNode *node, const char *key)
{
    if (node->_error)
        return (ft_nullptr);
    const TreeNode *current = node;
    while (*key != '=')
    {
        auto it = current->_children.find(*key);
        if (it == current->_children.end())
            return (ft_nullptr);
        current = it->second;
        key++;
    }
    if (*key == '=')
    {
        auto it = current->_children.find(*key);
        if (it == current->_children.end())
            return (ft_nullptr);
        current = it->second;
        key++;
    }
    else
        return (ft_nullptr);
    return (current->_data);
}

int tree_node_get_error(const TreeNode *node)
{
    return (node->_error);
}


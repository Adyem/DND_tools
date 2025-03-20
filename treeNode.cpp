#include "treeNode.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Libft/libft.hpp"
#include <csignal>
#include <cassert>

TreeNode *tree_node_new(void)
{
    TreeNode *node = static_cast<TreeNode *>(cma_malloc(sizeof(TreeNode)));
    if (!node)
        return (ft_nullptr);
    new (&node->children) ft_unord_map<char, TreeNode*>();
    node->data  = ft_nullptr;
    node->error = 0;
    return (node);
}

void tree_node_delete(TreeNode *node)
{
    if (!node)
        return ;
    for (auto &pair : node->children)
    {
        tree_node_delete(pair.second);
    }
    node->children.~ft_unord_map<char, TreeNode*>();
    if (node->data)
        cma_free(node->data);
    cma_free(node);
	return ;
}

static int tree_node_insert_helper(TreeNode *node, const char *key, int unset_value,
                              int *intVal, char **strVal, char ***dblVal)
{
    if (node->error)
        return (1);
    size_t length = ft_strlen_size_t(key);
    TreeNode *current = node;
    const char *ptr = key;
    while (*ptr)
    {
        char ch = *ptr++;
        if (!current->children[ch])
        {
            TreeNode *child = tree_node_new();
            if (!child)
            {
                node->error = 1;
                return (1);
            }
            current->children[ch] = child;
        }
        current = current->children[ch];
    }
    if (!current->data)
    {
        current->data = static_cast<t_treeNode_value *>(cma_malloc(sizeof(t_treeNode_value)));
        if (!current->data)
        {
            node->error = 1;
            return (1);
        }
    }
    ft_bzero(current->data, sizeof(t_treeNode_value));
    current->data->unset_value           = unset_value;
    current->data->key_length            = length;
    current->data->return_field_integer  = intVal;
    current->data->return_field_string   = strVal;
    current->data->return_field_double   = dblVal;
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
    if (node->error)
        return (ft_nullptr);
    const TreeNode *current = node;
    while (*key != '=')
    {
        auto it = current->children.find(*key);
        if (it == current->children.end())
            return (ft_nullptr);
        current = it->second;
        key++;
    }
    if (*key == '=')
    {
        auto it = current->children.find(*key);
        if (it == current->children.end())
            return (ft_nullptr);
        current = it->second;
        key++;
    }
    else
        return (ft_nullptr);
    return (current->data);
}

int tree_node_get_error(const TreeNode *node)
{
    return (node->error);
}


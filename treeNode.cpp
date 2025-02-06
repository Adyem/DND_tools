#include "treeNode.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/unordened_map.hpp"
#include "libft/Libft/libft.hpp"
#include <csignal>
#include <cassert>

TreeNode::TreeNode() : _data(ft_nullptr), _error(0)
{
	return ;
}

TreeNode::~TreeNode()
{
    for (auto& child : children)
        delete child.second;
    return;
}

void* TreeNode::operator new(size_t size)
{
    void* ptr = cma_malloc(size);
    if (!ptr)
        std::raise(SIGABRT);
    return (ptr);
}

void TreeNode::operator delete(void* ptr) noexcept
{
	if (ptr)
        cma_free(ptr);
	return ;
}

int TreeNode::insert_helper(const char *key, int unset_value, int *intVal, char *strVal,
								char **dblVal)
{
    size_t length = ft_strlen(key);
    if (DEBUG == 1)
        pf_printf("adding %s\n", key);
    TreeNode* current = this;
    const char* ptr = key;
    while (*ptr)
    {
        char ch = *ptr++;
        if (!current->children[ch])
            current->children[ch] = new TreeNode();
        current = current->children[ch];
    }
	if (!current->_data)
        current->_data = (t_treeNode_value *)cma_malloc(sizeof(t_treeNode_value));
	if (!current->_data)
	{
		this->_error = 1;
		return (1);
	}
    ft_bzero(current->_data, sizeof(t_treeNode_value));
    current->_data->unset_value = unset_value;
    current->_data->key_length = length;
    current->_data->return_field_integer = intVal;
    current->_data->return_field_string  = strVal;
    current->_data->return_field_double  = dblVal;
    return (0);
}

int TreeNode::insert(const char *key, int *value, int unset_value)
{
    return (insert_helper(key, unset_value, value, ft_nullptr, ft_nullptr));
}

int TreeNode::insert(const char *key, char *value)
{
    return (insert_helper(key, 0, ft_nullptr, value, ft_nullptr));
}

int TreeNode::insert(const char *key, char **value)
{
    return (insert_helper(key, 0, ft_nullptr, ft_nullptr, value));
}

const t_treeNode_value *TreeNode::search(const char *key) const
{
    const TreeNode* current = this;
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
    return (current->_data);
}

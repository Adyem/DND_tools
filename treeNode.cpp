#include "treeNode.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/unordened_map.hpp"
#include <csignal>
#include <cassert>

TreeNode::TreeNode() : _error(0), _data(ft_nullptr)
{
	return ;
}

TreeNode::~TreeNode()
{
	for (auto& child : children)
		delete child.second;
	if (this->_data)
	{
		cma_free (this->_data);
		this->_data = ft_nullptr;
	}
	return;
}

void* TreeNode::operator new(size_t size)
{
	return (cma_malloc(size));
}

void TreeNode::operator delete(void* ptr) noexcept
{
	if (ptr)
		cma_free(ptr);
	return;
}

int TreeNode::get_error() const
{
	return (this->_error);
}

int TreeNode::insert(const char *key, int *value, int unset_value, int min_val, int max_val)
{
	if (DEBUG == 1)
		pf_printf("adding %s\n", key);
	if (this->_error)
		return (1);
	TreeNode* current = this;
	while (*key)
	{
		char ch = *key++;
		if (!current->children[ch])
		{
			current->children[ch] = new TreeNode();
			if (!current->children[ch] || current->children[ch]->get_error())
			{
				this->_error = 1;
				return (1);
			}
		}
		current = current->children[ch];
	}
	if (!current->_data)
	{
		current->_data = (s_treeNode_value *)cma_malloc(sizeof(s_treeNode_value));
		if (!current->_data)
		{
			this->_error = 1;
			return (1);
		}
		ft_bzero(current->_data, sizeof(s_treeNode_value));
	}
	current->_data->unset_value = unset_value;
	current->_data->return_field = value;
	current->_data->min_value = min_val;
	current->_data->max_value = max_val;
	current->_data->string_field = ft_nullptr;
	return (0);
}

t_treeNode_value *TreeNode::search(const char *key) const
{
	if (this->_error)
		return (ft_nullptr);
	int index = 0;
	const TreeNode* current = this;
	pf_printf("printing key %s\n going trough key", key);
	while (*key != '=')
	{
		index++;
		pf_printf("%c", *key);
		auto it = current->children.find(*key);
		if (it == current->children.end())
			return (ft_nullptr);
		current = it->second;
		key++;
	}
	if (*key == '=')
	{
		index++;
		pf_printf("%c\n", *key);
		auto it = current->children.find(*key);
		if (it == current->children.end())
			return (ft_nullptr);
		current = it->second;
		key++;
	}
	if (!current->_data)
		return (ft_nullptr);
	current->_data->key_length = index;
	return (current->_data);
}

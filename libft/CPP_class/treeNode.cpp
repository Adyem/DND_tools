#include "treeNode.hpp"
#include "nullptr.hpp"
#include "../Libft/libft.hpp"
#include <unordered_map>
#include <csignal>

TreeNode::~TreeNode()
{
	for (auto& child : children)
        delete child.second;
	return ;
}

int TreeNode::insert(const char* key, int* value)
{
    size_t length = ft_strlen(key);
    if (length == 0 || key[length - 1] != '=')
        raise(SIGSEGV);
    for (size_t i = 0; i < length - 1; ++i)
	{
        if (key[i] == '=')
            raise(SIGSEGV);
    }
    TreeNode* current = this;
    while (*key)
	{
        char ch = *key++;
        if (!current->children[ch])
            current->children[ch] = new TreeNode();
        current = current->children[ch];
    }
    current->result = value;
	return (0);
}

int* TreeNode::search(const char* key) const
{
    const TreeNode* current = this;
    while (*key)
	{
        auto it = current->children.find(*key);
        if (it == current->children.end())
            return (ft_nullptr);
        current = it->second;
        key++;
    }
    return (current->result);
}

#include "dnd_tools.hpp"
#include "treeNode.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/unordened_map.hpp"
#include "libft/Libft/libft.hpp"
#include <csignal>
#include <cassert>

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

int TreeNode::insert(const char *key, int *value, int unset_value)
{
    size_t length = ft_strlen(key);
    assert(key != ft_nullptr && "key cannot be ft_nullptr");
    assert(length > 0 && "Key cannot be empty");
    assert(key[length - 1] == '=' && "Key must end with '='");

    if (DEBUG == 1)
        pf_printf("adding %s\n", key);

    for (size_t index = 0; index < length - 1; ++index)
    {
        assert(key[index] != '=' && "Key cannot contain '=' except at the end");
    }

    TreeNode* current = this;
    while (*key)
    {
        char ch = *key++;
        if (!current->children[ch])
            current->children[ch] = new TreeNode();
        current = current->children[ch];
    }
    current->unset_value = unset_value;
    current->result = value;
    return 0;
}


t_treeNode_returnValue TreeNode::search(const char *key) const
{
	size_t index = 0;
    const TreeNode* current = this;
    while (*key != '=')
	{
		index++;
        auto it = current->children.find(*key);
        if (it == current->children.end())
            return {0, 0, ft_nullptr};
        current = it->second;
        key++;
    }
	if (*key == '=')
	{
		index++;
        auto it = current->children.find(*key);
        if (it == current->children.end())
            return {0, 0, ft_nullptr};
        current = it->second;
        key++;
    }
	else
		return {0, 0, ft_nullptr};
	t_treeNode_returnValue result = {static_cast<int>(index), current->unset_value,
		current->result};
    return (result);
}

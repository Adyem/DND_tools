#include "treeNode.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Template/unordened_map.hpp"
#include "libft/Libft/libft.hpp"
#include <csignal>
#include <cassert>

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

TreeNode::~TreeNode()
{
	for (auto& child : children)
        delete child.second;
	return ;
}

int TreeNode::insert(const char *key, int *value)
{
    size_t length = ft_strlen(key);
	assert(key != ft_nullptr && "key cannot be ft_nullptr");
    assert(length > 0 && "Key cannot be empty");
    assert(key[length - 1] == '=' && "Key must end with '='");
	size_t index = 0;
    while (index < length - 1)
	{
        assert(key[index] != '=' && "Key cannot contain '=' except at the end");
		index++;
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
    return 0;
}

int* TreeNode::search(const char *key) const
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

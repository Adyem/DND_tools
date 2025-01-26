#include <csignal>
#include "libft/Template/unordened_map.hpp"

class TreeNode
{
	public:
    	ft_unord_map<char, TreeNode*> children;
    	int		*result = nullptr;

    	~TreeNode();
    	int		insert(const char *key, int *value);
    	int		*search(const char *key) const;

		void* operator new(size_t size);
		void operator delete(void* ptr) noexcept;
};

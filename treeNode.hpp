#ifndef TREENODE_HPP
# define TREENODE_HPP

#include <csignal>
#include "libft/Template/unordened_map.hpp"

#ifndef DEBUG
# define DEBUG 0
#endif

class TreeNode;

typedef struct s_treeNode_returnValue
{
	int		key_length;
	int		unset_value;
	int		*return_field;
	TreeNode	*node;
} t_treeNode_returnValue;

class TreeNode
{
	public:
		ft_unord_map<char, TreeNode*> children;
		int		*result = nullptr;
		int		unset_value;
		int		min_val;
		int		max_val;

		~TreeNode();
		int		insert(const char *key, int *value, int unset_value, int min_val, int max_val);
		t_treeNode_returnValue search(const char *key) const;

		void* operator new(size_t size);
		void operator delete(void* ptr) noexcept;
};

TreeNode	**ft_return_main_treeNode(void);
void		ft_cleanup_treeNode(void);

#endif

#ifndef TREENODE_HPP
# define TREENODE_HPP

#include <csignal>
#include "libft/Template/unordened_map.hpp"

typedef struct s_treeNode_returnValue
{
	int		key_length;
	int		*return_field;
} t_treeNode_returnValue;

class TreeNode
{
	public:
    	ft_unord_map<char, TreeNode*> children;
    	int		*result = nullptr;

    	~TreeNode();
    	int		insert(const char *key, int *value);
    	t_treeNode_returnValue search(const char *key) const;

		void* operator new(size_t size);
		void operator delete(void* ptr) noexcept;
};

//treeNode
TreeNode	**ft_return_main_treeNode(void);
void		ft_cleanup_treeNode(void);

#endif

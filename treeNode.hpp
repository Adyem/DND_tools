#ifndef TREENODE_HPP
# define TREENODE_HPP

#include <csignal>
#include "libft/Template/unordened_map.hpp"

#ifndef DEBUG
# define DEBUG 0
#endif

class TreeNode;

typedef struct s_treeNode_value
{
	int		key_length;
	int		unset_value;
	int		*return_field;
	int		min_value;
	int		max_value;
	char	**string_field;
} t_treeNode_value;

class TreeNode
{
	private:
		mutable int _error;

	public:
		ft_unord_map<char, TreeNode*> children;
		s_treeNode_value *_data;

		~TreeNode();
		TreeNode();
		int		insert(const char *key, int *value, int unset_value, int min_val, int max_val);
		t_treeNode_value *search(const char *key) const;

		void* operator new(size_t size);
		void operator delete(void* ptr) noexcept;
		int get_error() const;
};

TreeNode	**ft_return_main_treeNode(void);
void		ft_cleanup_treeNode(void);

#endif

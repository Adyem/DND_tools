#ifndef TREENODE_HPP
# define TREENODE_HPP

#ifndef DEBUG
# define DEBUG 0
#endif

#include <csignal>
#include "libft/Template/unordened_map.hpp"

typedef struct s_treeNode_value
{
	int		key_length;
	int		unset_value;
	int		*return_field_integer;
	char	**return_field_string;
	char	***return_field_double;
} t_treeNode_value;

class TreeNode
{
	private:
		t_treeNode_value *_data;
		int _error;
		int insert_helper(const char *key, int unset_value, int *intVal, char **strVal,
							char ***dblVal);

	public:
    	ft_unord_map<char, TreeNode*> children;
		
		TreeNode();
    	~TreeNode();
    	int		insert(const char *key, int *value, int unset_value);
		int		insert(const char *key, char **value);
		int		insert(const char *key, char ***value);
    	const t_treeNode_value *search(const char *key) const;
		void* operator new(size_t size);
		void operator delete(void* ptr) noexcept;
		int getError() const;
};

TreeNode	**ft_return_main_treeNode(void);
void		ft_cleanup_treeNode(void);

#endif

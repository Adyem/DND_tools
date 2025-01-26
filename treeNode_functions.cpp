#include "treeNode.hpp"
#include "dnd_tools.hpp"

TreeNode *ft_return_main_treeNode(void)
{
	static TreeNode *treenode;

	if (!treenode)
		treenode = new TreeNode;
	return (treenode);
}

void	ft_cleanup_treeNode(void)
{
	delete(ft_return_main_treeNode());
	return ;
}

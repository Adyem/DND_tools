#ifndef TREENODE_HPP
#define TREENODE_HPP

#ifndef DEBUG
# define DEBUG 0
#endif

#include <csignal>
#include "libft/Template/unordened_map.hpp"

typedef struct s_treeNode_value
{
    size_t   _key_length;
    int       _unset_value;
    int       *_return_field_integer;
    char      **_return_field_string;
    char      ***_return_field_double;
} t_treeNode_value;

typedef struct s_treeNode
{
    t_treeNode_value *_data;
    int _error;
    ft_unord_map<char, struct s_treeNode*> _children;
} TreeNode;

// Function declarations for creating/destroying nodes:
TreeNode *tree_node_new(void);
void tree_node_delete(TreeNode *node);

// Insertion functions:
int tree_node_insert(TreeNode *node, const char *key, int *value, int unset_value);
int tree_node_insert(TreeNode *node, const char *key, char **value);
int tree_node_insert(TreeNode *node, const char *key, char ***value);

// Search function:
const t_treeNode_value *tree_node_search(const TreeNode *node, const char *key);

// Accessor for the error flag:
int tree_node_get_error(const TreeNode *node);

// Main tree functions (used by other parts of your code):
TreeNode **ft_return_main_treeNode(void);
void ft_cleanup_treeNode(void);

#endif

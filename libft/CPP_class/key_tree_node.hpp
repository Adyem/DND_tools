#ifndef KEY_TREE_NODE_HPP
#define KEY_TREE_NODE_HPP

#include "../Template/map.hpp"
#include "../Template/vector.hpp"

class KeyTreeNode
{
	public:
    	const char* skillName;
    	ft_map<const char*, const char*> attributes;
    	ft_vector<KeyTreeNode*> children;

    	KeyTreeNode(const char* name);
    	~KeyTreeNode();

    	void addChild(KeyTreeNode* child);
    	void setAttribute(const char* key, const char* value);
    	const char* getAttribute(const char* key) const;
};

#endif

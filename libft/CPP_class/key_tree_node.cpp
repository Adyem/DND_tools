#include "key_tree_node.hpp"

KeyTreeNode::KeyTreeNode(const char* name) : skillName(name)
{
	return ;
}

KeyTreeNode::~KeyTreeNode()
{
	return ;
}

void KeyTreeNode::addChild(KeyTreeNode* child)
{
    children.push_back(child);
	return ;
}

void KeyTreeNode::setAttribute(const char* key, const char* value)
{
    attributes.at(key) = value;
	return ;
}

const char* KeyTreeNode::getAttribute(const char* key) const
{
    if (this->attributes.find(key) != attributes.end())
        return attributes.at(key);
    return (nullptr);
}

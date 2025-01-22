#include "key_tree.hpp"
#include "nullptr.hpp"

KeyTree::KeyTree(const char* rootName)
{
    root = new KeyTreeNode(rootName);
	return ;
}

KeyTree::~KeyTree()
{
    deleteTree(root);
	return ;
}

KeyTreeNode* KeyTree::getRoot() const
{
    return (root);
}

KeyTreeNode* KeyTree::findSkillRecursive(KeyTreeNode* node, const char* skillName) const
{
	if (strcmp(node->skillName, skillName) == 0)
        return (node);
	size_t index = 0;
    while (index < node->children.size())
	{
        KeyTreeNode* result = findSkillRecursive(node->children[index], skillName);
        if (result != ft_nullptr)
            return (result);
		index++;
    }
    return (ft_nullptr);
}

KeyTreeNode* KeyTree::findSkill(const char* skillName) const
{
    if (root == ft_nullptr)
		return (ft_nullptr);
    return (findSkillRecursive(root, skillName));
}

void KeyTree::addSkill(const char* parentName, const char* skillName)
{
    KeyTreeNode* parent = findSkill(parentName);
    if (parent != ft_nullptr)
	{
        KeyTreeNode* newSkill = new KeyTreeNode(skillName);
        parent->addChild(newSkill);
    }
}

void KeyTree::deleteTree(KeyTreeNode* node)
{
    if (node)
	{
		size_t index = 0;
        while (index < node->children.size())
		{
            deleteTree(node->children[index]);
			index++;
		}
        delete (node);
    }
}

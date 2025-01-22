#ifndef KEY_TREE_HPP
#define KEY_TREE_HPP

#include "key_tree_node.hpp"
#include <cstring>

class KeyTree {
private:
    KeyTreeNode* root;

    KeyTreeNode* findSkillRecursive(KeyTreeNode* node, const char* skillName) const;
    void deleteTree(KeyTreeNode* node);

public:
    KeyTree(const char* rootName);
    ~KeyTree();

    KeyTreeNode* getRoot() const;
    KeyTreeNode* findSkill(const char* skillName) const;
    void addSkill(const char* parentName, const char* skillName);
};

#endif // KEY_TREE_HPP

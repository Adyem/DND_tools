#include <iostream>
#include <unordered_map>
#include <stdexcept>

class TreeNode {
public:
    std::unordered_map<char, TreeNode*> children; // Use raw pointers to child nodes
    int* result = nullptr; // Store the integer pointer if it's a leaf node

    ~TreeNode(); // Destructor to clean up memory
    void insert(const char* key, int* value);
    int* search(const char* key) const; // Updated to use const char* instead of std::string
};

// Destructor definition
TreeNode::~TreeNode() {
    for (auto& child : children) {
        delete child.second; // Explicitly delete child nodes
    }
}

// Insert function definition
void TreeNode::insert(const char* key, int* value) {
    // Validate the key
    size_t length = strlen(key);
    if (length == 0 || key[length - 1] != '=') {
        throw std::invalid_argument("Key must end with '='");
    }
    for (size_t i = 0; i < length - 1; ++i) {
        if (key[i] == '=') {
            throw std::invalid_argument("Key contains '=' in an invalid position");
        }
    }

    // Build the tree
    TreeNode* current = this;
    while (*key) {
        char ch = *key++;
        if (!current->children[ch]) {
            current->children[ch] = new TreeNode();
        }
        current = current->children[ch];
    }
    current->result = value; // Assign the final value
}

// Search function definition
int* TreeNode::search(const char* key) const {
    const TreeNode* current = this;
    while (*key) {
        auto it = current->children.find(*key);
        if (it == current->children.end()) {
            return nullptr; // Key not found
        }
        current = it->second;
        key++;
    }
    return current->result; // Return the integer pointer if found
}

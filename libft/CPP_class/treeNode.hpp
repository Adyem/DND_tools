#include <unordered_map>
#include <csignal>

class TreeNode {
public:
    std::unordered_map<char, TreeNode*> children;
    int		*result = nullptr;

    ~TreeNode();
    int		insert(const char* key, int* value);
    int		*search(const char* key) const;
};

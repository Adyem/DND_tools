#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "../CMA/CMA.hpp"

template <typename KeyType, typename ValueType>
class Map
{
private:
    struct Node
    {
        Pair<KeyType, ValueType> data;
        Node* left;
        Node* right;

        Node(const KeyType& key, const ValueType& value)
            : data{key, value}, left(nullptr), right(nullptr) {}
    };
	bool	critical;
	bool	error;
    Node	*root;

public:
    Map();
    ~Map();

    void insert(const KeyType& key, const ValueType& value);
    ValueType* find(const KeyType& key);
    void remove(const KeyType& key);
    bool empty() const;
    void clear();

private:
    void insert(Node*& node, const KeyType& key, const ValueType& value);
    ValueType* find(Node* node, const KeyType& key) const;
    void remove(Node*& node, const KeyType& key);
    void clear(Node* node);
};


template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map() : root(nullptr)
{
	return ;
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::~Map()
{
    clear();
	return ;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
    insert(root, key, value);
	return ;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(Node*& node, const KeyType& key, const ValueType& value)
{
	if (node == nullptr)
        node = new Node(key, value);
	else if (key < node->data.key)
        insert(node->left, key, value);
	else if (key > node->data.key)
        insert(node->right, key, value);
	else
    	node->data.value = value;
	return ;
}

template <typename KeyType, typename ValueType>
ValueType* Map<KeyType, ValueType>::find(const KeyType& key)
{
    return (find(root, key));
}

template <typename KeyType, typename ValueType>
ValueType* Map<KeyType, ValueType>::find(Node* node, const KeyType& key) const
{
	if (node == nullptr)
        return (nullptr);
	else if (key < node->data.key)
        return (find(node->left, key));
	else if (key > node->data.key)
        return (find(node->right, key));
	else
        return (&node->data.value);
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(const KeyType& key)
{
    remove(root, key);
	return ;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(Node*& node, const KeyType& key)
{
    if (node == nullptr)
        return ;
    if (key < node->data.key)
        remove(node->left, key);
    else if (key > node->data.key)
        remove(node->right, key);
    else
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr)
        {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            Node* successor = node->right;
            while (successor->left != nullptr)
                successor = successor->left;

            node->data = successor->data;
            remove(node->right, successor->data.key);
        }
    }
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::empty() const
{
    return (root == nullptr);
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::clear()
{
    clear(root);
    root = nullptr;
	return ;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::clear(Node* node)
{
    if (node != nullptr)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
	return ;
}

#endif

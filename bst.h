#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional> // std::less

template <typename K, typename V, typename Compare = std::less<K>>
class BST 
{
protected:
    struct Node 
    {
        K key;
        V value;
        Node* left;
        Node* right;

        Node(const K& k, const V& v)
            : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;
    Compare comp; // default less


//--------------------------------Utility-------------------------------------
    virtual Node* insertNode(Node* node, const K& key, const V& value)
    {
        if (!node) return new Node(key, value);

        if (comp(key, node->key)) 
        { // key < node->key
            node->left = insertNode(node->left, key, value);
        } 

        else if (comp(node->key, key)) 
        { 
            node->right = insertNode(node->right, key, value);
        } 

        else 
        {
            node->value = value; // overwrite value
        }

        return node;
    }

    virtual Node* eraseNode(Node* node, const K& key)
    {
        if (!node) return nullptr;

        if (comp(key, node->key)) 
        {
            node->left = eraseNode(node->left, key);
        } 

        else if (comp(node->key, key))
        {
            node->right = eraseNode(node->right, key);
        }

        else 
        {
            // Found node
            if (!node->left && !node->right) 
            {
                delete node;
                return nullptr;
            } 

            else if (!node->left) 
            {
                Node* temp = node->right;
                delete node;
                return temp;
            } 

            else if (!node->right) 
            {
                Node* temp = node->left;
                delete node;
                return temp;
            } 

            else 
            {
                Node* minNode = findMin(node->right);
                node->key = minNode->key;
                node->value = minNode->value;
                node->right = eraseNode(node->right, minNode->key);
            }
        }

        return node;
    }

    Node* findNode(Node* node, const K& key) const
    {
        if (!node) return nullptr;

        if (!comp(key, node->key) && !comp(node->key, key)) // key == node->key
            return node;

        if (comp(key, node->key))
            return findNode(node->left, key);

        return findNode(node->right, key);
    }

//--------------------------------Support-------------------------------------
    Node* findMin(Node* node) const
    {
        while (node && node->left)
            node = node->left;

        return node;
    }

    void inorderPrint(Node* node) const
    {
        if (!node) return;

        inorderPrint(node->left);
        std::cout << "(" << node->key << "," << node->value << ") ";
        inorderPrint(node->right);
    }

    void clear(Node* node)
    {
        if (!node) return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

public:
    BST() : root(nullptr), comp(Compare()) {}
    explicit BST(Compare cmp) : root(nullptr), comp(cmp) {}
    virtual ~BST() { clear(root); }

// ---------------------------Public wrappers -----------------------------
    virtual void insert(const K& key, const V& value)
    {
        root = insertNode(root, key, value);
    }

    virtual void erase(const K& key)
    {
        root = eraseNode(root, key);
    }

    bool find(const K& key, V& outValue) const
    {
        Node* res = findNode(root, key);

        if (res) 
        {
            outValue = res->value;
            return true;
        }
        
        return false;
    }

    virtual void inorder() const
    {
        inorderPrint(root);
        std::cout << "\n";
    }

    void clear() 
    {
        clear(root);
        root = nullptr;
    }
};

#endif

#ifndef AVL_H
#define AVL_H

#include "bst.h"
#include <algorithm> // std::max


template <typename K, typename V, typename Compare = std::less<K>>
class AVL : public BST<K, V, Compare> 
{

private:
    using Base = BST<K, V, Compare>;
    using Node = typename Base::Node;
    using Base::root;
    using Base::findMin;
    using Base::comp; 

    struct AVLNode : public Node 
    {
        int height;
        AVLNode(const K& k, const V& v) : Node(k, v), height(1) {}
    };

//-------------------------------Support-----------------------------------------
    int getHeight(Node* n) { return n ? static_cast<AVLNode*>(n)->height : 0; }

    int getBalance(Node* n) // 0, 1, -1: balance ; >1: left-heavy, <-1: right-heavy
    {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    Node* rotateRight(Node* y) 
    {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        auto ay = static_cast<AVLNode*>(y);
        auto ax = static_cast<AVLNode*>(x);

        ay->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        ax->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) 
    {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        auto ax = static_cast<AVLNode*>(x);
        auto ay = static_cast<AVLNode*>(y);

        ax->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        ay->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

protected:
//--------------------------------Utility-----------------------------------------
    Node* insertNode(Node* node, const K& key, const V& value) override 
    {
    //--------------------------insert----------------------------
        if (!node) return new AVLNode(key, value);

        if (comp(key, node->key)) // key < node->key
            node->left = insertNode(node->left, key, value);

        else if (comp(node->key, key)) // key > node->key
            node->right = insertNode(node->right, key, value);

        else 
        {
            node->value = value; // update value if equal
            return node;
        }

    //--------------------------update height----------------------------
        
        auto n = static_cast<AVLNode*>(node);
        n->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

    //------------------------re balance------------------------------
        
        if (balance > 1 && comp(key, node->left->key)) // LL
            return rotateRight(node);

        if (balance < -1 && comp(node->right->key, key)) // RR
            return rotateLeft(node);

        if (balance > 1 && comp(node->left->key, key)) // LR
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && comp(key, node->right->key))  // RL
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* eraseNode(Node* node, const K& key) override 
    {
    //-----------------------remove------------------------------
        if (!node) return nullptr;

        if (comp(key, node->key))
            node->left = eraseNode(node->left, key);

        else if (comp(node->key, key))
            node->right = eraseNode(node->right, key);

        else 
        {
            // Delete like BST
            if (!node->left || !node->right)    // 0 or 1 child
            {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } 

            else // 2 child
            {
                Node* minNode = findMin(node->right);   //successor
                node->key = minNode->key;
                node->value = minNode->value;
                node->right = eraseNode(node->right, minNode->key);
            }
        }

        if (!node) return nullptr;

    //-----------------------update height------------------------------
        
        auto n = static_cast<AVLNode*>(node);
        n->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

    //----------------------re balance------------------------------
        
        if (balance > 1 && getBalance(node->left) >= 0) // LL
            return rotateRight(node);

        if (balance > 1 && getBalance(node->left) < 0) // LR
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
     
        if (balance < -1 && getBalance(node->right) <= 0)  // RR
            return rotateLeft(node);

        if (balance < -1 && getBalance(node->right) > 0) // RL
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

public:
    AVL() = default;
    explicit AVL(Compare cmp) { this->comp = cmp; }
};

#endif

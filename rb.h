#ifndef RB_H
#define RB_H

#include "bst.h"
#include <functional>

template <typename K, typename V, typename Compare = std::less<K>>
class RBTree : public BST<K, V, Compare> 
{
private:
    using Base = BST<K, V, Compare>;
    using typename Base::Node;
    using Base::root;
    using Base::comp;

    enum Color { RED, BLACK };

    struct RBNode : Node 
    {
        Color color;
        RBNode* parent;

        RBNode(const K& k, const V& v, Color c = RED)
            : Node(k, v), color(c), parent(nullptr) {}
    };

//---------------------------------Support----------------------------------------------------
    
    // helper cast (null safe)
    RBNode* toRB(Node* n) const { return n ? static_cast<RBNode*>(n) : nullptr; }

    RBNode* rotateLeft(RBNode* x) 
    {
        if (!x || !x->right) return x;

        RBNode* y = toRB(x->right);
        x->right = y->left;

        if (y->left) toRB(y->left)->parent = x;

        y->parent = x->parent;

        if (!x->parent) root = y;

        else if (x == toRB(x->parent)->left)
            toRB(x->parent)->left = y;

        else
            toRB(x->parent)->right = y;

        y->left = x;
        x->parent = y;

        return y;
    }

    RBNode* rotateRight(RBNode* x) 
    {
        if (!x || !x->left) return x;

        RBNode* y = toRB(x->left);
        x->left = y->right;
        if (y->right) toRB(y->right)->parent = x;

        y->parent = x->parent;

        if (!x->parent) root = y;

        else if (x == toRB(x->parent)->right)
            toRB(x->parent)->right = y;

        else
            toRB(x->parent)->left = y;

        y->right = x;
        x->parent = y;

        return y;
    }

    void replaceNode(RBNode* u, RBNode* v) 
    {
        if (!u->parent) root = v;   // u is root

        else if (u == toRB(u->parent)->left)    // u is left child
            toRB(u->parent)->left = v;

        else
            toRB(u->parent)->right = v;

        if (v) v->parent = u->parent;
    }

    void inorderPrintColor(RBNode* node) const 
    {
        if (!node) return;
        inorderPrintColor(toRB(node->left));

        std::cout << "(" << node->key << "," << node->value << "," 
                  << (node->color == RED ? "R" : "B") << ") ";

        inorderPrintColor(toRB(node->right));
    }

// ---------------------------- Fix violations ---------------------------------------------
    void fixInsert(RBNode* node) 
    {
        while (node && node != toRB(root) && toRB(node->parent) && toRB(node->parent)->color == RED) 
        {
            // parent is red -> violation
            RBNode* parent = toRB(node->parent);
            RBNode* grand = toRB(parent->parent);

            if (!grand) break;

            if (parent == grand->left)  // parent is left child
            {
                RBNode* uncle = toRB(grand->right);

                // Case 1: uncle red -> recolor
                if (uncle && uncle->color == RED) 
                {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grand->color = RED;
                    node = grand;
                } 
                else 
                {
                    // Case 2: node is right child -> rotate left
                    if (node == parent->right) 
                    {
                        node = parent;
                        rotateLeft(node);
                        parent = toRB(node->parent);    // update
                        grand = toRB(parent ? parent->parent : nullptr);
                    }

                    // Case 3: node is left child ->rotate right
                    parent->color = BLACK;
                    if (grand) 
                    {
                        grand->color = RED;
                        rotateRight(grand);
                    }
                }
            } 
            else    // Mirror case 
            {
                RBNode* uncle = toRB(grand->left);
                
                // Case 1: uncle red -> recolor
                if (uncle && uncle->color == RED) 
                {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grand->color = RED;
                    node = grand;
                } 

                else 
                {
                    //Case 2: node is left child -> rotate right
                    if (node == parent->left) 
                    {
                        node = parent;
                        rotateRight(node);
                        parent = toRB(node->parent);
                        grand = toRB(parent ? parent->parent : nullptr);
                    }

                    //Case 3: node is right child -> rotate left
                    parent->color = BLACK;
                    if (grand) 
                    {
                        grand->color = RED;
                        rotateLeft(grand);
                    }
                }
            }
        }
        if (root) toRB(root)->color = BLACK;
    }

    void fixDelete(RBNode* x, RBNode* parent) 
    {
        while ((x != toRB(root)) && (!x || x->color == BLACK)) // x is black
        {
            if (!parent) break;

            if (x == toRB(parent->left))    // x is left child
            {
                RBNode* sibling = toRB(parent->right);

                //Case1 : sibling red
                if (sibling && sibling->color == RED) 
                {
                    sibling->color = BLACK;
                    parent->color = RED;
                    rotateLeft(parent);
                    sibling = toRB(parent->right);
                }

                //Case 2: sibling black, both child black
                if ((!sibling || (!sibling->left || toRB(sibling->left)->color == BLACK))
                    && (!sibling || (!sibling->right || toRB(sibling->right)->color == BLACK))) 
                {
                    if (sibling) sibling->color = RED;

                    x = parent;
                    parent = toRB(x->parent);
                } 

                else 
                {
                    //Case 3 & 4: sibling black, at least one red child
                    if (!sibling->right || toRB(sibling->right)->color == BLACK) 
                    {
                        if (sibling->left) toRB(sibling->left)->color = BLACK;
                        
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = toRB(parent->right);
                    }

                    //Case 4
                    if (sibling) 
                    {
                        sibling->color = parent->color;
                        parent->color = BLACK;

                        //Make sure sibling's right child is black
                        if (sibling->right) 
                            toRB(sibling->right)->color = BLACK;
                    }

                    rotateLeft(parent);
                    x = toRB(root);
                    parent = toRB(x ? x->parent : nullptr);
                }
            } 
            else 
            {
                // x is right child
                RBNode* sibling = toRB(parent->left);

                //Case 1: sibling red 
                if (sibling && sibling->color == RED) 
                {
                    sibling->color = BLACK;
                    parent->color = RED;

                    rotateRight(parent);
                    sibling = toRB(parent->left);
                }

                //Case 2: sibling black, both chid black
                if ((!sibling || (!sibling->right || toRB(sibling->right)->color == BLACK))
                    && (!sibling || (!sibling->left || toRB(sibling->left)->color == BLACK))) 
                {
                    if (sibling) sibling->color = RED;
                    
                    x = parent;
                    parent = toRB(x->parent);
                } 

                else 
                {
                    //Case 3 & 4: sibling black, at least one red child
                    if (!sibling->left || toRB(sibling->left)->color == BLACK) 
                    {
                        if (sibling->right) toRB(sibling->right)->color = BLACK;
                        sibling->color = RED;
                        
                        rotateLeft(sibling);
                        sibling = toRB(parent->left);
                    }

                    //Case 4
                    if (sibling) 
                    {
                        sibling->color = parent->color;
                        parent->color = BLACK;

                        //Make sure sibling's left child is black
                        if (sibling->left) 
                            toRB(sibling->left)->color = BLACK;
                    }

                    rotateRight(parent);
                    x = toRB(root);
                    parent = toRB(x ? x->parent : nullptr);
                }
            }
        }
        if (x) x->color = BLACK;
    }

protected:
    Node* insertNode(Node* node, const K& key, const V& value) override 
    {
        RBNode* parent = nullptr;
        RBNode* curr = toRB(node);

        while (curr) 
        {
            parent = curr;
            if (comp(key, curr->key))
                curr = toRB(curr->left);

            else if (comp(curr->key, key))
                curr = toRB(curr->right);

            else 
            {
                curr->value = value;
                return node;
            }
        }

        RBNode* newNode = new RBNode(key, value);
        newNode->parent = parent;

        if (!parent) root = newNode;

        else if (comp(key, parent->key)) parent->left = newNode;

        else parent->right = newNode;

        fixInsert(newNode);
        return root;
    }

    Node* eraseNode(Node* node, const K& key) override 
    {
        // z : node to be deleted
        RBNode* z = toRB(this->findNode(root, key));
        if (!z) return root;

        RBNode* y = z;
        RBNode* x = nullptr;
        RBNode* xParent = nullptr;
        Color originalColor = y->color;

        if (!z->left)   // z has 0 or 1 child
        {
            x = toRB(z->right);
            xParent = toRB(z->parent);
            replaceNode(z, toRB(z->right));
        } 

        else if (!z->right) // z has 1 child
        {
            x = toRB(z->left);
            xParent = toRB(z->parent);
            replaceNode(z, toRB(z->left));
        } 

        else 
        {
            // z has 2 child
            y = toRB(this->findMin(z->right));
            originalColor = y->color;
            x = toRB(y->right);

            if (y->parent == z) xParent = y;

            else 
            {
                // y is not direct child of z
                replaceNode(y, toRB(y->right));
                y->right = z->right;
                if (y->right) toRB(y->right)->parent = y;
                xParent = toRB(y->parent);
            }

            replaceNode(z, y);
            y->left = z->left;

            if (y->left) toRB(y->left)->parent = y;
            y->color = z->color;
        }

        delete z;

        if (originalColor == BLACK) fixDelete(x, xParent);
        
        return root;
    }

public:
    RBTree() = default;

    void inorder() const override 
    {
        inorderPrintColor(toRB(root));
        std::cout << "\n";
    }
};

#endif

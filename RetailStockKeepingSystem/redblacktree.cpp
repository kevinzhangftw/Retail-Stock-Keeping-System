// File:        redblacktree.cpp
// Author:      Ina Vukmirovich
// Date:        2016-03-14
// Description: Contains implementation of RedBlackTree functions

#ifdef _REDBLACKTREE_H_

#include <math.h>

/*
 
 class Node
 {
 public:
 T data;
 Node<T>* left;
 Node<T>* right;
 Node<T>* p;     // parent pointer
 bool is_black;
 
 // parameterized constructor
 Node(T value)
 {
 data = value;
 left = NULL;
 right = NULL;
 p = NULL;
 is_black = false;
 }
 };
 
 Node<T>* root;
 int size;
 */


// recursive helper function for deep copy
// creates a new node based on sourcenode's contents, links back to parentnode,
//   and recurses to create left and right children
template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode)
{
    Node<T>* newnode = new Node<T>(sourcenode->data);
    newnode->p = parentnode;
    newnode->is_black = sourcenode->is_black;
    if (!parentnode) {
        root = newnode;
    }
    else if (sourcenode == sourcenode->p->left)
    {
        parentnode->left = newnode;
    }
    else
    {
        parentnode->right = newnode;
    }
    
    if (sourcenode->left != NULL) {
        CopyTree(sourcenode->left, newnode);
    }
    if (sourcenode->right != NULL) {
        CopyTree(sourcenode->right, newnode);
    }
    return newnode;
}

// recursive helper function for tree deletion
// deallocates nodes in post-order
template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
    if (!node) return;
    // recurse on left child
    RemoveAll(node->left);
    
    // recurse on right child
    RemoveAll(node->right);
    
    // visit current node
    delete node;
    return;
    
}

// Tree fix, performed after removal of a black node
// Note that the parameter x may be NULL
template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
    Node<T>* y;
    while (x != root and (!x or x->is_black) )
        if (xisleftchild) // x is left child
        {
            y = xparent->right; // x’s sibling
            if (y and y->is_black == false)
            {
                y->is_black = true;
                xparent->is_black = false; // p was black
                LeftRotate(xparent);
                y = xparent->right;
            }
            if ((!y->left or y->left->is_black == true) and (!y->right or y->right->is_black == true))
            {
                y->is_black = false;
                x = xparent;
            }
            else
            {
                if (!y or y->right->is_black == true)
                {
                    y->left->is_black = true;
                    y->is_black = false;
                    RightRotate(y);
                    y = xparent->right;
                }
                y->is_black = xparent->is_black;
                xparent->is_black = true;
                y->right->is_black = true;
                LeftRotate(xparent);
                x = root;
            }
        }
        else // x is right child
        {
            if (y->is_black == false)
            {
                y->is_black = true;
                xparent->is_black = false; // p was black
                RightRotate(xparent);
                y = xparent->left;
            }
            if (y->right->is_black == true and y->left->is_black == true)
            {
                y->is_black = false;
                x = xparent;
            }
            else
            {
                
                if (y->left->is_black == true)
                {
                    y->right->is_black = true;
                    y->is_black = false;
                    LeftRotate(y);
                    y = xparent->left;
                }
                y->is_black = xparent->is_black;
                xparent->is_black = true;
                y->left->is_black = true;
                RightRotate(xparent);
                x = root;
            }
        }
    x->is_black = true;
    return;
}

// Calculates the height of the tree
// Requires a traversal of the tree, O(n)
template <class T>
int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
    if (node != NULL)
    {
        // recurse on left child
        int h1 = CalculateHeight(node->left);
        int h2 = CalculateHeight(node->right);
        if (h1 >= 2)
        {
            return h1 + 1;
        }
        else return h2 + 1;
    }
    else return 0;
}

// default constructor
template <class T>
RedBlackTree<T>::RedBlackTree() : root(NULL), size(0)
{
    return;
}

// copy constructor, performs deep copy of parameter
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
    CopyTree(rbtree.root, NULL);
    size = rbtree.size;
}

// destructor
// Must deallocate memory associated with all nodes in tree
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
    RemoveAll();
    root = NULL;
}

// overloaded assignment operator
template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
{
    if (this != &rbtree)
    {
        this->root = rbtree.root;
        this->size = rbtree.size;
    }
    return *this;
}

// Accessor functions

// Calls BSTInsert and then performs any necessary tree fixing.
// If item already exists, do not insert and return false.
// Otherwise, insert, increment size, and return true.
template <class T>
bool RedBlackTree<T>::Insert(T item)
{
    if (root != NULL and Search(item) == true) return false;
    Node<T>* x = BSTInsert(item);
    x->is_black = false;
    while (x != root and x->p->is_black == false)
        if(x->p == x->p->p->left)  // parent is left child
        {
            Node<T>* y = x->p->p->right;    // uncle of x
            if (y!=NULL and y->is_black == false)       // uncle and parent both red
            {
                x->p->is_black = true;      // colour them black
                y->is_black = true;
                x->p->p->is_black = false;  // grandparent to red
                x = x->p->p;                // move x up the tree
            }
            
            else // uncle is black
            {
                if (x == x->p->right)       // rotate if x is right child
                {
                    x = x->p;
                    LeftRotate(x);
                }
                x->p->is_black = true;        // colour parent black
                x->p->p->is_black = false;    // colour grandparent red
                RightRotate(x->p->p);        // rotate grandparent
            }
        }
        else // parent is right child
        {
            Node<T>* y = x->p->p->left;
            if(y!=NULL and y->is_black == false)
            {
                x->p->is_black = true;
                y->is_black = true;
                x->p->p->is_black = false;
                x = x->p->p;
            }
            else
            {
                if(x == x->p->left)
                {
                    x = x->p;
                    RightRotate(x);
                }
                x->p->is_black = true;
                x->p->p->is_black = false;
                LeftRotate(x->p->p);
            }
        }
    root->is_black = true;
    size++;
    return true;
}

// Removal of an item from the tree.
// Must deallocate deleted node after RBDeleteFixUp returns
template <class T>
bool RedBlackTree<T>::Remove(T item)
{
    Node<T>* y;
    Node<T>* x;
    Node<T>* z = root;
    bool xIsLeft;
    
    // find item (z) in tree
    while (z != NULL)
    {
        if (item == z->data)
        {
            break;
        }
        else if (item < z->data)
            z = z->left;
        else
            z = z->right;
    }
    if (z == NULL) return false;                // item not in tree
    
    // z has zero or one child
    if (z->left == NULL or z->right == NULL)
    {
        y = z;
    }
    // z has two children
    else
    {
        y = Predecessor(z);
    }
    
    // check if y's child is left or right, x = child
    if (y->left != NULL) {
        x = y->left;
    }
    else
    {
        x = y->right;
    }
    if (x) {
        x->p = y->p;            // detach x from y
    }
    
    if (y->p == NULL) {     // if y is root, make x the root
        this->root = x;
    }
    else {                  // attach x to y's parent
        if (y == y->p->left) {
            y->p->left = x;
            xIsLeft = true;
        }
        else {
            y->p->right = x;
            xIsLeft = false;
        }
    }
    
    if (y != z) {       // if y has moved up
        z->data = y->data;   // replace z with y
    }
    if (y->is_black == true) {
        RBDeleteFixUp(x, y->p, xIsLeft);
    }
    size--;
    return true;
}

// deletes all nodes in the tree. Calls recursive helper function.
template <class T>
void RedBlackTree<T>::RemoveAll()
{
    if (size != 0) RemoveAll(root);
    size = 0;
}

// returns the number of items in the tree
template <class T>
int RedBlackTree<T>::Size() const
{
    return this->size;
}

// returns the height of the tree, from root to deepest null child. Calls recursive helper function.
// Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
template <class T>
int RedBlackTree<T>::Height() const
{
    return CalculateHeight(root);
}

#endif
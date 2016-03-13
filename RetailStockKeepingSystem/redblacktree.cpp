//
//  redblacktree.cpp
//  RetailStockKeepingSystem
//
//  Created by Kevin Zhang on 2016-02-29.
//  Copyright © 2016 Kevin Zhang. All rights reserved.
//

#ifdef _REDBLACKTREE_H_
// recursive helper function for deep copy
// creates a new node "thisnode" based on sourcenode's contents, links back to parentnode,
//   and recurses to create left and right children
template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode){
    //:TODO
    
}

// recursive helper function for tree deletion
// deallocates nodes in post-order
template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node){
    if (node!= NULL) {
        RemoveAll(node->left);
        RemoveAll(node->right);
        delete node;
    }
}

// Tree fix, performed after removal of a black node
// Note that the parameter x may be NULL
template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild){
    //:TODO
}

// Calculates the height of the tree
// Requires a traversal of the tree, O(n)
template <class T>
int RedBlackTree<T>::CalculateHeight(Node<T>* node) const{
   //:TODO
}

// default constructor
template <class T>
RedBlackTree<T>::RedBlackTree(){
    root = NULL;
    size = 0;
}

// copy constructor, performs deep copy of parameter
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree){
    //:TODO
    //copytree helper func used here
    root = NULL;
    size = 0;
    
}

// destructor
// Must deallocate memory associated with all nodes in tree
template <class T>
RedBlackTree<T>::~RedBlackTree(){
 //:TODO
//RemoveAll();
}

// overloaded assignment operator
template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree){
    //:TODO
    return *this;
}



// Accessor functions

// Calls BSTInsert and then performs any necessary tree fixing.
template <class T>
void RedBlackTree<T>::InsertFix(Node<T> *node){
    Node<T> *root = GetRoot();
    if (root != NULL) {
        root->is_black = true; //property 2
    }
    insert_case1(node);
    
    
    verify_properties(node);
    
    
}
template <class T>
void RedBlackTree<T>::insert_case1(Node<T> *node) {
    if (node->p == NULL){
        node->is_black = true;
    } else {
        insert_case2(node);
    }
}

template <class T>
void RedBlackTree<T>::insert_case2(Node<T> *node) {
    if (node->p->is_black) {
        return;
    } else {
        insert_case3(node);
    }
}

template <class T>
Node<T>* RedBlackTree<T>::uncle(Node<T> *node) {
    assert (node != NULL);
    assert (node->p != NULL);
    assert (node->p->p != NULL);
    return sibling(node->p);
}

template <class T>
Node<T>* RedBlackTree<T>::grandparent(Node<T> *node) {
    assert (node != NULL);
    assert (node->p != NULL);
    assert (node->p->p != NULL);
    return node->p->p;
}
template <class T>
Node<T>* RedBlackTree<T>::sibling(Node<T> *node) {
    assert (node != NULL);
    assert (node->p != NULL);
    if (node == node->p->left)
        return node->p->right;
    else
        return node->p->left;
}

template <class T>
void RedBlackTree<T>::insert_case3(Node<T> *node) {
    //Node<T> *uncle = uncle(node);
    if (uncle(node) != NULL && !uncle(node)->is_black) {
        node->p->is_black = true;
        uncle(node)->is_black = true;
        grandparent(node)->is_black = false;
        insert_case1(grandparent(node));
    } else {
        insert_case4(node);
    }
}
template <class T>
void RedBlackTree<T>::insert_case4(Node<T> *node) {
    if (node == node->p->right &&
        node->p == grandparent(node)->left) {
        LeftRotate(node->p);
        node = node->left;
    } else if (node == node->p->left &&
               node->p == grandparent(node)->right) {
        RightRotate(node->p);
        node = node->right;
    }
    insert_case5(node);
}

template <class T>
void RedBlackTree<T>::insert_case5(Node<T> *node) {
    node->p->is_black = true;
    grandparent(node)->is_black = false;
    if (node == node->p->left && node->p == grandparent(node)->left)
    {
        RightRotate(grandparent(node));
    }
    else
    {
        assert (node == node->p->right && node->p == grandparent(node)->right);
        LeftRotate(grandparent(node));
    }
}

template <class T>
void RedBlackTree<T>::verify_properties(Node<T> *node) {
    verify_property_4(node);
}



template <class T>
void RedBlackTree<T>::verify_property_4(Node<T> * node){
    //If a node is red, then both its children are black.
    if (node == NULL) { return; }

    if (!node->is_black) {
        if (node->left != NULL) {
            assert(node->left->is_black);
        }
        if (node->right != NULL) {
            assert(node->right->is_black);
        }
        assert(node->p->is_black);
    }

    
    verify_property_4(node->left);
    verify_property_4(node->right);
}

template <class T>
bool RedBlackTree<T>::Insert(T item){
    
    if (Search(item)) {
        // If item already exists, do not insert and return false.
        return false;
    } else {
        // Otherwise, insert, increment size, and return true.
        
        InsertFix(BSTInsert(item));
        size++;
        return true;
    }
    
    return false;
}


// Removal of an item from the tree.
// Must deallocate deleted node after RBDeleteFixUp returns
template <class T>
bool RedBlackTree<T>::Remove(T item){
    //:TODO
    
    return false;
}


// deletes all nodes in the tree. Calls recursive helper function.
template <class T>
void RedBlackTree<T>::RemoveAll(){
    RemoveAll(root);
}

// returns the number of items in the tree
template <class T>
int RedBlackTree<T>::Size() const{
    return size;
}

// returns the height of the tree, from root to deepest null child. Calls recursive helper function.
// Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
template <class T>
int RedBlackTree<T>::Height() const{
    //:TODO
    return 0;
}
#endif
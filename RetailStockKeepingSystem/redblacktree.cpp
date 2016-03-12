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
// If item already exists, do not insert and return false.
// Otherwise, insert, increment size, and return true.
template <class T>
bool RedBlackTree<T>::Insert(T item){
    
    BSTInsert(item);
    //:TODO
    
    
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
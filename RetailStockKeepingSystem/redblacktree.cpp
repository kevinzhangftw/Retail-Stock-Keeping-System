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
    Node<T>* y = NULL;
    while (x != root && x->is_black == true) {
        if (xisleftchild == true) {
            y = x->p->right; //y must be x's sibling
            if (y->is_black == false) {
                y->is_black = true;
                x->p->is_black = false; //x' parent must be black since y is red
                LeftRotate(x->p);
                y = x->p->right; //black height unchanged but x sibling is now black
            }
            if (y->left->is_black == true && y->right->is_black == true) {
                y->is_black = false;
                x = x->p;
            }else{
                if (y->right->is_black == true) {
                    y->left->is_black = true;
                    y->is_black = false;
                    RightRotate(y);
                    y=x->p->right;
                }
                y->is_black = x->p->is_black;
                x->p->is_black = true;
                y->right->is_black = true;
                LeftRotate(x->p);
                x = root;
            }
        }else{
            //TODO
            y = x->p->left; //y must be x's sibling
            if (y->is_black == false) {
                y->is_black = true;
                x->p->is_black = false; //x' parent must be black since y is red
                RightRotate(x->p);
                y = x->p->right; //black height unchanged but x sibling is now black
            }
            if (y->left->is_black == true && y->right->is_black == true) {
                y->is_black = false;
                x = x->p;
            }else{
                if (y->right->is_black == true) {
                    y->left->is_black = true;
                    y->is_black = false;
                    RightRotate(y);
                    y=x->p->left;
                }
                y->is_black = x->p->is_black;
                x->p->is_black = true;
                y->right->is_black = true;
                RightRotate(x->p);
                x = root;
            }
        }
    }
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
// If item already exists, do not insert and return false.
// Otherwise, insert, increment size, and return true.
template <class T>
bool RedBlackTree<T>::Insert(T item){
    Node<T>* x = BSTInsert(item);
    size++;
    x->is_black = false; //first thing i do is color this red
    while (x!=root && x->p->is_black == false) { //traverse up the tree till we have a black p
        if (x->p == x->p->p->left) { //x's parent is grandparent's left child
            Node<T>* y = x->p->p->right; //init y to be the sibling of x's p
            if (y->is_black == false) { //and x->p is red we have matching reds
                y->is_black = true; //y to black
                x->p->is_black = true; //x.p to black
                x->p->p->is_black = false; // grand parent to red
                x=x->p->p; //move x upwards
            }else{ //y->isblack, but x.p is red then we have two cases to consider
                if (x == x->p->right) { //this means x is x.p's right child
                    x= x->p;
                    LeftRotate(x); //we preform left rotation to bring x inline w/ x.p and x.p.p
                }
                //once we are in line, we can preform right rotate to balance the tree
                x->p->is_black = true; //x is red, x.p is black
                x->p->p->is_black = false; //x.p is black , so x.p.p should be red
                RightRotate(x->p->p);
            }
        }else{ //now we handle the symmetric side
            Node<T>* y = x->p->p->left;
            if (y->is_black == false) {
                y->is_black = true;
                x->p->is_black = true; //x.p to black
                x->p->p->is_black = false; // grand parent to red
                x=x->p->p;
            }else{ // y and x.p have different color
                if (x==x->p->left) { // x not in line with x.p and x.p.p
                    x= x->p;
                    RightRotate(x);
                }
                x->p->is_black = true; //x is red, x.p is black
                x->p->p->is_black = false; //x.p is black , so x.p.p should be red
                LeftRotate(x->p->p);
            }
        }
    }
    
    return false;
}

// Removal of an item from the tree.
// Must deallocate deleted node after RBDeleteFixUp returns
template <class T>
bool RedBlackTree<T>::Remove(T item){
    //:TODO
    //first we need to track the node
    if (Search(item)) {
        Node<T>* node = root;
        Node<T>* x = NULL;
        Node<T>* y = NULL;
        Node<T>* z = NULL;
        while (node != NULL){
            if (item == node->data)
                z = node; //ok we found this node , time for magic to happen
            else if (item < node->data)
                node = node->left; //traverse left
            else
                node = node->right; //traverse right
        }
        //fun begins here
        if (z->left==NULL || z->right==NULL) { //z has one child or z has no child
            y= z; //instead of delete z we will copy over the data and delete y
        }else{ //z has two children
            y=Predecessor(z);
        }
        
        if (y->left != NULL) { //in this case we only check if y's one child is left or right
            x = y->left; //because y is predessor , y must not have right child
        }else{
            x = y->right; // if z only has one child and it is right one
        }
        
        x->p = y->p; //attach x upwards
        
        if (y->p == NULL) { //if y has no parents, then root should be x
            root = x;
        }else{
            if (y == y->p->left) {
                y->p->left = x;
            }else{
                y->p->right = x;
            }//attach x downwards from y
        }
        
        if (y != z) {
            z->data = y->data;
        }//this happens when y is predessor of z
        //if y is red then no problemo
        if (y->is_black == true) { //but y is black the bh property si voilated
            RBDeleteFixUp(x, y->p, true);
        }
        
        delete y;
        size--;
        return true;
    }else{
        return false; //cant do anything if we cant find the node to delete
    }
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
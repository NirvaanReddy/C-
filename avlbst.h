#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
  
    virtual void rotateLeft(AVLNode<Key,Value>* const current_node);
    virtual void rotateRight(AVLNode<Key,Value>* const current_node);
  
    virtual void incHeight(AVLNode <Key, Value>* current_node, bool b);
    virtual void decHeight(AVLNode <Key, Value>* current_node, bool b);

    virtual void incbal(AVLNode <Key, Value>* current_node, bool b);
    virtual void decbal(AVLNode <Key, Value>* current_node, bool b);



    static bool isLeftChild(AVLNode<Key,Value>* ch);
    // Add helper functions here


};
template<class Key, class Value>
void AVLTree<Key,Value>::incbal(AVLNode<Key, Value>* current_node, bool b)
{
    if (b) {
        current_node -> setBalance(0);
    } 
    else {
        current_node -> setBalance(1);
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::decbal(AVLNode<Key, Value>* current_node, bool b)
{
    AVLNode<Key, Value> * const parent_node = current_node -> getParent();
    if (b) {
        switch (current_node -> getLeft() -> getBalance()) {
            case -1:
                if (parent_node != nullptr) {
                    decHeight(parent_node, isLeftChild(current_node -> getParent()));
                }
                return;
            case 1:
                if (parent_node != nullptr) {
                    decHeight(parent_node, isLeftChild(current_node -> getParent()));
                }
                return;
            case 0:
                return;
        }
    } 
    else {
        switch (current_node -> getRight() -> getBalance()) {
            case 1:
                if (parent_node != nullptr) {
                    decHeight(parent_node, isLeftChild(current_node -> getParent()));
                }
                return;
            case -1:
                if (parent_node != nullptr) {
                    decHeight(parent_node, isLeftChild(current_node -> getParent()));
                }
                return;
            case 0:
                return;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::incHeight(AVLNode <Key, Value>* current_node, bool b){
    if (b) {
        current_node -> updateBalance(-1);
    } 
    else {
        current_node -> updateBalance(1);
    }
    switch (current_node -> getBalance()) {
        case 0:
            return;
        case 1:
            if (current_node -> getParent() != nullptr) {
                incHeight(current_node -> getParent(), isLeftChild(current_node));
            }
            return;
        case -1:
            if (current_node -> getParent() != nullptr) {
                incHeight(current_node -> getParent(), isLeftChild(current_node));
            }
            return;
        case -2:
            incbal(current_node, true);
            return;
        case 2:
            incbal(current_node, false);
            return;
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::decHeight(AVLNode <Key, Value>* current_node, bool b){
    if (b == true) {
        current_node -> updateBalance(1);
    } else {
        current_node -> updateBalance(-1);
    }
    switch (current_node -> getBalance()) {
        case 0:
            if (current_node -> getParent() != nullptr) {
                decHeight(current_node -> getParent(), isLeftChild(current_node));
            }
            return;
        case 1:
            return;
        case -1:
            return;
        case -2:
            decbal(current_node, true);
            return;
        case 2:
            decbal(current_node, false);
            return;
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* current_node){
    AVLNode<Key,Value>* parent = current_node -> getParent();
    AVLNode<Key,Value>* newTop = current_node -> getLeft();
    
    current_node -> setLeft(newTop -> getRight());
    
    if (current_node -> getLeft() != nullptr) {
        current_node -> getLeft() -> setParent(current_node);
    }
    
    newTop ->setRight(current_node);
    current_node -> setParent(newTop);
    
    newTop->setParent(parent);
    if (parent != NULL) {
        if (parent -> getRight() == current_node) {
            parent ->setRight(newTop);
        } 
        else {
            parent -> setLeft(newTop);
        }
    } 
    else {
       this -> root_ = newTop;
    }
}


template <class Key, class Value>
bool AVLTree<Key,Value>::isLeftChild(AVLNode<Key,Value>* ch){
    return ch -> getParent() -> getLeft() == ch;
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value>* current_node){
    AVLNode<Key,Value>* parent = current_node -> getParent();
    AVLNode<Key,Value>* newTop = current_node -> getRight();
    
    current_node -> setRight(newTop -> getLeft());
    
    if (current_node -> getRight() != nullptr) {
        current_node -> getRight() -> setParent(current_node);
    }
    
    newTop ->setLeft(current_node);
    current_node -> setParent(newTop);
    
    newTop->setParent(parent);
    if (parent != NULL) {
        if (parent -> getLeft() == current_node) {
            parent ->setLeft(newTop);
        } 
        else {
            parent -> setRight(newTop);
        }
    } 
    else {
        this -> root_ = newTop;
    }
}

// Node<Key,Value>* temp = BinarySearchTree<Key,Value>::predecessor(curr);
// AVLNode<Key,Value>* n = (AVLNode<Key,Value>*) temp;

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO
    if (this -> root_ == NULL) {
        this -> root_ = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
        return;
    }

    AVLNode<Key,Value>* current = static_cast<AVLNode<Key,Value>*>(this -> root_);
    if (new_item.first == current -> getKey()) {
        current -> setValue(new_item.second);       //overrides the value if it already exists
            return;
    }
    else if (new_item.first < current->getKey()) {
        if (current->getLeft() == nullptr) {
            current->setLeft(new AVLNode<Key,Value>(new_item.first,new_item.second, current));
            incHeight(current, true);
            return;
        } else {
            current = current->getLeft();
        }
    }
    else {
        if (current->getRight() == nullptr) {
            current->setRight(new AVLNode<Key,Value>(new_item.first,new_item.second, current));
            incHeight(current, false);
            return;
        } else {
            current = current->getRight();
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key,Value>* rem = static_cast<AVLNode<Key,Value>*>(this -> internalFind(key));
    if (rem == NULL){
        return; // key is not found in the AVL tree
    }
    if (rem -> getLeft() == NULL && rem ->getRight() == NULL){ //leaf node case
        if (rem -> getParent() == nullptr) {
            this -> root_ = nullptr;
        }
        else {
            AVLNode<Key,Value>* parent_node = rem -> getParent();
            if (isLeftChild(rem)) {
                rem -> getParent() -> setLeft(NULL);
            } else {
                rem -> getParent() -> setRight(nullptr);
            }
            decHeight(parent_node, isLeftChild(rem));
        }
    }
    else if (rem -> getLeft() != NULL && rem -> getRight() == nullptr){ //two child case
        nodeSwap(rem, static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::predecessor(rem)));
        AVLNode<Key,Value>* parent_node = rem -> getParent();

        if (rem -> getLeft() == NULL){
            if (isLeftChild(rem)) {
                parent_node -> setLeft(NULL);
            } 
            else {
                parent_node -> setRight(nullptr);
            }
        }
        else {
            AVLNode<Key,Value>* y = rem -> getLeft();
            if (isLeftChild(rem)){
                parent_node -> setLeft(NULL);
                y -> setParent(parent_node);
            }
            else {
                parent_node -> setRight(nullptr);
                y -> setParent(parent_node);
            }
        }
        decHeight(parent_node, isLeftChild(rem));
    }
    else if(rem -> getLeft() != nullptr) {
        AVLNode<Key,Value>* left = rem -> getLeft();
        if (rem -> getParent() == nullptr) {
            this -> root_ = left;
            left -> setParent(nullptr);
        } 
        else {
            AVLNode<Key,Value>* parent_node = rem -> getParent();
            if (isLeftChild(rem)) {
                parent_node -> setLeft(left);
            } 
            else {
                parent_node -> setRight(left);
            }
            left -> setParent(parent_node);
            decHeight(parent_node, isLeftChild(rem));
        }
    }
    else {
        AVLNode<Key,Value>* right = rem -> getRight();
        if (rem -> getParent() == nullptr) {
            this -> root_ = right;
            right -> setParent(nullptr);
        } 
        else {
            AVLNode<Key,Value>* parent_node = rem -> getParent();
            if (isLeftChild(rem)) {
                parent_node -> setLeft(right);
            } else {
                parent_node -> setRight(right);
            }
            right -> setParent(parent_node);
            decHeight(parent_node, isLeftChild(rem));
        }
    }
    delete rem;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}



#endif

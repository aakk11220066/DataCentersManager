//
// Created by User on 2019-11-29.
//

#ifndef DATACENTERSMANAGER_AVLTREE_H
#define DATACENTERSMANAGER_AVLTREE_H

#include "BinarySearchTree.h"
#include "../../DataManagerExceptions.h"

template <typename T>
class AVLTree : public BinarySearchTree<T>{
private:
    typedef std::shared_ptr<typename BinaryTree<T>::BinaryTreeNode>
            BinTreeNodePtr;

    BinTreeNodePtr rotateRR(typename BinaryTree<T>::BinaryTreeNode& root);

    BinTreeNodePtr rotateLL(typename BinaryTree<T>::BinaryTreeNode& root);

    BinTreeNodePtr rotateRL(typename BinaryTree<T>::BinaryTreeNode& root);

    BinTreeNodePtr rotateLR(typename BinaryTree<T>::BinaryTreeNode& root);

    //rebalance tree
    BinTreeNodePtr fixBalance(typename BinaryTree<T>::BinaryTreeNode& root);

    //returns balance factor defined for standard AVL trees
    int getBalanceFactor(typename BinaryTree<T>::BinaryTreeNode& node);

public:

    //ctor
    AVLTree();

    //dtor
    virtual ~AVLTree();

    //copy ctor
    AVLTree(const AVLTree &original);

    //BST promotion ctor (assumes original fits AVLTreeTemp standards)
    explicit AVLTree(const BinarySearchTree<T> &original);

    //operator=
    AVLTree &operator=(const AVLTree &original);

    //insert
    void insert(const T& data);

    //remove
    void remove(const T& data);
};


#endif //DATACENTERSMANAGER_AVLTREE_H

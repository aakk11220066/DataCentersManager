//
// Created by Akiva on 2019-11-28.
//

#ifndef DATASTRUCTURESWETHW1_BINARYSEARCHTREE_H
#define DATASTRUCTURESWETHW1_BINARYSEARCHTREE_H

#include "BinaryTree.h"

template<typename T>
class BinarySearchTree : public BinaryTree<T> {
private:
    //----FRIENDS----
    //to grant access to BinaryTreeNode from superclass
    template<typename U>
    friend U *findRecursive(typename BinaryTree<U>::BinaryTreeNode *root, const U &data);

public:
    //ctor
    explicit BinarySearchTree() = default;

    //dtor
    virtual ~BinarySearchTree() = default;

    //copy ctor
    BinarySearchTree(const BinarySearchTree &original) = default;

    //operator=
    BinarySearchTree &operator=(const BinarySearchTree &original) = default;

    //find
    virtual T &find(const T &data) const;
};



//-----------IMPLEMENTATIONS------------

#include "../../DataManagerExceptions.h"

template<typename T>
T *findRecursive(typename BinaryTree<T>::BinaryTreeNode *root, const T &data) {
    if (!root) return nullptr;
    if (data == root->data) return &(root->data);
    if (data > root->data) return findRecursive(root->right, data);
    else return findRecursive(root->left, data);
}

template<typename T>
T &BinarySearchTree<T>::find(const T &data) const {
    T *output = findRecursive(this->root, data);
    if (!output) throw DataManagerExceptions::ObjectUnfound();
    else return *output;
}


#endif //DATASTRUCTURESWETHW1_BINARYSEARCHTREE_H

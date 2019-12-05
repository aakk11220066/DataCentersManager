//
// Created by Akiva on 2019-11-28.
//

#ifndef DATASTRUCTURESWETHW1_BINARYTREE_H
#define DATASTRUCTURESWETHW1_BINARYTREE_H

#include "../Array.h"
#include <memory>
#include <algorithm> //for function max

template<typename T>
class BinaryTree {
protected:
    class BinaryTreeNode {
    private:
        unsigned int height = 1;
    public:
        T data;
        BinaryTreeNode *left = nullptr, *right = nullptr;

        //ctor
        explicit BinaryTreeNode(const T &data);

        //dtor
        virtual ~BinaryTreeNode();

        //Deletes a single node, returning its child.  Assumes node has single child
        BinaryTreeNode *deleteSingleNode();

        //copy ctor
        BinaryTreeNode(const BinaryTreeNode &original) = default;

        //operator=
        BinaryTreeNode &operator=(const BinaryTreeNode &original) = default;

        //receives output array and heap-allocated index, returns inOrder of sub-tree
        Array<T> &getInOrderRecursive(Array<T> &output, unsigned int &indexOffset) const;

        //returns height of node after modification of tree
        int getHeight();
    };

protected:
    BinaryTreeNode *root = nullptr;

private:
    unsigned int getSize(BinaryTreeNode *root);

public:
    //ctor
    BinaryTree() = default;

    //dtor
    virtual ~BinaryTree();

    //copy ctor
    BinaryTree(const BinaryTree &original) = default;

    //operator=
    BinaryTree &operator=(const BinaryTree &original) = default;

    //get array of tree, ordered inOrder
    Array<T> getInOrder() const;
};



//-----------IMPLEMENTATIONS------------

template<typename T>
Array<T> BinaryTree<T>::getInOrder() const { //wrapper for recursive call
    const auto constThis = const_cast<BinaryTree *> (this);
    Array<T> output = Array<T>(constThis->getSize(root));
    if (!root) return output;

    //remember placement in output array
    unsigned int *indexOffset = new unsigned int;
    *indexOffset = 0; //start at beginning

    root->getInOrderRecursive(output, *indexOffset);

    delete indexOffset;
    return output;
}

template<typename T>
Array<T> &BinaryTree<T>::BinaryTreeNode::getInOrderRecursive(Array<T> &output, unsigned int &indexOffset) const {

    if (this->left) {
        this->left->getInOrderRecursive(output, indexOffset);
    }

    output[indexOffset] = this->data;
    ++(indexOffset);

    if (this->right) {
        this->right->getInOrderRecursive(output, indexOffset);
    }

    return output;
}

template<typename T>
//runtime: O(n)
unsigned int BinaryTree<T>::getSize(
        BinaryTree::BinaryTreeNode *root) {

    if (!root) return 0;
    return 1 + getSize(root->left) + getSize(root->right);
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    delete (root);
}

template<typename T>
typename BinaryTree<T>::BinaryTreeNode *
BinaryTree<T>::BinaryTreeNode::deleteSingleNode() {

    BinaryTreeNode *child = (this->right) ? this->right : this->left;
    right = left = nullptr;
    delete (this);
    return child;
};

template<typename T>
BinaryTree<T>::BinaryTreeNode::BinaryTreeNode(const T &data) : data(data) {}

template<typename T>
BinaryTree<T>::BinaryTreeNode::~BinaryTreeNode() {
    delete (left);
    delete (right);
}

template<typename T>
int BinaryTree<T>::BinaryTreeNode::getHeight() {
    unsigned int leftHeight = (left) ? left->height : 0;
    unsigned int rightHeight = (right) ? right->height : 0;
    return height = 1 + std::max(leftHeight, rightHeight);
}


#endif //DATASTRUCTURESWETHW1_BINARYTREE_H

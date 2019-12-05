//
// Created by Akiva on 2019-11-29.
//

#ifndef DATACENTERSMANAGER_AVLTREE_H
#define DATACENTERSMANAGER_AVLTREE_H

#include "BinarySearchTree.h"
#include "../../DataManagerExceptions.h"

template <typename T>
class AVLTree : public BinarySearchTree<T>{
private:
    typedef typename BinaryTree<T>::BinaryTreeNode *
            BinTreeNodePtr;

    static BinTreeNodePtr rotateRR(typename BinaryTree<T>::BinaryTreeNode &root);

    static BinTreeNodePtr rotateLL(typename BinaryTree<T>::BinaryTreeNode &root);

    static BinTreeNodePtr rotateRL(typename BinaryTree<T>::BinaryTreeNode &root);

    static BinTreeNodePtr rotateLR(typename BinaryTree<T>::BinaryTreeNode &root);

    //rebalance tree
    static BinTreeNodePtr fixBalance(typename BinaryTree<T>::BinaryTreeNode &root);

    //returns balance factor defined for standard AVL trees
    static int getBalanceFactor(typename BinaryTree<T>::BinaryTreeNode &node);

    //--- FRIENDS ---
    //for BinTreeNodePtr, BinaryTreeNode type usage
    template<typename U>
    friend unsigned int height(typename AVLTree<U>::BinTreeNodePtr nodePtr);

    template<typename U>
    friend typename AVLTree<U>::BinTreeNodePtr
    insertRecursive(typename AVLTree<U>::BinTreeNodePtr rootPtr, const U &data);

    template<typename U>
    friend typename AVLTree<U>::BinTreeNodePtr
    getSuccessor(typename BinaryTree<U>::BinaryTreeNode &root);

    template<typename U>
    friend typename AVLTree<U>::BinTreeNodePtr
    destroy(typename AVLTree<U>::BinTreeNodePtr targetNode);

    template<typename U>
    friend typename AVLTree<U>::BinTreeNodePtr
    removeRecursive(typename AVLTree<U>::BinTreeNodePtr rootPtr, const U &data);

    template<typename U>
    friend void swapData(typename BinaryTree<U>::BinaryTreeNode &node1,
                         typename BinaryTree<U>::BinaryTreeNode &node2);
public:

    //ctor
    AVLTree() = default;

    //dtor
    virtual ~AVLTree() = default;

    //copy ctor
    AVLTree(const AVLTree &original) = default;

    //operator=
    AVLTree &operator=(const AVLTree &original) = default;

    //insert
    void insert(const T& data);

    //remove
    void remove(const T& data);
};


//-----------IMPLEMENTATIONS------------

template<typename T>
unsigned int height(typename AVLTree<T>::BinTreeNodePtr nodePtr) {
    return (nodePtr) ? nodePtr->getHeight() : 0;
}

template<typename T>
int AVLTree<T>::getBalanceFactor(typename BinaryTree<T>::BinaryTreeNode &node) {
    unsigned int heightLeft = height<T>(node.left);
    unsigned int heightRight = height<T>(node.right);
    return heightLeft - heightRight;
}

template<typename T>
typename AVLTree<T>::BinTreeNodePtr
AVLTree<T>::rotateRR(typename BinaryTree<T>::BinaryTreeNode &root) {

    AVLTree<T>::BinTreeNodePtr temp = root.right->left;
    AVLTree<T>::BinTreeNodePtr output = root.right;
    root.right->left = &root;
    root.right = temp;
    return output;
}

template<typename T>
typename AVLTree<T>::BinTreeNodePtr
AVLTree<T>::rotateLL(typename BinaryTree<T>::BinaryTreeNode &root) {

    AVLTree<T>::BinTreeNodePtr temp = root.left->right;
    AVLTree<T>::BinTreeNodePtr output = root.left;
    root.left->right = &root;
    root.left = temp;
    return output;
}

template<typename T>
typename AVLTree<T>::BinTreeNodePtr
AVLTree<T>::rotateRL(typename BinaryTree<T>::BinaryTreeNode &root) {

    root.right = rotateLL(*(root.right));
    return rotateRR(root);
}

template<typename T>
typename AVLTree<T>::BinTreeNodePtr
AVLTree<T>::rotateLR(typename BinaryTree<T>::BinaryTreeNode &root) {

    root.left = rotateRR(*(root.left));
    return rotateLL(root);
}

template<typename T>
typename AVLTree<T>::BinTreeNodePtr
AVLTree<T>::fixBalance(typename BinaryTree<T>::BinaryTreeNode &root) {

    AVLTree<T>::BinTreeNodePtr output;

    int balanceFactor = getBalanceFactor(root);
    if (abs(balanceFactor) != 2) output = &root;
    else if (balanceFactor == 2 && getBalanceFactor(*(root.left)) == -1) {
        output = rotateLR(root);
    } else if (balanceFactor == 2) {
        output = rotateLL(root);
    } else if (getBalanceFactor(*(root.right)) == 1) output = rotateRL(root);
    else output = rotateRR(root);

    root.getHeight(); //update height
    return output;
}

template<typename T>
typename AVLTree<T>::BinTreeNodePtr
insertRecursive(typename AVLTree<T>::BinTreeNodePtr rootPtr, const T &data) {

    if (!rootPtr) {
        return new typename BinaryTree<T>::BinaryTreeNode(data);
    }
    if (rootPtr->data == data) {
        throw DataManagerExceptions::ObjectAlreadyExists();
    }

    if (data > rootPtr->data) {
        rootPtr->right = insertRecursive(rootPtr->right, data);
        return AVLTree<T>::fixBalance(*rootPtr);
    }
    rootPtr->left = insertRecursive(rootPtr->left, data);
    return AVLTree<T>::fixBalance(*rootPtr);
}

template<typename T>
void AVLTree<T>::insert(const T &data) {
    this->root = insertRecursive(this->root, data);
}

template<typename T>
void swapData(typename BinaryTree<T>::BinaryTreeNode &node1,
              typename BinaryTree<T>::BinaryTreeNode &node2) {

    T temp = node1.data;
    node1.data = node2.data;
    node2.data = temp;
}

//finds the next greatest element to root in root's subtree
//assumes root has a right child
template<typename T>
typename AVLTree<T>::BinTreeNodePtr
getSuccessor(typename BinaryTree<T>::BinaryTreeNode &root) {

    typename AVLTree<T>::BinTreeNodePtr successor = root.right;
    while (successor->left) {
        successor = successor->left;
    }

    return successor;
}

template<typename T>
typename AVLTree<T>::BinTreeNodePtr
destroy(typename AVLTree<T>::BinTreeNodePtr targetNode) {

    //targetNode has no children - return empty subtree
    if (!(targetNode->right) && !(targetNode->left)) {
        return targetNode->deleteSingleNode();
    }

    //targetNode has only left child
    if (!(targetNode->right)) {
        return targetNode->deleteSingleNode();
    }

    //targetNode has only right child
    if (!(targetNode->left)) {
        return targetNode->deleteSingleNode();
    }

    //targetNode has 2 children
    /*swap data between targetNode and next greatest node, then remove next
     * greatest node from subtree from whence it came
     * (greater => right subtree).
     * Successor will have only 1 child maximum, by property of BST
     */
    typename AVLTree<T>::BinTreeNodePtr successorNode = getSuccessor<T>(*targetNode);
    swapData<T>(*targetNode, *successorNode);
    targetNode->right = removeRecursive(targetNode->right, successorNode->data);
    return AVLTree<T>::fixBalance(*targetNode);
}

template<typename T>
typename AVLTree<T>::BinTreeNodePtr
removeRecursive(typename AVLTree<T>::BinTreeNodePtr rootPtr, const T &data) {

    if (!rootPtr) throw DataManagerExceptions::ObjectUnfound();
    else if (data == rootPtr->data) {
        return destroy<T>(rootPtr);
    } else if (data > rootPtr->data) {
        rootPtr->right = removeRecursive(rootPtr->right, data);
    } else {
        rootPtr->left = removeRecursive(rootPtr->left, data);
    }
    return AVLTree<T>::fixBalance(*rootPtr);
}

template<typename T>
void AVLTree<T>::remove(const T &data) {
    this->root = removeRecursive(this->root, data);
}

#endif //DATACENTERSMANAGER_AVLTREE_H

//
// Created by User on 2019-11-29.
//

#include "Data Structures/AVLTree/AVLTree.h"
#include <iostream>

int main() {
    AVLTree<int> tree; //instantiation success
    /*try{ //find failure throws exception - success
        tree.find(6);
        assert(0);
    } catch (DataManagerExceptions::ObjectUnfound error1) {
        std::cout<<"typeid(error1) = "<<typeid(error1).name()<<"\n";
    }*/
    //insert elements - success
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(13);
    tree.insert(20);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(9);

    //remove test - success
    tree.remove(7);
    std::cout << "\n";
    Array<int> list = tree.getInOrder();
    for (int i = 0; i < list.getSize(); ++i) std::cout << list[i] << ", ";

    std::cout << "\nTest complete.";
    return 0;
}
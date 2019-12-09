//
// Created by Akiva on 2019-11-29.
//

//#include "Data Structures/AVLTree/AVLTree.h"
//#include <iostream>
#include "DataCenterManager.h"

int main() {

    //AVLTree<int> tree; //instantiation success
    /*try{ //find failure throws exception - success
        tree.find(6);
        assert(0);
    } catch (DataManagerExceptions::ObjectUnfound error1) {
        std::cout<<"typeid(error1) = "<<typeid(error1).name()<<"\n";
    }*/
    //insert elements - success
/*
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

    //find test - success
    std::cout << "\nLooking for 4, found " << tree.find(4);
    //int temp = tree.find(7);
    //printf("temp is %d", temp);

    std::cout << "\nTest complete.";
*/

    DataCenterManager dcm;
    dcm.AddDataCenter(31, 2);
    dcm.AddDataCenter(20, 8);
    dcm.AddDataCenter(50, 3);

    int *arr;
    int num;
    //dcm.RequestServer(50, 1, 1 , &num);
    //dcm.RequestServer(50, 2, 1 , &num);
    dcm.RemoveDataCenter(31);
    int res = dcm.GetDataCentersByOs(0, &arr, &num);


    printf("res is %d\n", res);
    printf("num is %d\n", num);
    for (int i=0; i<num; i++){
        printf("data is %d\n", arr[i]);
    }
    free(arr);

    return 0;
}
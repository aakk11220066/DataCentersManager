#include <iostream>
#include "linkedList.h"
#include "DataCenter.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    //Node exmp;
    //exmp.print();
/*
    DoubleLinkedList db;
    Node* p1 = new Node(1);
    Node* p2 = new Node(2);
    Node* p3 = new Node(3);
    Node* p56 = new Node(56);
    db.beginningInsert(p1);
    db.beginningInsert(p2);
    db.beginningInsert(p3);
    db.endInsert(p56);
    db.print();
    printf("head is %d, tail is %d\n", db.getHead()->getData(), db.getTail()->getData());
    Node* temp = p3;
    db.deleteNode(temp);
    db.print();
    printf("head is %d, tail is %d\n", db.getHead()->getData(), db.getTail()->getData());
    */


    DataCenter dc(125, 5);
    //dc.printPosition();
    dc.printServers();
    int *assigned = new int;
    dc.requestServer(1,1, assigned);
    dc.printServers();
    dc.requestServer(0,1, assigned);
    dc.printServers();
    dc.requestServer(1, 0, assigned);
    dc.printServers();
    dc.freeServer(2);
    dc.printServers();
    dc.freeServer(1);
    dc.printServers();
    dc.freeServer(0);
    dc.printServers();

    dc.requestServer(0,4, assigned);
    dc.printServers();
    dc.requestServer(0,4, assigned);
    dc.printServers();
    dc.requestServer(0,4, assigned);
    dc.printServers();
    dc.requestServer(0,4, assigned);
    dc.printServers();
    dc.requestServer(0,4, assigned);
    dc.printServers();

    dc.requestServer(1,1, assigned);
    //dc.printServers();
    dc.requestServer(1,4, assigned);
    //dc.printServers();
    dc.requestServer(1,3, assigned);
    //dc.printServers();


    DataCenter dc2(125, 3);
    //if (dc2 > dc) printf("correct\n");
    //if (dc2 == dc) printf("correct2\n");
    delete assigned;

    return 0;
}

//
// Created by Roy on 28/11/19.
//

#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H

#include <iostream>
#include "DataManagerExceptions.h"

class Node {
private:
    int m_data;
    Node *next;
    Node *previous;
public:

    //constructor
    explicit Node(int data = 0) : m_data(data), next(nullptr), previous(nullptr) {}

    //get m_data
    int getData() const {return m_data;}

    //get next Node pointer
    Node* getNext() const {return next;}

    //get get previous Node pointer
    Node* getPrevious() const {return previous;}

    //set next & previous pointer to a given pointer, respectively.
    void setNext(Node* p){next = p;}
    void setPrevious(Node* p){if (p == nullptr) return; previous = p;}
};

class DoubleLinkedList{
private:
    Node* head;
    Node* tail;
    int size;
    bool doNotDelete = false;
public:

    //ctor
    DoubleLinkedList(): head(nullptr), tail(nullptr), size(0){}

    /**
    copy ctor
    operates on O(1) even though list's size is n.
     boolean dataMember doNotDelete updates such that when copied list's destructor will be called.,
     there won't be a case in which the nodes would be deleted twice.
     */
    DoubleLinkedList(const DoubleLinkedList &original) : head(original.head), tail(original.tail), size(original.size),
                                                         doNotDelete(false) {
        if (original.doNotDelete) throw DataManagerExceptions::LinkedListExpired();
        const_cast<DoubleLinkedList &>(original).doNotDelete = true;
    }

    //operator==
    DoubleLinkedList &operator=(const DoubleLinkedList &original) {
        if (original.doNotDelete) throw DataManagerExceptions::LinkedListExpired();
        head = original.head;
        tail = original.tail;
        size = original.size;
        doNotDelete = false;
        const_cast<DoubleLinkedList &>(original).doNotDelete = true;
        return (*this);
    }

    //dtor
    //only deletes a linked list whose doNotDelete value is appropriate.
    ~DoubleLinkedList() noexcept {
        if (doNotDelete) return;
        while(head!= nullptr){
            Node *temp = head;
            //head = head->next;
            head = head->getNext();
            delete temp;
        }
    }

    //get list's size.
    int getSize() const {return size;}

    //get list's tail.
    Node* getTail() const {
        if (doNotDelete) throw DataManagerExceptions::LinkedListExpired();
        return tail;
    }

    /** adds a given Node's pointer to the list.
     * if the list is empty, both head and tail updates to these address.
     * if it isn't, list's head is updated to the given Pointer.
     * @param p
     */
    void beginningInsert(Node* p);
    void deleteNode(Node* p);
};

void DoubleLinkedList::beginningInsert(Node* p){
    if (p== nullptr) return;
    if (doNotDelete) throw DataManagerExceptions::LinkedListExpired();
    if (size ==0){
        head =p;
        tail =p;
    }
    else{
        //head->previous = p;
        head->setPrevious(p);
        p->setNext(head);
        //p->next = head;
        head = p;
    }
    size++;
}

/** deletes a node in the following cases:
 * if list's size is 1, updates tail & head to null.
 * if the pointer points to the head/tail, delete and update head/tail.
 * else, update neighbouring nodes accordingly when deleting.
 * @param p
 */
void DoubleLinkedList::deleteNode(Node *p){
    if (doNotDelete) throw DataManagerExceptions::LinkedListExpired();
    if (size == 1){
        head = nullptr;
        tail = nullptr;
        delete p;
        size--;
        return;
    }
    if (p == head){
        (p->getNext())->setPrevious(nullptr);
        head = head->getNext();
        delete p;
        size--;
        return;
    }
    if (p == tail){
        (p->getPrevious())->setNext(nullptr);
        tail = p->getPrevious();
        delete p;
        size--;
        return;
    }
    if (p == nullptr){
        return;
    }
    else {
        (p->getPrevious())->setNext(p->getNext());
        (p->getNext())->setPrevious(p->getPrevious());
        delete p;
    }
    size--;
}

#endif //UNTITLED_LINKEDLIST_H

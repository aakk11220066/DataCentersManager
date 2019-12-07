//
// Created by Roy on 28/11/19.
//

#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H

#include <iostream>
#include "DataManagerExceptions"

class Node {
private:
    int m_data;
    Node *next;
    Node *previous;
public:
    explicit Node(int data = 0) : m_data(data), next(nullptr), previous(nullptr) {}
    int getData() const {return m_data;}
    Node* getNext() const {return next;}
    Node* getPrevious() const {return previous;}
    void setNext(Node* p){next = p;}
    void setPrevious(Node* p){if (p == nullptr) return; previous = p;}
    void print() { std::cout << m_data << std::endl; };
};

class DoubleLinkedList{
private:
    Node* head;
    Node* tail;
    int size;
    boolean doNotDelete = false;
public:
    DoubleLinkedList(): head(nullptr), tail(nullptr), size(0){}
    DoubleLinkedList(DoubleLinkedList& original) : head(original.head), tail(original.tail), size(original.size), doNotDelete(false) {
        if (original.doNotDelete) throw LinkedListExpired();
        original.doNotDelete = true;
    }
    DoubleLinkedList operator=(DoubleLinkedList& original){
        if (original.doNotDelete) throw LinkedListExpired();
        head = original.head;
        tail = original.tail;
        size = original.size;
        doNotDelete = false;
        original.doNotDelete = true;
    }
    ~DoubleLinkedList(){
        if (doNotDelete) return;
        while(head!= nullptr){
            Node* temp = head;
            //head = head->next;
            head = head->getNext();
            delete temp;
        }
    }
    int getSize() const {return size;}
    Node* getTail() const {
        if (doNotDelete) throw LinkedListExpired();
        return tail;
    }
    Node* getHead() const { 
        if (doNotDelete) throw LinkedListExpired();
        return head;
    }
    void beginningInsert(Node* p);
    void endInsert(Node* p);
    void deleteNode(Node* p);
    void print(){
        if (doNotDelete) throw LinkedListExpired();
        Node* p = head;
        while (p!= nullptr){
            std::cout << p->getData() << " < ";
            p=p->getNext();
        }
        std::cout << std::endl;
    }
};

void DoubleLinkedList::beginningInsert(Node* p){
    if (p== nullptr) return;
    if (doNotDelete) throw LinkedListExpired();
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
    void DoubleLinkedList::endInsert(Node* p){
        if (p== nullptr) return;
        if (doNotDelete) throw LinkedListExpired();
        if (size ==0){
            head =p;
            tail =p;
        }
        else{
            //tail->next = p;
            //p->previous = tail;
            tail->setNext(p);
            p->setPrevious(tail);
            tail = p;
        }
        size++;
    }
void DoubleLinkedList::deleteNode(Node *p){
    if (doNotDelete) throw LinkedListExpired();
    if (size == 1){
        head = nullptr;
        tail = nullptr;
        delete p;
        size--;
        return;
    }
    if (p == head){
        //(p->next)->previous = nullptr;
        //head = head->next;
        (p->getNext())->setPrevious(nullptr);
        head = head->getNext();
        delete p;
        size--;
        return;
    }
    if (p == tail){
        //(p->previous)->next = nullptr;
        //tail = p->previous;
        (p->getPrevious())->setNext(nullptr);
        tail = p->getPrevious();
        delete p;
        size--;
        return;
    }
    else {
        //(p->previous)->next = p->next;
        //(p->next)->previous = p->previous;
        (p->getPrevious())->setNext(p->getNext());
        (p->getNext())->setPrevious(p->getPrevious());
        delete p;
    }
    size--;
}

#endif //UNTITLED_LINKEDLIST_H

//
// Created by Roy on 28/11/19.
//

#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H

class Node {
private:
    int m_data;
    Node *next;
    Node *previous;
public:
    explicit Node(int data = 0) : m_data(data), next(nullptr), previous(nullptr) {}
    int getData() {return m_data;}
    Node* getNext(){return next;}
    Node* getPrevious(){return previous;}
    void setNext(Node* p){next = p;}
    void setPrevious(Node* p){if (p == nullptr) return; previous = p;}
    void print() { std::cout << m_data << std::endl; };
};

class DoubleLinkedList{
private:
    Node* head;
    Node* tail;
    int size;
public:
    DoubleLinkedList(): head(nullptr), tail(nullptr), size(0){}
    ~DoubleLinkedList(){
        while(head!= nullptr){
            Node* temp = head;
            //head = head->next;
            head = head->getNext();
            delete temp;
        }
    }
    int getSize() {return size;}
    Node* getTail(){return tail;}
    Node* getHead(){ return head;}
    void beginningInsert(Node* p);
    void endInsert(Node* p);
    void deleteNode(Node* p);
    void print(){
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

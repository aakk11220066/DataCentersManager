//
// Created by Roy on 28/11/19.
//

#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H
class Node {
public:
    int m_data;
    Node *next;
    Node *previous;

    explicit Node(int data = 0) : m_data(data), next(nullptr), previous(nullptr) {}
    void print() { std::cout << m_data << std::endl; };
};

class DoubleLinkedList{
public:
    Node* head;
    Node* tail;
    int size;
    DoubleLinkedList(): head(nullptr), tail(nullptr), size(0){}
    ~DoubleLinkedList(){
        while(head!= nullptr){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void beginningInsert(Node* p);
    void endInsert(Node* p);
    void deleteNode(Node* p);
    void print(){
        Node* p = head;
        while (p!= nullptr){
            std::cout << p->m_data << " < ";
            p=p->next;
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
        head->previous = p;
        p->next = head;
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
        tail->next = p;
        p->previous = tail;
        tail = p;
    }
    size++;
}
void DoubleLinkedList::deleteNode(Node *p){
    if (size == 1){
        head = nullptr;
        tail = nullptr;
        delete p;
    }
    if (p == head){
        printf("hi!!\n");
        (p->next)->previous = nullptr;
        head = head->next;
        delete p;
        return;
    }
    if (p == tail){
        (p->previous)->next = nullptr;
        tail = p->previous;
        delete p;
        return;
    }
    else {
        (p->previous)->next = p->next;
        (p->next)->previous = p->previous;
        delete p;
    }
    size--;
}

#endif //UNTITLED_LINKEDLIST_H

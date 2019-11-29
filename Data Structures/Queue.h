//
// Created by User on 2019-11-29.
//

#ifndef DATACENTERSMANAGER_QUEUE_H
#define DATACENTERSMANAGER_QUEUE_H

#include "../linkedList.h"
#include <memory>

template <typename T>
class Queue : private DoubleLinkedList<T> {
public:
    //ctor
    Queue();

    //dtor
    virtual ~Queue();

    //copy ctor
    Queue(const Queue& original);

    //operator=
    Queue& operator=(const Queue& original);

    //enqueue
    void enqueue(const T& data);

    //dequeue
    T& dequeue();

    //head
    T& head();

    //is_empty
    bool is_empty();
};

#endif //DATACENTERSMANAGER_QUEUE_H

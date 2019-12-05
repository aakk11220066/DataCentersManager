//
// Created by Akiva on 2019-11-29.
//

#include "Queue.h"


template<typename T>
void Queue<T>::enqueue(const T &data) {
    beginningInsert(&data);
}

template<typename T>
T &Queue<T>::dequeue() {
    T& output = head();
    deleteNode(head);
    return output;
}

template<typename T>
T &Queue<T>::head() {
    return *(getTail);
}

template<typename T>
bool Queue<T>::is_empty() {
    return head;
}


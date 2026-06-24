#pragma once
#include "LinkedList.h"

struct QNode {
    Product data;
    QNode *next = nullptr;
};

class Restock {
private:
    QNode* front = nullptr;
    QNode* rear  = nullptr;
    int size = 0;

public:
    bool isEmpty() { return front == nullptr; }
    int getSize() { return size; }

    void enqueue(Product p) {
        QNode *e = new QNode;
        e->data = p;
        e->next = nullptr;

        if (rear) {
            rear->next = e;
            rear = e;        
        } else {
            rear = e;
            front = e;
        }
        size++;
    }

    Product dequeue() {
        QNode* temp = front;
        Product p = temp->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        size--;
        return p;
    }
       Product peek() {
        return front->data;
    }
};
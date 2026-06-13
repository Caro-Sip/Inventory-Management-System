#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Product.h"

class DoublyLinkedList {
public:

    struct Element2 {
        Element2* prev;
        Element2* next;
        Product data;
        
        Element2(const Product& p) : prev(nullptr), next(nullptr), data(p) {}
    };

private:
    Element2* head;
    Element2* tail;
    int size;

public:
    DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
 
    ~DoublyLinkedList();

    Element2* getHead() const;
    int getSize() const;
    int getMaxID() const;

    Element2* add(const Product& data);
    void removeNode(Element2* nodelyL);
    void display() const;
    void sort();
    
};

// class SinglyLinkedList {
// private:
//     struct Element {
//         Element* next;
//         Product data; 
        
//         Element(const Product& p) : next(nullptr), data(p) {}
//     };

//     Element* head;
//     Element* tail;
//     int size;

// public:
//     SinglyLinkedList();
    
//     SinglyLinkedList(const SinglyLinkedList&) = delete;
//     SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
    
//     ~SinglyLinkedList();

//     Element* getHead() const;
//     void add(const Product& data);
// };

#endif
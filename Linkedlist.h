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
    void setHead(Element2* node);
    int getSize() const;
    int getMaxID() const;

    Element2* split(Element2* head);
    Element2* merge(Element2* left, Element2* right, bool (*compare)(const Product&, const Product&));
    Element2* mergeSort(Element2* head, bool (*compare)(const Product&, const Product&));

    Element2* add(const Product& data);
    void removeNode(Element2* node);
    void display() const;
};

#endif
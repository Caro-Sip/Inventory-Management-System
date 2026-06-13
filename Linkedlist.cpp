#include <iostream>
#include<iomanip>
#include "Linkedlist.h"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoublyLinkedList::~DoublyLinkedList(){
    Element2 *current = head;
    while(current != nullptr){
        Element2 *nextNode = current -> next;
        delete current;
        current = nextNode;
    }
}
DoublyLinkedList::Element2* DoublyLinkedList::getHead() const { return head; }
void DoublyLinkedList::setHead(Element2* node) { head = node; }

int DoublyLinkedList::getSize() const { return size; }

int DoublyLinkedList::getMaxID() const {
    int max = 0;
    Element2* node = head;
    while (node != nullptr) {
        if (node->data.id > max) {
            max = node->data.id;
        }
        node = node->next; 
    }
    return max;
}

DoublyLinkedList::Element2* DoublyLinkedList::add(const Product& data) {
    Element2* node = new Element2(data);
    node-> next = nullptr;

    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    size++;
    return node;
}
void DoublyLinkedList::display() const {
    std::cout << std::endl;
    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(20) << "Name"
              << std::setw(12) << "Quantity"
              << std::setw(10) << "Price"
              << "\n";
    std::cout << std::string(52, '-') << "\n";

    Element2* current = head;
    while (current != nullptr) {
        std::cout << std::left
                  << std::setw(10) << current->data.id
                  << std::setw(20) << current->data.name
                  << std::setw(12) << current->data.quantity
                  << std::setw(10) << current->data.price
                  << "\n";
        current = current->next;
    }
}



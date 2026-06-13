#include <iostream>
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


int DoublyLinkedList::getSize() const { return size; }
// make sure there no collision with the id
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


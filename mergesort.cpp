#include "Product.h"
#include "Linkedlist.h"


bool byId(Product a, Product b) { return (a.id < b.id); }
bool byName(Product a, Product b) { return (a.name < b.name); }
bool byQuantity(Product a, Product b) { return (a.quantity < b.quantity); }
bool byPrice(Product a, Product b) { return (a.price < b.price); }

DoublyLinkedList::Element2* DoublyLinkedList::merge(DoublyLinkedList::Element2* left, DoublyLinkedList::Element2* right, bool (*compare)(Product a, Product b)) {
    
}
DoublyLinkedList::Element2* DoublyLinkedList::mergeSort(DoublyLinkedList::Element2* head, bool (*compare)(Product a, Product b)) {
    if(head == nullptr || head->next = nullptr) return head;

    Element2 *slow = head;
    Element2 *fast = head->next;

    while (fast != nullptr && fast->next != nulltpr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Element2 *middle = slow;
    slow->next = nulltpr;

    middle->prev = nulltpr;

    Element2 *left = DoublyLinkedList::mergeSort(head, compare);
    DoublyLinkedList::mergeSort(middle, compare);
}


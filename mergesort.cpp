#include "Product.h"
#include "Linkedlist.h"

bool byId(const Product &a, const Product &b) { return (a.id < b.id); }
bool byName(const Product &a, const Product &b) { return (a.name < b.name); }
bool byQuantity(const Product &a, const Product &b) { return (a.quantity < b.quantity); }
bool byPrice(const Product &a, const Product &b) { return (a.price < b.price); }

DoublyLinkedList::Element2* DoublyLinkedList::split(DoublyLinkedList::Element2* head) {
    DoublyLinkedList::Element2* fast = head;
    DoublyLinkedList::Element2* slow = head;

    while (fast != nullptr && fast->next != nullptr
           && fast->next->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }

    DoublyLinkedList::Element2* mid = slow->next;
    slow->next = nullptr;
    if (mid != nullptr)
        mid->prev = nullptr;

    return mid;
}

DoublyLinkedList::Element2* DoublyLinkedList::merge(DoublyLinkedList::Element2* left, DoublyLinkedList::Element2* right, bool (*compare)(const Product &a,const Product &b)) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    if (compare(left->data, right->data)) {
        left->next = merge(left->next, right, compare);
        if (left->next != nullptr)
            left->next->prev = left;
        left->prev = nullptr;
        return left;
    } else {
        right->next = merge(left, right->next, compare);
        if (right->next != nullptr)
            right->next->prev = right;
        right->prev = nullptr;
        return right;
    }
}

DoublyLinkedList::Element2* DoublyLinkedList:: mergeSort(DoublyLinkedList::Element2* head, bool (*compare)(const Product &a,const Product &b)) {
    if (head == nullptr || head->next == nullptr) return head;

    DoublyLinkedList::Element2* second = split(head);

    head   = mergeSort(head, compare);
    second = mergeSort(second, compare);

    return DoublyLinkedList::merge(head, second, compare);
}
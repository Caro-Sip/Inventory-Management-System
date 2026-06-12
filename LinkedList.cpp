#include "LinkedList.h"

class SinglyLinkedList : public LinkedList {
private:
  Element *head;
  Element *tail;
  int size;

public:
  SinglyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  Element *getHead() { return head; }

  void add(Element2 *data) {
    Element *node = new Element;
    node->data = data;
    node->next = nullptr;

    if (size == 0) {
      head = node;
    } else {
      tail->next = node;
    }
    tail = node;
    size++;
  }
};

class DoublyLinkedList : public LinkedList {
private:
  Element2 *head;
  Element2 *tail;
  int size;

public:
  DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  int getMaxID() {
    int max = 0;
    Element2 *node = head;
    while (node != nullptr) {
      if (node->data.id > max)
        max = node->data.id;
      node = (Element2 *)node->next;
    }
    return max;
  }

  Element2 *add(Product data) {
    Element2 *node = new Element2;
    node->data = data;
    node->next = nullptr;

    if (size == 0) {
      node->prev = nullptr;
      head = node;
    } else {
      node->prev = tail;
      tail->next = node;
    }
    tail = node;
    size++;
    return node; // return pointer to the new node
  }

  void remove(std::string id) {
    // need hashtable first
  }
};
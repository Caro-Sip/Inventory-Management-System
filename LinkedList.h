#pragma once

#include "Product.h"
#include <iostream>

struct Element2 {
  Element2 *prev;
  Element2 *next;
  Product data;
};

struct Element {
  Element *next;
  Element2 *data;
};

class SinglyLinkedList {
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

class DoublyLinkedList {
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

  Element2 *getHead() { return head; }
  int getSize() { return size; }

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

  void remove(int id) {
    // need hashtable first
  }

  void update(int id) {
    // waiting
  }

  void display() {
    Element2 *node = head;
    while (node != nullptr) {
      std::cout << node->data.id << " | " << node->data.name << " | "
                << node->data.quantity << " | " << node->data.price << "\n";
      node = node->next;
    }
  }
};
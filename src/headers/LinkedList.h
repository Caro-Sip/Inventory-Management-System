#pragma once

#include "Product.h"
#include <iomanip>
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

  ~DoublyLinkedList() {
    Element2 *curr = head;
    while (curr != nullptr) {
      Element2 *next = curr->next;
      delete curr;
      curr = next;
    }
  }

  void clear() {
    Element2 *curr = head;
    while (curr != nullptr) {
      Element2 *next = curr->next;
      delete curr;
      curr = next;
    }
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
    return node;
  }

  void remove(int id) {
    Element2 *curr = head;
    while (curr != nullptr) {
      if (curr->data.id == id) {
        if (curr->prev != nullptr) {
          curr->prev->next = curr->next;
        } else {
          head = curr->next;
        }
        if (curr->next != nullptr) {
          curr->next->prev = curr->prev;
        } else {
          tail = curr->prev;
        }
        delete curr;
        size--;
        return;
      }
      curr = curr->next;
    }
  }

  void display(Element2 &data) {
    std::cout << std::left << std::setw(5) << data.data.id << std::setw(15)
              << data.data.name << std::setw(10) << data.data.quantity
              << std::setw(10) << data.data.price << "\n";
  }
};
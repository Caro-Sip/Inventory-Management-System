#pragma once

#include "LinkedList.h"
#include "Product.h"
#include <iomanip>

template <typename T>

class vector {
private:
  int capacity;
  int used;
  T *data;

  void increaseSize() {
    capacity *= 2;
    T *newData = new T[capacity];

    for (int i = 0; i < used; i++) {
      newData[i] = data[i];
    }
    delete[] data;
    data = newData;
  }

public:
  vector() {
    data = new T[1];
    capacity = 1;
    used = 0;
  }
  ~vector() { delete[] data; }

  T &operator[](int index) { return data[index]; }

  void push_back(T data) {
    if (capacity == used)
      increaseSize();
    this->data[used++] = data;
  }

  int size() { return used; }

  // custom display all
  void display() {
    std::cout << std::endl;
    std::cout << std::left << std::setw(5) << "ID" << std::setw(15) << "Name"
              << std::setw(10) << "Quantity" << std::setw(10) << "Price"
              << "\n";
    std::cout << std::string(40, '-') << "\n";

    for (int i = 0; i < used; i++) {
      std::cout << std::left << std::setw(5) << data[i].id << std::setw(15)
                << data[i].name << std::setw(10) << data[i].quantity
                << std::setw(10) << data[i].price << "\n";
    }
  }

  // custom load doubly linked list into vector
  void load(DoublyLinkedList &ls) {
    Element2 *node = ls.getHead();
    while (node != nullptr) {
      this->push_back(node->data);
      node = node->next;
    }
  }
};
#pragma once

#include "LinkedList.h"

class HashTable {
private:
  int tableSize;
  Element **table;

  int hash(int id) { return id % this->tableSize; }

public:
  HashTable() : tableSize(0), table(nullptr) {}

  ~HashTable() {
    for (int i = 0; i < this->tableSize; i++) {
      Element *node = this->table[i];
      while (node != nullptr) {
        Element *next = node->next;
        delete node;
        node = next;
      }
    }
    delete[] this->table;
  }

  void insert(Element2 *node) {
    int index = hash(node->data.id);
    Element *newNode = new Element;
    newNode->data = node;
    newNode->next = this->table[index];
    this->table[index] = newNode;
  }

  void init(DoublyLinkedList &ls) {
    this->tableSize = ls.getSize();
    this->table = new Element *[this->tableSize];
    for (int i = 0; i < this->tableSize; i++) {
      this->table[i] = nullptr;
    }

    Element2 *node = ls.getHead();
    while (node != nullptr) {
      this->insert(node);
      node = node->next;
    }
  }

  Element2 *search(int id) {
    if (id < 0 || id >= this->tableSize)
      return nullptr;
    Element *node = this->table[hash(id)];
    while (node != nullptr) {
      if (node->data->data.id == id) {
        return node->data;
      }
      node = node->next;
    }
    return nullptr;
  }
};
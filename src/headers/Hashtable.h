#pragma once

#include "LinkedList.h"

class HashTable {
private:
  int tableSize;
  // a variable declared as a pointer to an array of pointers in heap
  Element **table;

  int hash(int id) { return id % this->tableSize; }

public:
  //
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

  void insert(Element2 *node) {
    int index = hash(node->data.id);
    Element *newNode = new Element;
    newNode->data = node;
    newNode->next = this->table[index];
    this->table[index] = newNode;
  }
  
  void clear() {
    for (int i = 0; i < this->tableSize; i++) {
      Element *node = this->table[i];
      while (node != nullptr) {
        Element *next = node->next;
        delete node;
        node = next;
      }
      this->table[i] = nullptr;
    }
    delete[] this->table;
    this->table = nullptr;
    this->tableSize = 0;
  }

  Element2* search(int id) {
    if (id < 0 || this->tableSize == 0 || this->table == nullptr) return nullptr;
    Element *node = this->table[hash(id)];
    // Walks through the SLL until it finds the matching id
    while (node != nullptr) {
      if (node->data->data.id == id) {
        return node->data;
      }
      node = node->next;
    }
    return nullptr;
  }
};
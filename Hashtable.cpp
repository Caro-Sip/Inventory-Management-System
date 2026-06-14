#include "Hashtable.h"
#include "Linkedlist.h"
#include <iostream>

HashTable::HashTable() : table(BucketCount, nullptr) {}

HashTable::~HashTable() {
  for (int i = 0; i < BucketCount; ++i) {
    HashNode *current = table[i];
    while (current != nullptr) {
      HashNode *toDelete = current;
      current = current->next;
      delete toDelete;
    }
  }
}

int HashTable::hash(int id) const {
  return (id < 0) ? (-id % BucketCount) : (id % BucketCount);
}
void HashTable::insert(int id, DoublyLinkedList::Element2 *data) {
  if (data == nullptr)
    return;
  int index = hash(id);
  HashNode *newNode = new HashNode(id, data);
  if (table[index] == nullptr) {
    table[index] = newNode;
  } else {
    newNode->next = table[index];
    table[index] = newNode;
  }
}

DoublyLinkedList::Element2 *HashTable::search(int id) {
  int index = hash(id);
  HashNode *current = table[index];
  while (current != nullptr) {
    if (current->id == id) {
      return current->data;
    }
    current = current->next;
  }
  return nullptr;
}

void HashTable::load(DoublyLinkedList *ls) {
    DoublyLinkedList::Element2 *node = ls->getHead();
  while (node != nullptr){
        insert(node->data.id, node);
        node = node->next;
    }

    // if (!found) {
    //   HashNode *newNode = new HashNode(node->data.id, node);
    //   newNode->next = table[index];
    //   table[index] = newNode;
    // }
}
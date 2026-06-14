
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Linkedlist.h"
#include <utility>
#include <vector>

class HashTable {
private:
  struct HashNode {
    int id;
    DoublyLinkedList::Element2 *data;
    HashNode *next;
    HashNode(int id, DoublyLinkedList::Element2 *data) {
      this->id = id;
      this->data = data;
      this->next = nullptr;
    }
  };
  const int BucketCount = 100;
  std::vector<HashNode *> table;
  int hash(int id) const;

public:
  HashTable();

  HashTable(const HashTable &) = delete;
  HashTable &operator=(const HashTable &) = delete;

  ~HashTable();

  void insert(int id, DoublyLinkedList::Element2 *data);
  DoublyLinkedList::Element2 *search(int id);
  void remove(int id);
  void load(DoublyLinkedList *ls);
};
#endif

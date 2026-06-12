#include "LinkedList.h"

class HashTable {
private:
  int tableSize;
  Element2 **table;

  int hash(int id) { return id % this->tableSize; }

public:
  HashTable() : tableSize(0), table(nullptr) {}

  ~HashTable() { delete[] this->table; }

  void init(int size) {
    this->tableSize = size;
    this->table = new Element2 *[this->tableSize];
    for (int i = 0; i < this->tableSize; i++) {
      this->table[i] = nullptr;
    }
  }

  void insert(Element2 *node) { this->table[hash(node->data.id)] = node; }

  Element2 *search(int id) {
    if (id < 0 || id >= this->tableSize)
      return nullptr;
    return this->table[hash(id)];
  }
};
#include "LinkedList.cpp"

class HashTable {
private:
  int tableSize;
  SinglyLinkedList **table;

  int hash(int id) { return id % this->tableSize; }

public:
  HashTable() : tableSize(0), table(nullptr) {}

  ~HashTable() {
    for (int i = 0; i < this->tableSize; i++) {
      delete this->table[i];
    }
    delete[] this->table;
  }

  void init(int size) {
    this->tableSize = size;
    this->table = new SinglyLinkedList *[this->tableSize];
    for (int i = 0; i < this->tableSize; i++) {
      this->table[i] = new SinglyLinkedList;
    }
  }

  void insert(Element2 *node) { this->table[hash(node->data.id)]->add(node); }

  Element2 *search(int id) {
    if (id < 0 || id >= this->tableSize)
      return nullptr;
    Element *node = this->table[hash(id)]->getHead();
    while (node != nullptr) {
      if (node->data->data.id == id) {
        return node->data;
      }
      node = node->next;
    }
    return nullptr;
  }
};
#pragma once


#include <vector>
#include <utility>


// class HashTable {
// private:
//   int tableSize;
//   SinglyLinkedList **table;

//   int hash(int id) { return id % this->tableSize; }

// public:
//   HashTable() : tableSize(0), table(nullptr) {}

//   ~HashTable() {
//     for (int i = 0; i < this->tableSize; i++) {
//       delete this->table[i];
//     }
//     delete[] this->table;
//   }

//   void insert(Element2 *node) { this->table[hash(node->data.id)]->add(node); }

//   void init(DoublyLinkedList &ls) {
//     this->tableSize = ls.getSize();
//     this->table = new SinglyLinkedList *[this->tableSize];
//     for (int i = 0; i < this->tableSize; i++) {
//       this->table[i] = new SinglyLinkedList;
//     }

//     Element2 *node = ls.getHead();
//     while (node != nullptr) {
//       this->insert(node);
//       node = node->next;
//     }
//   }
struct Element2;

class HashTable{
  private:
  struct HashNode{
    int id;
    Element2 *value;
    Element2 *next;
    HashNode(int id, Element2* v){
      this->id = id;
      this->value = v;
      this->next =nullptr;

    }
  };
  const int BucketCount = 100;
  std::vector<HashNode*> table;
  int hash(int id) const;
 public:
  HashTable();

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;


    ~HashTable();

    void insert(int id, Element2* node);
    Element2* search(int id);
    void remove(int id);
    void display();
};


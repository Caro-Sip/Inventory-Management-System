
#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <vector>
#include <utility>

struct Element2;

class HashTable{
  private:
  struct HashNode{
    int id;
    Element2 *value;
    HashNode *next;
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
#endif

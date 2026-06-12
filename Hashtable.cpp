#include "LinkedList.cpp"

int nextPrime(int n) {
  while (true) {
    bool isPrime = true;
    for (int i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        isPrime = false;
        break;
      }
    }
    if (isPrime)
      return n;
    n++;
  }
}

class HashTable {
private:
  Element2 **table;
  int tableSize;

  int hash(int id) { return id % this->tableSize; }

public:
  HashTable() : table(nullptr), tableSize(0) {}

  ~HashTable() { delete[] this->table; }

  void init(int maxID) {
    this->tableSize = nextPrime(maxID + 1);
    this->table = new Element2 *[this->tableSize];
    for (int i = 0; i < this->tableSize; i++) {
      this->table[i] = nullptr;
    }
  }

  void insert(Element2 *node) { this->table[hash(node->data.id)] = node; }

  Element2 *search(int id) {
    if (id < 0 || id >= this->tableSize) {
      return nullptr;
    }
    return this->table[hash(id)];
  }
};
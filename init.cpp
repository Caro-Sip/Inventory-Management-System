#include "Hashtable.h"
#include "file_io.cpp"
#include "vector.h"

HashTable table;
DoublyLinkedList *ls = new DoublyLinkedList;
vector<Product> vector_ls;

void init() {
  loadFromCSV(*ls);
  table.init(*ls);
  vector_ls.load(*ls);
}
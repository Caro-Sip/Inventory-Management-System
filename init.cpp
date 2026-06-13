#include "Hashtable.h"
#include "file_io.cpp"
#include "vector.h"
#include <vector>

HashTable table;
DoublyLinkedList *ls = new DoublyLinkedList;
Vector vector_ls;

void init() {
  loadFromCSV(*ls);
  table.init(*ls);
  vector_ls.init(*ls);
}
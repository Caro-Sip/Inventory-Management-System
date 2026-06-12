#include "Hashtable.h"
#include "file_io.cpp"

HashTable table;
DoublyLinkedList *ls = new DoublyLinkedList;
void init() {
  loadFromCSV(*ls);
  table.init(*ls);
}
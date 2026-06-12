#include "Product.h"

struct Element2 {
  Element2 *prev;
  Element2 *next;
  Product data;
};

struct Element {
  Element *next;
  Element2 *data;
};

class LinkedList {
protected:
  int size;
};
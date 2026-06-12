#include "Product.h"

struct Element {
  Element *next;
  Product data;
};

struct Element2 : Element {
  Element2 *prev;
};

class LinkedList {
public:
  virtual void add(Product Data) = 0;
  virtual void display() = 0;
};
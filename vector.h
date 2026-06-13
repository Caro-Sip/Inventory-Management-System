#pragma once

#include "LinkedList.h"
#include "Product.h"
#include <iomanip>
#include <vector>

using namespace std;

class Vector {
private:
  std::vector<Product> ls;

public:
  void init(DoublyLinkedList &ls) { update(ls); }
  std::vector<Product> &getVector() { return this->ls; }

  void update(DoublyLinkedList &ls) {
    this->ls.clear();
    Element2 *node = ls.getHead();
    while (node != nullptr) {
      this->ls.push_back(node->data);
      node = node->next;
    }
  }
  void display() {
    cout << endl;
    cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(10)
         << "Quantity" << setw(10) << "Price"
         << "\n";
    cout << string(40, '-') << "\n";

    for (Product x : this->ls) {

      cout << left << setw(5) << x.id << setw(15) << x.name << setw(10)
           << x.quantity << setw(10) << x.price << "\n";
    }
  }
};
#pragma once
#include "Product.h"
#include "LinkedList.h"
#include <fstream>
#include <sstream>

inline void loadFromCSV(DoublyLinkedList &ls) {
  std::ifstream file("Product.csv");
  std::string line;

  getline(file, line);

  while (getline(file, line)) {
    std::stringstream read(line);
    std::string id, name, quantity, price;

    getline(read, id, ',');
    getline(read, name, ',');
    getline(read, quantity, ',');
    getline(read, price, ',');

    Product data;
    data.id = stoi(id);
    data.name = name;
    data.quantity = stoi(quantity);
    data.price = stod(price);

    ls.add(data);
  }

  file.close();
}

inline void appendToCSV(Product data) {
  std::ofstream file("Product.csv", std::ios::app);
  file << data.id << "," << data.name << "," << data.quantity << ","
       << data.price << "\n";
  file.close();
}

inline void saveToCSV(DoublyLinkedList &ls) {
  std::ofstream file("Product.csv", std::ios::trunc);
  file << "id,name,quantity,price\n";
  file.close();

  Element2 *node = ls.getHead();
  while (node != nullptr) {
    appendToCSV(node->data);
    node = node->next;
  }
}

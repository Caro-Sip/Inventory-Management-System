#pragma once

#include "LinkedList.h"
#include <fstream>
#include <sstream>

void loadFromCSV(DoublyLinkedList &ls) {
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

void saveToCSV(DoublyLinkedList &ls) {
  std::ofstream file("Product.csv", std::ios::trunc);

  file << "id,name,quantity,price\n";

  Element2 *node = ls.getHead();
  while (node != nullptr) {
    file << node->data.id << "," << node->data.name << ","
         << node->data.quantity << "," << node->data.price << "\n";
    node = node->next;
  }

  file.close();
}
#pragma once

#include "Product.h"
#include <iomanip>
#include <iostream>


  void display(Element2 &data) {
    std::cout << std::left << std::setw(5) << data.data.id << std::setw(15)
              << data.data.name << std::setw(10) << data.data.quantity
              << std::setw(10) << data.data.price << "\n";
  }
};
#pragma once
#include "Product.h"
#include "vector.h"

bool byId(Product a, Product b);
bool byName(Product a, Product b);
bool byQuantity(Product a, Product b);
bool byPrice(Product a, Product b);

void merge(vector<Product> &arr, vector<Product> &left, vector<Product> &right,
           bool (*compare)(Product a, Product b));
void mergeSort(vector<Product> &arr, bool (*compare)(Product, Product));

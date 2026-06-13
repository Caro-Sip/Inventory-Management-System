#pragma once

#include "Product.h"
#include <vector>
using namespace std;

bool byId(Product a, Product b) { return (a.id < b.id); }
bool byName(Product a, Product b) { return (a.name < b.name); }
bool byQuantity(Product a, Product b) { return (a.quantity < b.quantity); }
bool byPrice(Product a, Product b) { return (a.price < b.price); }

void merge(vector<Product> &arr, vector<Product> &left, vector<Product> &right,
           bool (*compare)(Product a, Product b)) {
  int l = 0;
  int r = 0;
  int i = 0;

  while (l < left.size() && r < right.size()) {
    if ((*compare)(left[l], right[r])) {
      arr[i] = left[l];
      i++;
      l++;
    } else {
      arr[i] = right[r];
      i++;
      r++;
    }
  }
  while (l < left.size()) {
    arr[i] = left[l];
    i++;
    l++;
  }
  while (r < right.size()) {
    arr[i] = right[r];
    i++;
    r++;
  }
}

void mergeSort(vector<Product> &arr, bool (*compare)(Product a, Product b)) {
  int length = arr.size();
  if (length <= 1)
    return;
  int middle = length / 2;

  vector<Product> left(arr.begin(), arr.begin() + middle);
  vector<Product> right(arr.begin() + middle, arr.end());

  mergeSort(left, compare);
  mergeSort(right, compare);
  merge(arr, left, right, compare);
}
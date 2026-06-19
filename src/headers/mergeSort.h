#pragma once
#include "Product.h"
#include "vector.h"

inline bool byId(Product a, Product b) { return (a.id < b.id); }
inline bool byName(Product a, Product b) { return (a.name < b.name); }
inline bool byQuantity(Product a, Product b) { return (a.quantity < b.quantity); }
inline bool byPrice(Product a, Product b) { return (a.price < b.price); }

inline void merge(vector<Product> &arr, vector<Product> &left, vector<Product> &right,
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

inline void mergeSort(vector<Product> &arr, bool (*compare)(Product, Product)) {
  int length = arr.size();
  if (length <= 1)
    return;

  int middle = length / 2;

  vector<Product> left;
  vector<Product> right;

  for (int i = 0; i < middle; i++)
    left.push_back(arr[i]);

  for (int i = middle; i < length; i++)
    right.push_back(arr[i]);

  mergeSort(left, compare);
  mergeSort(right, compare);
  merge(arr, left, right, compare);
}

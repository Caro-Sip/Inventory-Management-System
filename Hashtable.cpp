#include <iostream>
#include "Linkedlist.h"
#include "Hashtable.h"

HashTable::HashTable() : table(BucketCount, nullptr) {}
// Distructor 
HashTable::~HashTable() {
    for (int i = 0; i < BucketCount; ++i) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
}
int HashTable::hash(int id) const {
    return (id < 0) ? (-id % BucketCount) : (id % BucketCount);
}
void HashTable::insert(int id,Element2* node){
    if(node == nullptr)return;
    int index = hash(id);
    HashNode *newNode = new HashNode(id,node);
    if(table[index] == nullptr){
        table[index] = newNode;
    }else{
        newNode->next = table[index];
        table[index] = newNode;
}
void HashTable::display() {
    for (int i = 0; i < BUCKET; i++) {
        cout << i;
        for (int x : table[i]) {
            cout << " --> " << x;
        }
        cout << endl;
    }
}
}

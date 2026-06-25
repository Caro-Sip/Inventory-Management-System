#pragma once

#include <cstdio>
#include "Product.h"
#include "LinkedList.h"

struct TreeNode{
    Product* data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Product* p){
        this->data = p;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class Tree{
private:
    TreeNode* root; 

    // clear function that performs on a LRD
    void clear(TreeNode* node){
        if(node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    TreeNode* insert(TreeNode* current, Product* p){
        if(current == nullptr){
            current = new TreeNode(p);
        }
        else if(p->price < current->data->price){
            current->left = insert(current->left, p);
        }
        else if(p->price >= current->data->price){
            current->right = insert(current->right, p);
        }
        
        return current;
    }

    void rangeSearch(TreeNode* node, double minPrice, double maxPrice){
        if (node == nullptr) return;

        if (node->data->price > minPrice) {
            rangeSearch(node->left, minPrice, maxPrice);
        }

        if(node->data->price >= minPrice && node->data->price <= maxPrice){
            printf("%-5d%-15s%-10d%-10.2f\n", 
                node->data->id, 
                node->data->name.c_str(), // Convert std::string to C-string
                node->data->quantity, 
                node->data->price);
        }

        if (node->data->price < maxPrice){
            rangeSearch(node->right, minPrice,maxPrice);
        }
    }

public:
    Tree(){
        root = nullptr;
    }

    ~Tree(){
        clear(root);
    }

    void insert(Product* p){
        root = insert(root, p);
    }

    void rangeSearch(double minPrice, double maxPrice) {
        printf("\n%-5s%-15s%-10s%-10s\n", "ID", "Name", "Quantity", "Price");
        printf("----------------------------------------\n");
        rangeSearch(root, minPrice, maxPrice);
    }

    void clear(){
        clear(root);
        root = nullptr;
    }

    void load(DoublyLinkedList* ls){
        clear();
        Element2* node = ls->getHead();
        while(node != nullptr){
            insert(&(node->data));
            node = node->next;
        }
    }
};
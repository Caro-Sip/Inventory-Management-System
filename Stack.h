#pragma once
#include "Product.h"
#include <string>

enum class action { Add, Update, Remove };

struct state {
    action type;
    Product before;  
    Product after;
};

class Stack {
private:
static const int Max = 100;
    state data[Max];
    int top = -1;

public:
bool isEmpty();
bool isFull();
    void push(state action) {
        if (!isFull()) {
            data[++top] = action;
        }
    }

    state pop() {
        return data[top--];
    }

    state peek() {
        return data[top];
    }
};
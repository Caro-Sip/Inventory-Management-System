#pragma once
#include "Product.h"
#include <string>
#include <iostream>

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
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == Max - 1;
    }

    void push(state action) {
        if (isFull()) {
            std::cout << "Undo history full\n";
            std::cout << "Are you sure? Type y/n:\n";

            std::string ans;
            std::cin >> ans;
            std::cin.ignore();

            if (ans == "y") {
                for (int i = 0; i < Max - 1; i++) {
                    data[i] = data[i + 1];
                }
                top--;
            } else {
                std::cout << "Action cancelled. History not updated.\n";
                return;
            }
        }
        data[++top] = action;
    }

    state pop() {
        return data[top--];
    }

    state peek() {
        return data[top];
    }
};
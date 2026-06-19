#include "Stack.h"
#include <iostream>
#include <string>

Stack::Stack() {
    top = -1;
}

bool Stack::isEmpty() {
    return top == -1;
}

bool Stack::isFull() {
    return top == Max - 1;
}

void Stack::push(state action) {
    if (isFull()) {
        std::cout << "Undo history full\n";
        std::cout << "Are you sure? Type y/n:\n";

        std::string ans;
        std::cin >> ans;   // <-- was missing
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
    data[++top] = action;  // <-- was missing in original too
}

state Stack::pop() {
    return data[top--];
}

state Stack::peek() {
    return data[top];
}
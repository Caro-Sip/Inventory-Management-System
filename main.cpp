#include <iostream>
#include <string>
#include "Stack.h"

class IMS {
    enum class MenuState {
        Main,
        ViewList,
        Exit,
    };

    MenuState currentState = MenuState::Main;
    Stack stack; 
public:
    void start() {
        while (currentState != MenuState::Exit) {
            switch (currentState) {
                case MenuState::Main:
                    handleMainMenu();
                    break;
                case MenuState::ViewList:
                    handleViewListMenu();
                    break;
                case MenuState::Exit:
                    break;
            }
        }
        std::cout << "Goodbye\n";
    }

private:
    void handleMainMenu() {
        std::cout << "\n=== Inventory Management System ===\n";
        std::cout << "1. View List\n";
        std::cout << "2. Add Item\n";
        std::cout << "3. Update Item\n";
        std::cout << "4. Remove Item\n";
        std::cout << "5. Review Restock\n";
        std::cout << "6. Undo\n";
        std::cout << "0. Quit\n";
        std::cout << "Enter option: ";

        std::string input;
        std::getline(std::cin, input);

        if (input == "1") {
            currentState = MenuState::ViewList;
        } else if (input == "2") {
            handleAddItem();
        } else if (input == "3") {
            handleUpdateItem();
        } else if (input == "4") {
            handleRemoveItem();
        } else if (input == "5") {
            handleRestockItem();
        } 
        else if(input == "6"){}

                else if (input == "0") {
            currentState = MenuState::Exit;
        }
        else {
            std::cout << "Invalid Option. Please try again.\n";
        }
    }

    void handleViewListMenu() {
        std::cout << "\n=== View List ===\n";
        handleViewList();
        std::cout << "\nPress Enter to return to main menu...";
        std::string input;
        std::getline(std::cin, input);
        
        currentState = MenuState::Main;
    }

    void handleViewList() {
        std::cout << "Unimplemented Method 1\n";
    }

    void handleAddItem() {
        std::cout << "Unimplemented Method 2\n";
    }

    void handleUpdateItem() {
        std::cout << "Unimplemented Method 3\n";
    }

    void handleRemoveItem() {
        std::cout << "Unimplemented Method 4\n";
    }

    void handleRestockItem() {
        std::cout << "Unimplemented Method 5\n";
    }
void handleUndo() {            
     
        if (stack.isEmpty()) {
            std::cout << "Nothing to undo.\n";
            return;
        }
        

        state LastAction = stack.pop(); 

        if (LastAction.type == action::Add) {
            std::cout << "ADDED \"" << LastAction.after.name << "\"\n";
        } else if (LastAction.type == action::Remove) {
            std::cout << "REMOVED\"" << LastAction.before.name << "\"\n";
        } else if (LastAction.type == action::Update) {
            std::cout << "UPDATED \"" << LastAction.after.name << "\"\n";
        }
    }
};




int main(){
    IMS ims;
    ims.start();
    return 0;
}


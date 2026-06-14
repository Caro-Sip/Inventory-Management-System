#include "Hashtable.cpp"
#include "Linkedlist.cpp"
#include "file_io.cpp"
#include "mergesort.cpp"
#include <iomanip>
#include <iostream>
#include <string>

DoublyLinkedList *ls = new DoublyLinkedList;
HashTable *table = new HashTable;

class IMS {
  enum class MenuState {
    Main,
    ViewList,
    Exit,
  };

  MenuState currentState = MenuState::Main;

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
    } else if (input == "0") {
      currentState = MenuState::Exit;
    } else {
      std::cout << "Invalid Option. Please try again.\n";
    }
  }

  void handleViewListMenu() {
    std::cout << "\n=== View List ===\n";
    std::cout << "1.id\n";
    std::cout << "2.name\n";
    std::cout << "3.quantity\n";
    std::cout << "4.price\n";
    std::cout << "0.back\n";
    std::cout << "Enter option: ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "1") {
      ls->setHead(ls->mergeSort(ls->getHead(), byId));
    } else if (input == "2") {
      ls->setHead(ls->mergeSort(ls->getHead(), byName));
    } else if (input == "3") {
      ls->setHead(ls->mergeSort(ls->getHead(), byQuantity));
    } else if (input == "4") {
      ls->setHead(ls->mergeSort(ls->getHead(), byPrice));
    } else if (input == "0") {
      currentState = MenuState::Main;
      return;
    } else {
      std::cout << "Invalid Option. Please try again.\n";
      return;
    }
    ls->display();
  }

  void handleAddItem() { std::cout << "Unimplemented Method 2\n"; }

  void handleUpdateItem() {
    std::cout << "\n=== update ===\n";
    std::cout << "id to update: ";
    int id;

    std::cin >> id;
    std::cin.ignore(10000, '\n');

    DoublyLinkedList::Element2 *node = table->search(id);

    if (node) {
      std::cout << "\n=== found ===\n";
      std::cout << std::left << std::setw(10) << node->data.id << std::setw(20)
                << node->data.name << std::setw(12) << node->data.quantity
                << std::setw(10) << node->data.price << "\n\n";

      std::string input;

      std::cout << "New name (" << node->data.name << "): ";
      std::getline(std::cin, input);
      if (!input.empty())
        node->data.name = input;

      std::cout << "New quantity (" << node->data.quantity << "): ";
      std::getline(std::cin, input);
      if (!input.empty())
        node->data.quantity = std::stoi(input);

      std::cout << "New price (" << node->data.price << "): ";
      std::getline(std::cin, input);
      if (!input.empty())
        node->data.price = std::stod(input);

      std::cout << "Updated successfully.\n";
    } else {
      std::cout << "Not found.\n";
    }
  }

  void handleRemoveItem() {
    std::cout << "\n=== Delete ===\n";
    std::cout << "id to Delete: ";
    int id;

    std::cin >> id;
    std::cin.ignore(10000, '\n');

    DoublyLinkedList::Element2 *node = table->search(id);

    if (node) {
      std::cout << "\n=== found ===\n";
      std::cout << std::left << std::setw(10) << node->data.id << std::setw(20)
                << node->data.name << std::setw(12) << node->data.quantity
                << std::setw(10) << node->data.price << "\n\n";

      std::cout << "yes/no: ";

      std::string choice;
      getline(std::cin, choice);
      if (choice == "yes") {
        table->remove(id);
        ls->removeNode(node);
        std::cout << "Deleted successfully.\n";
      } else {
        std::cout << "Deletion cancelled.\n";
      }
    } else {
      std::cout << "Not found.\n";
    }
  }

  void handleRestockItem() { std::cout << "Unimplemented Method 5\n"; }
};

int main() {
  loadFromCSV(*ls);
  table->load(ls);
  IMS ims;
  ims.start();
  saveToCSV(*ls);
  return 0;
}

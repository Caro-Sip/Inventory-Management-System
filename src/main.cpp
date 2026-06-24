#include "headers/Hashtable.h"
#include "headers/LinkedList.h"
#include "headers/Stack.h"
#include "headers/file_io.h"
#include "headers/mergeSort.h"
#include "queues.h"
#include "headers/vector.h"
#include <string>

HashTable table;
DoublyLinkedList *ls = new DoublyLinkedList;
vector<Product> vector_ls;

void reload() {
  vector_ls.clear();
  ls->clear();
  table.clear();

  loadFromCSV(*ls);
  table.init(*ls);
  vector_ls.load(*ls);
}

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
  Restock restockQueue;
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
    } else if (input == "6") {
      handleUndo();
    } else if (input == "0") {
      currentState = MenuState::Exit;
    } else {
      std::cout << "Invalid Option. Please try again.\n";
    }
  }

  void handleViewListMenu() {
    int choice;
    std::cout << "\n=== View By ===\n";
    std::cout << "1. id\n";
    std::cout << "2. name\n";
    std::cout << "3. price\n";
    std::cout << "4. quantity\n";
    std::cout << "0. back\n";
    std::cout << "choice: ";

    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1:
      mergeSort(vector_ls, byId);
      vector_ls.display();
      break;
    case 2:
      mergeSort(vector_ls, byName);
      vector_ls.display();
      break;
    case 3:
      mergeSort(vector_ls, byPrice);
      vector_ls.display();
      break;
    case 4:
      mergeSort(vector_ls, byQuantity);
      vector_ls.display();
      break;
    case 0:

      currentState = MenuState::Main;
      break;
    default:
      std::cout << "Invalid option.\n";
    }
  }

  void handleAddItem() {
    Product data;
    std::cout << "\n=== Add Item ===\n";
    std::cout << "name: ";
    std::getline(std::cin, data.name);
    std::cout << "price: ";
    std::cin >> data.price;
    std::cout << "quantity: ";
    std::cin >> data.quantity;
    std::cin.ignore();

    data.id = vector_ls.getAvailableId();
    Element2 *node = ls->add(data);
    vector_ls.push_back(data);
    appendToCSV(data);
    table.insert(node);

    state s;
    s.type = action::Add;
    s.after = data;
    stack.push(s);

    std::cout << "\n=== Item Added ===\n";
    std::cout << std::left << std::setw(5) << data.id << std::setw(15)
              << data.name << std::setw(10) << data.quantity << std::setw(10)
              << data.price << "\n";
  }

  void handleUpdateItem() {
    int id;
    std::cout << "\n=== Update Item ===\n";
    std::cout << "id: ";
    std::cin >> id;
    std::cin.ignore();

    Element2 *node = table.search(id);

    if (node) {
      state s;
      s.type = action::Update;
      s.before = node->data;

      std::cout << "\n=== Found ===\n";
      ls->display(*node);

      std::cout << "name (" << node->data.name << "): ";
      std::string name;
      std::getline(std::cin, name);
      if (!name.empty())
        node->data.name = name;

      std::cout << "price (" << node->data.price << "): ";
      std::string price;
      std::getline(std::cin, price);
      if (!price.empty())
        node->data.price = std::stod(price);

      std::cout << "quantity (" << node->data.quantity << "): ";
      std::string quantity;
      std::getline(std::cin, quantity);
      if (!quantity.empty())
        node->data.quantity = std::stoi(quantity);

      std::cout << "\n=== Item Updated ===\n";
      ls->display(*node);

      s.after = node->data;
      stack.push(s);

      saveToCSV(*ls);
      reload();

    } else {
      std::cout << "Item not found.\n";
    }
  }
  void handleRemoveItem() { std::cout << "Unimplemented Method 4\n"; }

  void handleRestockItem() {
    std::cout << "\n=== Restock Management ===\n";
    std::cout << "1. Display Item\n";
    std::cout << "2. Auto Restock\n";
    std::cout << "3. Restock by ID\n";
    std::cout << "0. Back\n";
    std::cout << "Enter option: ";

    std::string choice;
    std::getline(std::cin, choice);
    if (choice == "1") {
      displayLowQuantity();

    } else if (choice == "2") {
      autoRestockoption();

    } else if (choice == "3") {
      restockById();

    } else if (choice == "0") {
      return;
    } else {
      std::cout << "Invalid option.\n";
    }
  }
  void displayLowQuantity() {
    std::cout << "\n=== Option ===\n";
    mergeSort(vector_ls, byQuantity);
    vector_ls.display();
    std::cout << "\n--- Warning: ITEM needed to restock ---\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(15) << "Name"
              << "Current Qty\n";
    std::cout << "-------------------------------------------\n";
    for (Product x : vector_ls) {
      if (x.quantity < 5) {
        std::cout << std::left << std::setw(5) << x.id << std::setw(15)
                  << x.name << x.quantity << std::endl;
      } else {
        break;
      }
    }
  }

  void autoRestockoption() {
    while (!restockQueue.isEmpty()) {
      restockQueue.dequeue();
    }

    int lowCount = 0;
    for (size_t i = 0; i < vector_ls.size(); i++) {
      Product p = vector_ls[i];
      if (p.quantity < 5) {
        std::cout << std::left << std::setw(5) << p.id << std::setw(15)
                  << p.name << p.quantity << " (LOW)\n";
        restockQueue.enqueue(p);
        lowCount++;
      }
    }

    if (lowCount == 0) {
      std::cout << "All items are stocked.\n";
      return;
    }

    std::cout << "\n Found " << lowCount;

    while (!restockQueue.isEmpty()) {
      Product data = restockQueue.peek();
      std::cout << "\nProcessing ID" << data.id << data.name << data.quantity
                << std::endl;
      std::cout << "Enter new quantity (0 to skip, negative to stop queue): ";

      std::string input;
      std::getline(std::cin, input);
      if (input.empty())
        continue;

      int newQuantity = std::stoi(input);

      if (newQuantity < 0) {
        std::cout << "Queue processing halted.\n";
        break;
      }

      restockQueue.dequeue();

      if (newQuantity == 0) {
        std::cout << "Skipped \"" << data.name << "\".\n";
        continue;
      }

      Element2 *node = table.search(data.id);
      if (node) {
        state s;
        s.type = action::Update;
        s.before = node->data;

        node->data.quantity = newQuantity;

        s.after = node->data;
        stack.push(s);

        saveToCSV(*ls);
        reload();
        std::cout << "Successfully updated to " << newQuantity << "!\n";
      }
    }
  }

  void restockById() {

    std::cout << "\nEnter Product ID to restock: ";
    std::string idInput;
    std::getline(std::cin, idInput);
    if (idInput.empty())
      return;
    int targetId = std::stoi(idInput);

    Element2 *node = table.search(targetId);

    if (node) {
      std::cout << "Found: " << node->data.name
                << " | Current Qty: " << node->data.quantity << "\n";
      std::cout << "Enter added stock amount (e.g., write '10' to add 10 "
                   "more items): ";

      std::string qtyInput;
      std::getline(std::cin, qtyInput);
      if (qtyInput.empty())
        return;
      int addedQty = std::stoi(qtyInput);

      if (addedQty <= 0) {
        std::cout << "Invalid quantity amount. Aborted.\n";
        return;
      }

      state s;
      s.type = action::Update;
      s.before = node->data;

      node->data.quantity += addedQty;

      s.after = node->data;
      stack.push(s);

      saveToCSV(*ls);
      reload();

      std::cout << "\nUpdated \"" << node->data.name
                << "\" total stock to: " << node->data.quantity << "\n";
    } else {
      std::cout << "Error: Product ID " << targetId
                << " not found in system.\n";
    }
  }

  void handleUndo() {
    if (stack.isEmpty()) {
      std::cout << "Nothing to undo.\n";
      return;
    }

    state LastAction = stack.pop();

    if (LastAction.type == action::Add) {
      ls->remove(LastAction.after.id);
      std::cout << "Undid add: \"" << LastAction.after.name << "\"\n";
    } else if (LastAction.type == action::Update) {
      Element2 *node = table.search(LastAction.before.id);
      if (node)
        node->data = LastAction.before;
      std::cout << "Undid update: \"" << LastAction.after.name << "\"\n";
    } else if (LastAction.type == action::Remove) {
      ls->add(LastAction.before);
      std::cout << "Undid remove: \"" << LastAction.before.name << "\"\n";
    }

    saveToCSV(*ls);
    reload();
  }
};

int main() {
  loadFromCSV(*ls);
  table.init(*ls);
  vector_ls.load(*ls);

  IMS ims;
  ims.start();

  saveToCSV(*ls);
  delete ls;
  return 0;
}
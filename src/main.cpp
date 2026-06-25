#include "headers/Hashtable.h"
#include "headers/LinkedList.h"
#include "headers/Stack.h"
#include "headers/file_io.h"
#include "headers/mergeSort.h"
#include "headers/queues.h"
#include "headers/vector.h"
#include <string>
#include "headers/Tree.h"

enum class MenuState {
  Main,

  ViewList,
  ViewList_Id,
  ViewList_Name,
  ViewList_Price,
  ViewList_Quantity,

  AddItem,
  UpdateItem,
  RemoveItem,

  Restock,
  Restock_Display,
  Restock_Auto,
  Restock_Id,
  Order_Id,

  Undo,
  FilterByPrice,
};

HashTable table;
DoublyLinkedList *ls = new DoublyLinkedList;
vector<Product> vector_ls;
Stack<state> stack;
Stack<MenuState> navStack;
Restock restockQueue;
Tree priceTree;

void reload() {
  vector_ls.clear();
  ls->clear();
  table.clear();
  priceTree.clear();

  loadFromCSV(*ls);
  table.init(*ls);
  vector_ls.load(*ls);
  priceTree.load(ls);
}

class IMS {
public:
  void start() {
    navStack.push(MenuState::Main);

    while (!navStack.isEmpty()) {
      switch (navStack.peek()) {
      case MenuState::Main:
        handleMainMenu();
        break;
      case MenuState::ViewList:
        handleViewListMenu();
        break;
      case MenuState::AddItem:
        handleAddItem();
        break;
      case MenuState::UpdateItem:
        handleUpdateItem();
        break;
      case MenuState::RemoveItem:
        handleRemoveItem();
        break;
      case MenuState::Restock:
        handleRestock();
        break;
      case MenuState::Restock_Display:
        handleRestockDisplay();
        break;
      case MenuState::Restock_Auto:
        handleRestockAuto();
        break;
      case MenuState::Restock_Id:
        handleRestockById();
        break;
      case MenuState::Order_Id:
        handleOrderById();
        break;
      case MenuState::Undo:
        handleUndo();
        break;
      case MenuState::FilterByPrice:
        handleFilterByPrice();
        break;
      default:
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
    std::cout << "6. Order Item\n";
    std::cout << "7. Undo\n";
    std::cout << "8. Filter by Price Range\n";
    std::cout << "0. Quit\n";
    std::cout << "Enter option: ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "1")
      navStack.push(MenuState::ViewList);
    else if (input == "2")
      navStack.push(MenuState::AddItem);
    else if (input == "3")
      navStack.push(MenuState::UpdateItem);
    else if (input == "4")
      navStack.push(MenuState::RemoveItem);
    else if (input == "5")
      navStack.push(MenuState::Restock);
    else if (input == "6")
      navStack.push(MenuState::Order_Id);
    else if (input == "7")
      navStack.push(MenuState::Undo);
    else if (input == "8")
      navStack.push(MenuState::FilterByPrice);
    else if (input == "0")
      navStack.pop();
    else
      std::cout << "Invalid Option. Please try again.\n";
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
      navStack.pop();
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
    priceTree.insert(&node->data);

    state s;
    s.type = action::Add;
    s.after = data;
    stack.push(s);

    std::cout << "\n=== Item Added ===\n";
    std::cout << std::left << std::setw(5) << data.id << std::setw(15)
              << data.name << std::setw(10) << data.quantity << std::setw(10)
              << data.price << "\n";

    navStack.pop();
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

    navStack.pop();
  }

  void handleRemoveItem() {
     int id;
    std::cout << "\n=== Delete Item ===\n";
    std::cout << "id: ";
    std::cin >> id;
    std::cin.ignore();

    Element2 *node = table.search(id);

    // node != nullptr == true
    if (node) {
      state s;
      s.type = action::Remove;
      s.before = node->data;

      std::cout << "\n=== Found ===\n";
      ls->display(*node);

      std::cout << "name (" << node->data.name << "): ";
      std::cout << "price (" << node->data.price << "): ";
      std::cout << "quantity (" << node->data.quantity << "): ";

      std::cout << "\n=== Item Deleted ===\n";
      s.after = node->data;
      ls->remove(id);
      stack.push(s);
      saveToCSV(*ls);
      reload();
    } else {
      // node == nullptr == false
      std::cout << "Item not found.\n";
    }
    navStack.pop();
  }

  void handleRestock() {
    std::cout << "\n=== Restock Management ===\n";
    std::cout << "1. Display Item\n";
    std::cout << "2. Auto Restock\n";
    std::cout << "3. Restock by ID\n";
    std::cout << "0. Back\n";
    std::cout << "Enter option: ";

    std::string choice;
    std::getline(std::cin, choice);

    if (choice == "1")
      navStack.push(MenuState::Restock_Display);
    else if (choice == "2")
      navStack.push(MenuState::Restock_Auto);
    else if (choice == "3")
      navStack.push(MenuState::Restock_Id);
    else if (choice == "0")
      navStack.pop();
    else
      std::cout << "Invalid option.\n";
  }

  void handleRestockDisplay() {
    std::cout << "\n=== Low Stock Items ===\n";
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

    navStack.pop();
  }

  void handleRestockAuto() {
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
      navStack.pop();
      return;
    }

    std::cout << "\nFound " << lowCount << " low stock items.\n";

    while (!restockQueue.isEmpty()) {
      Product data = restockQueue.peek();
      std::cout << "\nProcessing ID" << data.id << " " << data.name
                << " qty:" << data.quantity << std::endl;
      std::cout << "Enter new quantity (0 to skip, negative to stop queue): ";

      std::string input;
      std::getline(std::cin, input);
      if (input.empty()) {
        restockQueue.dequeue();
        continue;
      }

      int addedQuantity = std::stoi(input);

      if (addedQuantity < 0) {
        std::cout << "Queue processing halted.\n";
        break;
      }

      restockQueue.dequeue();

      if (addedQuantity == 0) {
        std::cout << "Skipped \"" << data.name << "\".\n";
        continue;
      }

      Element2 *node = table.search(data.id);
      if (node) {
        state s;
        s.type = action::Update;
        s.before = node->data;

        node->data.quantity += addedQuantity;

        s.after = node->data;
        stack.push(s);

        saveToCSV(*ls);
        reload();
        std::cout << "Successfully restocked by " << addedQuantity << "!\n";
      }
    }

    navStack.pop();
  }

  void handleRestockById() {
    std::cout << "\nEnter Product ID to restock: ";
    std::string idInput;
    std::getline(std::cin, idInput);
    if (idInput.empty()) {
      navStack.pop();
      return;
    }
    int targetId = std::stoi(idInput);

    Element2 *node = table.search(targetId);

    if (node) {
      std::cout << "Found: " << node->data.name
                << " | Current Qty: " << node->data.quantity << "\n";
      std::cout << "Enter added stock amount (e.g., write '10' to add 10 more "
                   "items): ";

      std::string qtyInput;
      std::getline(std::cin, qtyInput);
      if (qtyInput.empty()) {
        navStack.pop();
        return;
      }
      int addedQty = std::stoi(qtyInput);

      if (addedQty <= 0) {
        std::cout << "Invalid quantity amount. Aborted.\n";
        navStack.pop();
        return;
      }

      state s;
      s.type = action::Update;
      s.before = node->data;

      node->data.quantity += addedQty;

      s.after = node->data;
      stack.push(s);

      std::string updatedName = node->data.name;
      int updatedQuantity = node->data.quantity;

      saveToCSV(*ls);
      reload();

      std::cout << "\nUpdated \"" << updatedName
                << "\" total stock to: " << updatedQuantity << "\n";
    } else {
      std::cout << "Error: Product ID " << targetId
                << " not found in system.\n";
    }

    navStack.pop();
  }

  void handleOrderById() {
    std::cout << "\nEnter Product ID to order: ";
    std::string idInput;
    std::getline(std::cin, idInput);
    if (idInput.empty()) {
      navStack.pop();
      return;
    }
    int targetId = std::stoi(idInput);

    Element2 *node = table.search(targetId);

    if (node) {
      std::cout << "Found: " << node->data.name
                << " | Current Qty: " << node->data.quantity << "\n";
      std::cout << "Enter quantity to order: ";

      std::string qtyInput;
      std::getline(std::cin, qtyInput);
      if (qtyInput.empty()) {
        navStack.pop();
        return;
      }
      int orderedQty = std::stoi(qtyInput);

      if (orderedQty <= 0 || orderedQty > node->data.quantity) {
        std::cout << "Invalid quantity amount. Aborted.\n";
        navStack.pop();
        return;
      }

      state s;
      s.type = action::Update;
      s.before = node->data;

      node->data.quantity -= orderedQty;

      s.after = node->data;
      stack.push(s);

      std::string updatedName = node->data.name;
      int updatedQuantity = node->data.quantity;

      saveToCSV(*ls);
      reload();

      std::cout << "\nUpdated \"" << updatedName
                << "\" total stock to: " << updatedQuantity << "\n";
    } else {
      std::cout << "Error: Product ID " << targetId
                << " not found in system.\n";
    }

    navStack.pop();
  }

  void handleUndo() {
    if (stack.isEmpty()) {
      std::cout << "Nothing to undo.\n";
      navStack.pop();
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

    navStack.pop();
  }

  void handleFilterByPrice(){
    double minPrice, maxPrice;
    std::cout << "\n=== Filter by Price Range ===\n";
    std::cout << "Enter minimum price: ";
    std::cin >> minPrice;
    std::cout << "Enter maximum price: ";
    std::cin >> maxPrice;
    std::cin.ignore(); 
    if (minPrice > maxPrice) {
        std::cout << "Error: Minimum price cannot be greater than maximum price.\n";
    } else {
        priceTree.rangeSearch(minPrice, maxPrice);
    }
    navStack.pop(); 
  }
};

int main() {
  loadFromCSV(*ls);
  table.init(*ls);
  vector_ls.load(*ls);
  priceTree.load(ls);

  IMS ims;
  ims.start();

  saveToCSV(*ls);
  delete ls;
  return 0;
}
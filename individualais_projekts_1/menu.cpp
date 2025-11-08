#include "menu.h"
#include <iostream>
using namespace std;

void showMainMenu() {
  cout << "=============================================\n";
  cout << "            WELCOME TO STORE SYSTEM          \n";
  cout << "=============================================\n";
  cout << "MAIN MENU\n";
  cout << "---------------------------------------------\n";
  cout << "1. View data\n";
  cout << "2. Add Data\n";
  cout << "3. Edit Data\n";
  cout << "4. Remove Data\n";
  cout << "5. Search Receipt\n";
  cout << "6. Sorting\n";
  cout << "7. Save and Exit\n";
  cout << "---------------------------------------------\n";
  cout << "Your choice: ";
}

void showViewDataSubMenu() {
  cout << endl;
  cout << "MAIN MENU selected item: VIEW DATA\n";
  cout << "-----------------------------------\n";
  cout << "1. View all data\n";
  cout << "2. View part of data\n";
  cout << "3. Return to Main Menu\n";
  cout << "------------------------------------\n";
  cout << "Your choice: ";
}

void showViewPartDataSubMenu() {
  cout << endl;
  cout << "VIEW DATA selected item: VIEW PART OF DATA\n";
  cout << "------------------------------------------\n";
  cout << "1. View Products\n";
  cout << "2. View Employees\n";
  cout << "3. View Discount Cards\n";
  cout << "4. View Receipts\n";
  cout << "5. Return to View Data\n";
  cout << "------------------------------------------\n";
  cout << "Your choice: ";
}

void showAddDataSubMenu() {
  cout << endl;
  cout << "MAIN MENU selected item: ADD DATA\n";
  cout << "---------------------------------\n";
  cout << "1. Add Product\n";
  cout << "2. Add Employee\n";
  cout << "3. Add Discount Card\n";
  cout << "4. Add Receipt\n";
  cout << "5. Return to Main Menu\n";
  cout << "---------------------------------\n";
  cout << "Your choice: ";
}

void showEditDataMenu() {
  cout << endl;
  cout << "MAIN MENU selected item: EDIT DATA\n";
  cout << "----------------------------------\n";
  cout << "1. Edit Products\n";
  cout << "2. Edit Employees\n";
  cout << "3. Edit Discount Cards\n";
  cout << "4. Edit Receipts\n";
  cout << "5. Return to Main Menu\n";
  cout << "----------------------------------\n";
  cout << "Your choice: ";
}

void showRemoveDataMenu() {
  cout << endl;
  cout << "MAIN MENU selected item: REMOVE DATA\n";
  cout << "------------------------------------\n";
  cout << "1. Remove Products\n";
  cout << "2. Remove Employees\n";
  cout << "3. Remove Discount Cards\n";
  cout << "4. Remove Receipts\n";
  cout << "5. Return to Main Menu\n";
  cout << "------------------------------------\n";
  cout << "Your choice: ";
}

void showSortDataMenu() {
  cout << endl;
  cout << "MAIN MENU selected item: SORTING\n";
  cout << "--------------------------------\n";
  cout << "1. Product by name\n";
  cout << "2. Product by price\n";
  cout << "3. Product price descending\n";
  cout << "4. Product by quantity\n";
  cout << "5. Product quantity descending\n";
  cout << "6. Return to Main Menu\n";
  cout << "--------------------------------\n";
  cout << "Your choice: ";
}

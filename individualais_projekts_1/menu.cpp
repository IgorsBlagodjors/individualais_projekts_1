#include <iostream>
#include "menu.h"
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
    cout << "4. Delete Data\n";
    cout << "5. Search\n";
    cout << "6. Exit\n";
    cout << "---------------------------------------------\n";
    cout << "Your choice: ";
}

void showViewDataSubMenu() {
    cout << endl;
    cout << "MAIN MENU selected item: VIEW DATA\n";
    cout << "-----------------------------------------------------------\n";
    cout << "1. View all data\n";
    cout << "2. View part of data\n";
    cout << "3. Return to Main Menu\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Your choice: ";
}

void showViewPartDataSubMenu()
{
    
    cout << endl;
    cout << "VIEW DATA selected item: VIEW PART OF DATA\n";
    cout << "-----------------------------------------------------------\n";
    cout << "1. View Products \n";
    cout << "2. View Employees\n";
    cout << "3. View Receipts\n";
    cout << "4. View DiscountCards\n";
    cout << "5. Return to View Data\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Your choice: ";
}

#include <iostream>
#include "menu.h"
using namespace std;

void showMenu() {
    cout << "===== Store Management Menu =====" << endl;
    cout << "1. Display " << endl;
    cout << "5. Add Data" << endl;
    cout << "6. Edit Data" << endl;
    cout << "7. Delete Data" << endl;
    cout << "8. Search Data" << endl;
    cout << "9. Sort Data" << endl;
    cout << "10. Calculations" << endl;
    cout << "0. Save and Exit" << endl;
    cout << "Select option: ";
}

void displayMenu(){
    cout  << endl;
    cout << "===== Display Menu =====" << endl;
    cout << "1. Display All" << endl;
    cout << "2. Display Products" << endl;
    cout << "3. Display Employees" << endl;
    cout << "4. Display Clients" << endl;
    cout << "5. Display Purchases" << endl;
    cout << "0. Return to Main Menu" << endl;
    cout << "Select option: ";
}

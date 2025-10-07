#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include "Function.h"
#include "FakeData.h"
#include "menu.h"
#include "dataView.h"
int main() {

    saveProducts(products, 20, "products.txt");
    saveEmployees(employees, 5, "employees.txt");
    saveDiscountCards(cards, 4, "discountCards.txt");
    saveReceipts(receipts, 4, "Receipts.txt");
    cout << "Data has been saved to files!" << endl;

    int choice;
    do {
        showMainMenu();
        cin >> choice;
        switch (choice) {
        case 1: {
            int viewDataSubMenuChoise;
            do {
                showViewDataSubMenu();
                cin >> viewDataSubMenuChoise;     
                switch (viewDataSubMenuChoise) {
                    case 1:
                    loadAndDisplayEmployees("employees.txt");
					break;
                    case 2: 
						int viewPartDataSubMenuChoise;   
                        do {
                        showViewPartDataSubMenu(); 
                        cin >> viewPartDataSubMenuChoise;
                        switch (viewPartDataSubMenuChoise) {
                        case 1:
                            loadAndDisplayEmployees("employees.txt");
                            break;
                        case 2: showViewPartDataSubMenu();
                            break;               
                        }
                        cout << endl;
                    } while (viewPartDataSubMenuChoise != 4);
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                }
                cout << endl;
            } while (viewDataSubMenuChoise != 3);
            break;
        }
        case 6: break;
        default:
            cout << "Invalid choice!" << endl;
        }
        cout << endl;
    } while (choice != 6);
    return 0;
}

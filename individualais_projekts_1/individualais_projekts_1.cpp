#include <iostream>
#include "Function.h"
#include "FakeData.h"
#include "menu.h"
using namespace std;

int main() {
	//initialize data from FakeData.h
    saveProducts(products, 20, "products.txt");
    saveEmployees(employees, 5, "employees.txt");
    saveClients(clients, 4, "clients.txt");
    savePurchases(purchases, 4, "purchases.txt");
    cout << "Data has been saved to files!" << endl;
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            int displayChoice;
            do {
                displayMenu();
                cin >> displayChoice;

                switch (displayChoice) {
                case 0:
                    cout << "Returning to main menu..." << endl;
                    break;  
                default:
                    cout << "Invalid choice!" << endl;
                }

                cout << endl;

            } while (displayChoice != 0);
            break;
        }

        case 5:
           
        case 6:
            
        case 7:
           
        case 8:
            
        case 9:
            
        case 10:   
        case 0:
            saveProducts(products, 20, "products.txt");
            saveEmployees(employees, 5, "employees.txt");
            saveClients(clients, 4, "clients.txt");
            savePurchases(purchases, 4, "purchases.txt");
            cout << "Data has been saved to files!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }

        cout << endl;

    } while (choice != 0);

    return 0;
}

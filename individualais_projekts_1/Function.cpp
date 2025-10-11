#include "Function.h"
#include <fstream>
#include <iomanip>
#include "menu.h"
#include <iostream>
#include "dataView.h"
using namespace std;

void saveProducts(const Product* arr, int size, const char* filename) {
    std::ofstream file(filename);
    file << "[\n";
    for (int i = 0; i < size; i++) {
        file << "  {\n"
            << "    \"code\": " << arr[i].code << ",\n"
            << "    \"name\": \"" << arr[i].name << "\",\n"
            << "    \"price\": " << arr[i].price << ",\n"
            << "    \"quantityInStock\": " << arr[i].quantityInStock << ",\n"
            << "    \"category\": \"" << categoryToChar(arr[i].category) << "\"\n"
            << "  }";
        if (i < size - 1) file << ",";
        file << "\n";
    }
    file << "]";
}

void saveEmployees(const Employee* arr, int size, const char* filename) {
    std::ofstream file(filename);
    file << "[\n";
    for (int i = 0; i < size; i++) {
        file << "  {\n"
            << "    \"id\": " << arr[i].id << ",\n"
            << "    \"firstName\": \"" << arr[i].firstName << "\",\n"
            << "    \"lastName\": \"" << arr[i].lastName << "\",\n"
            << "    \"department\": \"" << categoryToChar(arr[i].department) << "\"\n"
            << "  }";
        if (i < size - 1) file << ",";
        file << "\n";
    }
    file << "]";
}

void saveDiscountCards(const DiscountCard* arr, int size, const char* filename) {
    std::ofstream file(filename);
    file << "[\n";
    for (int i = 0; i < size; i++) {
        file << "  {\n"
            << "    \"cardNumber\": " << arr[i].cardNumber << ",\n"
            << "    \"ownerFirstName\": \"" << arr[i].ownerFirstName << "\",\n"
            << "    \"ownerLastName\": \"" << arr[i].ownerLastName << "\",\n"
            << "    \"type\": \"" << cardToChar(arr[i].type) << "\"\n"
            << "  }";
        if (i < size - 1) file << ",";
        file << "\n";
    }
    file << "]";
}

void saveReceipts(const Receipt* arr, int size, const char* filename) {
    std::ofstream file(filename);
    file << "[\n";
    for (int i = 0; i < size; i++) {
        double totalNoDiscount = arr[i].getTotalNoDiscount();
        double totalWithDiscount = arr[i].getTotalWithDiscount();
        double vat = arr[i].getVAT();

        file << "  {\n"
            << "    \"receiptNumber\": " << arr[i].receiptNumber << ",\n"
            << "    \"date\": \"" << arr[i].date << "\",\n"
            << "    \"product\": \"" << arr[i].product.name << "\",\n"
            << "    \"quantity\": " << arr[i].quantity << ",\n"
            << "    \"price\": " << arr[i].product.price << ",\n"
            << "    \"total_no_discount\": " << totalNoDiscount << ",\n"
            << "    \"total_with_discount\": " << totalWithDiscount << ",\n"
            << "    \"VAT\": " << vat << ",\n"
            << "    \"discountCard\": \"" << arr[i].card.cardNumber << "\"\n"
            << "  }";
        if (i < size - 1) file << ",";
        file << "\n";
    }
    file << "]";
}

void runProgramMenu()
{
    int choice;
    do {
        showMainMenu();
        cin >> choice;
        switch (choice) {
        case 1: {
            int viewChoice;
            do {
                showViewDataSubMenu();
                cin >> viewChoice;
                switch (viewChoice) {
                case 1:
                    loadAndDisplayFullDataResponse();
                    break;
                case 2: {
                    int subChoice;
                    do {
                        showViewPartDataSubMenu();
                        cin >> subChoice;
                        switch (subChoice) {
                        case 1:
                            loadAndDisplayProduct("products.txt");
                            break;
                        case 2:
                            loadAndDisplayEmployees("employees.txt");
                            break;
                        case 3:
                            loadAndDisplayReceipt("Receipts.txt");
                            break;
                        case 4:
                            loadAndDisplayDiscountCard("discountCards.txt");
                            break;
                        }
                        cout << endl;
                    } while (subChoice != 5);
                    break;
                }
                default:
                    cout << "Invalid choice!" << endl;
                }
                cout << endl;
            } while (viewChoice != 3);
            break;
        }
        case 6:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
        cout << endl;
    } while (choice != 6);
}

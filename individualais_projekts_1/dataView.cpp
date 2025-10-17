#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "dataView.h"
#include "dataTypes.h"
#include "globals.h"

using namespace std;


void displayFullDataResponse()
{
    displayProducts(loadedProducts, loadedProductCount);
	cout << endl;
    displayEmployees(loadedEmployees, loadedEmployeeCount);
    cout << endl;
    displayDiscountCards(loadedCards, loadedCardCount);
    cout << endl;
    displayReceipts(loadedReceipts, loadedReceiptCount);
    cout << endl;
}

void displayEmployees(const Employee* arr, int size) {
    cout << "=================== EMPLOYEES ===================" << endl;
    cout << left << setw(5) << "N"
        << setw(15) << "First name"
        << setw(15) << "Last name"
        << setw(15) << "Department" << endl;
    cout << "-------------------------------------------------" << endl;

    for (int i = 0; i < size; i++) {
        cout << left << setw(5) << i + 1
            << setw(15) << arr[i].firstName
            << setw(15) << arr[i].lastName
            << setw(15) << categoryToChar(arr[i].department) 
            << endl;
    }
    cout << "=================================================" << endl;
}

void displayProducts(const Product* arr, int size) {
    cout << "================================ PRODUCTS ================================" << endl;
    cout << left
        << setw(5) << "N"
        << setw(10) << "Code"
        << setw(25) << "Name"
        << setw(10) << "Price"
        << setw(15) << "Quantity"
        << setw(15) << "Category" << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    for (int i = 0; i < size; i++) {
        cout << left
            << setw(5) << i + 1
            << setw(10) << arr[i].code
            << setw(25) << arr[i].name
            << setw(10) << fixed << setprecision(2) << arr[i].price
            << setw(15) << arr[i].quantityInStock
            << setw(15) << categoryToChar(arr[i].category)
            << endl;
    }
    cout << "===============================================================================" << endl;
}

void displayDiscountCards(const DiscountCard* arr, int size) {
    cout << "===================== DISCOUNT CARDS =====================" << endl;
    cout << left
        << setw(5) << "N"
        << setw(15) << "Card Number"
        << setw(15) << "First Name"
        << setw(15) << "Last Name"
        << setw(15) << "Type" << endl;
    cout << "----------------------------------------------------------" << endl;

    for (int i = 0; i < size; i++) {
        cout << left
            << setw(5) << i + 1
            << setw(15) << arr[i].cardNumber
            << setw(15) << arr[i].ownerFirstName
            << setw(15) << arr[i].ownerLastName
            << setw(15) << cardToChar(arr[i].type)
            << endl;
    }
    cout << "==========================================================" << endl;
}

void displayReceipts(const Receipt* arr, int size) {
    cout << "====================================================== RECEIPTS ======================================================" << endl;
    cout << left
        << setw(5) << "N"
        << setw(12) << "Receipt#"
        << setw(12) << "Date"
        << setw(22) << "Product"
        << setw(8) << "Qty"
        << setw(10) << "Price"
        << setw(16) << "Total (no disc)"
        << setw(16) << "Total (disc)"
        << setw(10) << "VAT"
        << setw(12) << "Card#" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < size; i++) {
        cout << left
            << setw(5) << i + 1
            << setw(12) << arr[i].receiptNumber
            << setw(12) << arr[i].date
            << setw(22) << arr[i].product.name
            << setw(8) << arr[i].quantity
            << setw(10) << fixed << setprecision(2) << arr[i].product.price
            << setw(16) << fixed << setprecision(2) << arr[i].getTotalNoDiscount()
            << setw(16) << fixed << setprecision(2) << arr[i].getTotalWithDiscount()
            << setw(10) << fixed << setprecision(2) << arr[i].getVAT()
            << setw(12) << arr[i].card.cardNumber
            << endl;
    }

    cout << "=======================================================================================================================" << endl;
}

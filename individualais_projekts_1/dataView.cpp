#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "dataView.h"
using namespace std;

void loadAndDisplayFullDataResponse() {
    cout << "\n\n======================= FULL DATA REPORT =======================\n\n";

    loadAndDisplayEmployees("employees.txt");
    cout << endl;

    loadAndDisplayProduct("products.txt");
    cout << endl;

    loadAndDisplayDiscountCard("discountCards.txt");
    cout << endl;

    loadAndDisplayReceipt("receipts.txt");
    cout << "\n===================== END OF REPORT =====================\n";
}

void loadAndDisplayEmployees(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: cannot open " << filename << endl;
        return;
    }

    cout << "=================== EMPLOYEES ===================" << endl;
    cout << left << setw(5) << "N"
        << setw(15) << "First name"
        << setw(15) << "Last name"
        << setw(15) << "Department" << endl;
    cout << "-------------------------------------------------" << endl;

    string line;
    string firstName, lastName, department;
    int index = 1;

    while (getline(file, line)) {
        if (line.find("\"firstName\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            firstName = line.substr(start, end - start);
        }
        else if (line.find("\"lastName\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            lastName = line.substr(start, end - start);
        }
        else if (line.find("\"department\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            department = line.substr(start, end - start);

            cout << left << setw(5) << index++
                << setw(15) << firstName
                << setw(15) << lastName
                << setw(15) << department << endl;
        }
    }

    cout << "=================================================" << endl;
    file.close();
}

void loadAndDisplayProduct(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: cannot open " << filename << endl;
        return;
    }

    cout << "================================ PRODUCTS ================================" << endl;
    cout << left
        << setw(5) << "N"
        << setw(10) << "Code"
        << setw(25) << "Name"
        << setw(10) << "Price"
        << setw(15) << "Quantity"
        << setw(15) << "Category" << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    string line;
    string name, category;
    int code = 0, quantity = 0;
    double price = 0.0;
    int index = 1;

    while (getline(file, line)) {
        if (line.find("\"code\"") != string::npos) {
            auto start = line.find(":") + 1;
            code = stoi(line.substr(start));
        }
        else if (line.find("\"name\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            name = line.substr(start, end - start);
        }
        else if (line.find("\"price\"") != string::npos) {
            auto start = line.find(":") + 1;
            price = stod(line.substr(start));
        }
        else if (line.find("\"quantityInStock\"") != string::npos) {
            auto start = line.find(":") + 1;
            quantity = stoi(line.substr(start));
        }
        else if (line.find("\"category\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            category = line.substr(start, end - start);

            cout << left
                << setw(5) << index++
                << setw(10) << code
                << setw(25) << name
                << setw(10) << fixed << setprecision(2) << price
                << setw(15) << quantity
                << setw(15) << category
                << endl;
        }
    }

    cout << "===============================================================================" << endl;
    file.close();
}

void loadAndDisplayDiscountCard(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: cannot open " << filename << endl;
        return;
    }

    cout << "===================== DISCOUNT CARDS =====================" << endl;
    cout << left
        << setw(5) << "N"
        << setw(15) << "Card Number"
        << setw(15) << "First Name"
        << setw(15) << "Last Name"
        << setw(15) << "Type" << endl;
    cout << "----------------------------------------------------------" << endl;

    string line;
    int cardNumber = 0;
    string ownerFirstName, ownerLastName, type;
    int index = 1;

    while (getline(file, line)) {
        if (line.find("\"cardNumber\"") != string::npos) {
            auto start = line.find(":") + 1;
            cardNumber = stoi(line.substr(start));
        }
        else if (line.find("\"ownerFirstName\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            ownerFirstName = line.substr(start, end - start);
        }
        else if (line.find("\"ownerLastName\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            ownerLastName = line.substr(start, end - start);
        }
        else if (line.find("\"type\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            type = line.substr(start, end - start);

            cout << left
                << setw(5) << index++
                << setw(15) << cardNumber
                << setw(15) << ownerFirstName
                << setw(15) << ownerLastName
                << setw(15) << type
                << endl;
        }
    }

    cout << "==========================================================" << endl;
    file.close();
}

void loadAndDisplayReceipt(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: cannot open " << filename << endl;
        return;
    }

    cout << "=============================================== RECEIPTS ===============================================" << endl;
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
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    string line;
    int receiptNumber = 0, quantity = 0;
    double price = 0.0, totalNoDiscount = 0.0, totalWithDiscount = 0.0, vat = 0.0;
    string date, product, discountCard;
    int index = 1;

    while (getline(file, line)) {
        if (line.find("\"receiptNumber\"") != string::npos) {
            auto start = line.find(":") + 1;
            receiptNumber = stoi(line.substr(start));
        }
        else if (line.find("\"date\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            date = line.substr(start, end - start);
        }
        else if (line.find("\"product\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            product = line.substr(start, end - start);
        }
        else if (line.find("\"quantity\"") != string::npos) {
            auto start = line.find(":") + 1;
            quantity = stoi(line.substr(start));
        }
        else if (line.find("\"price\"") != string::npos) {
            auto start = line.find(":") + 1;
            price = stod(line.substr(start));
        }
        else if (line.find("\"total_no_discount\"") != string::npos) {
            auto start = line.find(":") + 1;
            totalNoDiscount = stod(line.substr(start));
        }
        else if (line.find("\"total_with_discount\"") != string::npos) {
            auto start = line.find(":") + 1;
            totalWithDiscount = stod(line.substr(start));
        }
        else if (line.find("\"VAT\"") != string::npos) {
            auto start = line.find(":") + 1;
            vat = stod(line.substr(start));
        }
        else if (line.find("\"discountCard\"") != string::npos) {
            auto start = line.find("\"", line.find(":")) + 1;
            auto end = line.find_last_of("\"");
            discountCard = line.substr(start, end - start);

           
            cout << left
                << setw(5) << index++
                << setw(12) << receiptNumber
                << setw(12) << date
                << setw(22) << product
                << setw(8) << quantity
                << setw(10) << fixed << setprecision(2) << price
                << setw(16) << fixed << setprecision(2) << totalNoDiscount
                << setw(16) << fixed << setprecision(2) << totalWithDiscount
                << setw(10) << fixed << setprecision(2) << vat
                << setw(12) << discountCard
                << endl;
        }
    }

    cout << "=========================================================================================================" << endl;
    file.close();
}

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "dataView.h"
using namespace std;
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


void loadAndDisplayProduct(const char* filename)
{
}

void loadAndDisplayDiscountCard(const char* filename)
{
}

void loadAndDisplayReceipt(const char* filename)
{
}

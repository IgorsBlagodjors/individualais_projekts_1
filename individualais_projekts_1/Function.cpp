#include "Function.h"
#include <algorithm>
#include <cctype>
#include <cstring>
#include <limits>
#include <regex>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include "menu.h"
#include <iostream>
#include "dataView.h"
#include "globals.h"
using namespace std;

// =============================== HELPER FUNCTIONS ===============================

namespace {
void copyToBuffer(char* destination, size_t destinationSize, const string& value) {
    if (destinationSize == 0) {
        return;
    }

    std::strncpy(destination, value.c_str(), destinationSize - 1);
    destination[destinationSize - 1] = '\0';
}
} // namespace

// Input int validation for numbers
static int intValidator(const string& prompt, bool allowZeroAsCancel = false) {
    int code;

    cout << prompt;

    while (true) {
        if (cin >> code) {
            if (code == 0 && allowZeroAsCancel) {
                cout << "\033[33mOperation cancelled.\033[0m\n";
                return 0;
            }
            if (code > 0 && code <= 9999) {
                cin.ignore(1000, '\n'); 
                return code;
            }
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number from 1 to 9999: \033[0m";
    }
}

// Input double validation for numbers
static double doubleValidator(const string& prompt, bool allowZeroAsCancel = false) {
    double code;

    cout << prompt;

    while (true) {
        if (cin >> code) {
            if (code == 0 && allowZeroAsCancel) {
                cout << "\033[33mOperation cancelled.\033[0m\n";
                return 0;
            }
            if (code > 0 && code <= 9999) {
                cin.ignore(1000, '\n');
                return code;
            }
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number from 1 to 9999: \033[0m";
    }
}

// Function for safe input of a string into a char
static void stringValidator(char* buffer, int maxLen, const string& prompt) {
    while (true) {
        cout << prompt;
        cin.getline(buffer, maxLen);

        // If the buffer overflowed, clear the remaining characters
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[31mInput too long! Maximum " << (maxLen - 1) << " characters.\033[0m\n";
            continue;
        }

        // Check for empty string
        if (std::strlen(buffer) == 0) {
            cout << "\033[31mInput cannot be empty!\033[0m\n";
            continue;
        }

        // Check that input is not only digits
        bool allDigits = std::all_of(buffer, buffer + std::strlen(buffer), ::isdigit);
        if (allDigits) {
            cout << "\033[31mInput cannot be only numbers!\033[0m\n";
            continue;
        }

        break;
    }
}

// Function for index selection with undo option (0 = undo)
static int indexValidator(int size, const string& prompt) {
    if (size == 0) {
        cout << "\033[31mNo items available.\033[0m\n";
        return 0;
    }
    cout << prompt;
    int index;
    while (true) {
        if (!(cin >> index)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\033[31mInvalid input. Enter a number: \033[0m";
            continue;
        }
        cin.ignore(1000, '\n'); 

        if (index == 0) {
            return 0; 
        }
        if (index >= 1 && index <= size) {
            return index;
        }

        cout << "\033[31mInvalid selection. Choose 1-" << size << " or 0 to cancel: \033[0m";
    }
}

// Input validation for string (can leave the old, press Enter)
static void editStringValidator(char* buffer, int maxLen, const string& fieldName) {
    while (true) {
        cout << "Current " << fieldName << ": " << buffer << endl;
        cout << "Press Enter to keep current value.\n";
        cout << "Enter new " << fieldName << " (max " << (maxLen - 1) << " chars): ";

        char input[31];
        cin.getline(input, maxLen);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[31mInput too long!.\033[0m\n";
            continue;

        }

        if (std::strlen(input) == 0)
            return;

        bool allDigits = std::all_of(input, input + std::strlen(input), ::isdigit);
        if (allDigits) {
            cout << "\033[31mInput cannot be only numbers!.\033[0m\n";
            continue;

        }

        copyToBuffer(buffer, static_cast<size_t>(maxLen), input);
        break;
    }

}

// Input validation for int (loop until valid or Enter)
static void editIntValidator(int& field, const string& fieldName) {
    while (true) {
        cout << "Current " << fieldName << ": " << field << endl;
        cout << "Press Enter to keep current value.\n";
        cout << "Enter new " << fieldName << " (1-9999): ";

        string input;
        getline(cin, input);

        if (input.empty()) {
            return;
        }

        try {
            int value = stoi(input);
            if (value > 0 && value <= 9999) {
                field = value;
                return; 
            }
            else {
                cout << "\033[31mInvalid range. Enter a number from 1 to 9999 or press Enter to keep old value.\033[0m\n";
            }
        }
        catch (...) {
            cout << "\033[31mInvalid input. Enter a valid number or press Enter to keep old value.\033[0m\n";
        }
    }
}

// Input validation for double (loop until valid or Enter)
static void editDoubleValidator(double& field, const string& fieldName) {
    while (true) {
        cout << "Current " << fieldName << ": " << field << endl;
        cout << "Press Enter to keep current value.\n";
        cout << "Enter new " << fieldName << " (0.01-9999.99): ";

        string input;
        getline(cin, input);

        if (input.empty()) {
            return;
        }

        try {
            double value = stod(input);
            if (value > 0.0 && value <= 9999.99) {
                field = value;
                return; 
            }
            else {
                cout << "\033[31mInvalid range. Enter a number from 0.01 to 9999.99 or press Enter to keep old value.\033[0m\n";
            }
        }
        catch (...) {
            cout << "\033[31mInvalid input. Enter a valid number or press Enter to keep old value.\033[0m\n";
        }
    }
}

// Expand dynamic array if needed
template<typename T>
void arrayExtension(T*& arr, int& size, int& capacity, const T& element) {
    if (size >= capacity) {
        int newCapacity = (capacity == 0) ? 4 : capacity * 2;
        T* temp = new T[newCapacity];

        for (int i = 0; i < size; ++i)
            temp[i] = arr[i];

        delete[] arr;
        arr = temp;
        capacity = newCapacity;
    }
    arr[size++] = element;
}

// Universal function to delete an item from a dynamic array
template<typename T>
void deleteItem(T*& arr, int& size, void (*displayFunc)(const T*, int), const char* itemName) {
    if (size == 0) {
        cout << "\033[31mNo " << itemName << " to delete!\033[0m\n";
        return;
    }

    displayFunc(arr, size);

    int index;
    cout << "Enter index of " << itemName << " to delete (1-" << size << "), (0 to cancel): ";
    cin >> index;

    if (index == 0) {
        cout << "\033[33mDelete cancelled.\033[0m\n";
        return;
    }

    if (index < 1 || index > size) {
        cout << "\033[31mInvalid number!\033[0m\n";
        return;
    }

    // Shift elements to remove selected
    for (int i = index - 1; i < size - 1; ++i)
        arr[i] = arr[i + 1];

    size--;
    cout << "\033[32mItem deleted successfully!\033[0m\n";
}

// Function to validate a correct date
static string dateValidCheck(const string& dateInput) {
    string date = dateInput;

    while (true) {
        regex pattern(R"(^\d{4}-\d{2}-\d{2}$)");
        if (!regex_match(date, pattern)) {
            cout << "\033[32mInvalid format. Use yyyy-mm-dd.\033[0m\n";
            return "";
        }

        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));

        if (year < 2025) {
            cout << "\033[32mYear cannot be less than 2025.\033[0m\n";
            return "";
        }

        if (month < 1 || month > 12) {
            cout << "\033[32mMonth must be between 01 and 12.\033[0m\n";
            return "";
        }

        bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        int daysInMonth[] = { 31, leap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if (day < 1 || day > daysInMonth[month - 1]) {
            cout << "\033[32mInvalid day for this month.\033[0m\n";
            return "";
        }

        return date;
    }
}

// Search receipts based on criteria
static void searchReceipts(Receipt* receipts, int count) {
    cout << "\n=== Search Receipts ===\n";

    int inputCardNumber;
    double minPrice, maxPrice;
    string categoryStr;

    cout << "Enter card number (0 to skip): ";
    cin >> inputCardNumber;

    cout << "Enter min total price (or -1 to skip): ";
    cin >> minPrice;

    cout << "Enter max total price (or -1 to skip): ";
    cin >> maxPrice;
    cin.ignore();

    cout << "Enter product category (Food, Clothes, Electronics, Books, HomeAndGarden or leave empty): ";
    getline(cin, categoryStr);

    bool categoryFilter = false;
    Category category;

    if (!categoryStr.empty()) {
        category = charToCategory(categoryStr);
        categoryFilter = true;
    }

    vector<Receipt> foundReceipts;

    for (int i = 0; i < count; ++i) {
        const Receipt& r = receipts[i];
        bool match = true;

        // 1. Filter by card number
        if (inputCardNumber != 0 && r.card.cardNumber != inputCardNumber)
            match = false;

        // 2. Filter by total price
        double total = r.getTotalWithDiscount();
        if (minPrice >= 0 && total < minPrice) match = false;
        if (maxPrice >= 0 && total > maxPrice) match = false;

        // 3. Filter by category
        if (categoryFilter) {
            bool categoryFound = false;
            for (const auto& item : r.items) {
                if (item.product.category == category) {
                    categoryFound = true;
                    break;
                }
            }
            if (!categoryFound) match = false;
        }

        if (match)
            foundReceipts.push_back(r);
    }

    if (foundReceipts.empty()) {
        cout << "\033[31mNo receipts found matching the criteria.\033[0m\n";
    }
    else {
        cout << "\n\033[32mFound " << foundReceipts.size() << " matching receipts:\033[0m\n";
        displayReceipts(foundReceipts.data(), static_cast<int>(foundReceipts.size()));
    }
}

// Check if file exists
bool fileExists(const std::string& filename) {
    ifstream file(filename);
    return file.good();
}

// Save all data and exit
static void saveAndExit() {
    saveProducts(loadedProducts, loadedProductCount, "products.json");
    saveEmployees(loadedEmployees, loadedEmployeeCount, "employees.json");
    saveDiscountCards(loadedCards, loadedCardCount, "discountCards.json");
    saveReceipts(loadedReceipts, loadedReceiptCount, "Receipts.json");
}

// Deduct purchased quantity from stock
static bool deductStock(int productCode, int quantity) {
    for (int i = 0; i < loadedProductCount; ++i) {
        if (loadedProducts[i].code == productCode) {
            if (quantity > loadedProducts[i].quantityInStock) {
                cout << "\033[31mNot enough stock for " << loadedProducts[i].name
                    << "! Available: " << loadedProducts[i].quantityInStock << "\033[0m\n";
                return false;
            }

            loadedProducts[i].quantityInStock -= quantity;
            return true;
        }
    }

    cout << "\033[31mProduct with code " << productCode << " not found!\033[0m\n";
    return false;
}

static PurchasedProduct inputNewProduct() {
    PurchasedProduct newItem;
    displayProducts(loadedProducts, loadedProductCount);

    int prodIndex;
    cout << "Select product index: ";
    while (!(cin >> prodIndex) || prodIndex < 1 || prodIndex > loadedProductCount) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid selection. Choose 1-" << loadedProductCount << ": \033[0m";
    }
    cin.ignore();

    newItem.product = loadedProducts[prodIndex - 1];

    int qty;
    while (true) {
        cout << "Enter quantity: ";
        if (cin >> qty && qty > 0) {
            cin.ignore(1000, '\n');
            if (deductStock(newItem.product.code, qty)) {
                newItem.quantity = qty;
                break;
            }
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\033[31mInvalid quantity. Enter a positive number: \033[0m" <<endl;
        }
    }

    return newItem;
}

// =============================== SAVE FUNCTIONS ===============================

// Save products to JSON file
void saveProducts(const Product* arr, int size, const char* filename) {
    ofstream file(filename);
    file << "[\n";

    for (int i = 0; i < size; ++i) {
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
    cout << "\033[32mSaved " << size << " products to " << filename << "!\033[0m\n";
}

// Save employees to JSON file
void saveEmployees(const Employee* arr, int size, const char* filename) {
    ofstream file(filename);
    file << "[\n";

    for (int i = 0; i < size; ++i) {
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
    cout << "\033[32mSaved " << size << " employees to " << filename << "!\033[0m\n";
}

// Save discount cards to JSON file
void saveDiscountCards(const DiscountCard* arr, int size, const char* filename) {
    ofstream file(filename);
    file << "[\n";

    for (int i = 0; i < size; ++i) {
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
    cout << "\033[32mSaved " << size << " discount cards to " << filename << "!\033[0m\n";
}

// Save receipts to JSON file
void saveReceipts(const Receipt* arr, int size, const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "\033[31mError: cannot open file " << filename << " for writing.\033[0m\n";
        return;
    }

    file << "[\n";
    for (int i = 0; i < size; ++i) {
        const Receipt& r = arr[i];
        double totalNoDiscount = r.getTotalNoDiscount();
        double totalWithDiscount = r.getTotalWithDiscount();
        double vat = r.getVAT();

        file << "  {\n"
            << "    \"receiptNumber\": " << r.receiptNumber << ",\n"
            << "    \"date\": \"" << r.date << "\",\n"
            << "    \"discountCard\": " << r.card.cardNumber << ",\n"
            << "    \"items\": [\n";

        for (size_t j = 0; j < r.items.size(); ++j) {
            const auto& item = r.items[j];
            file << "      {\n"
                << "        \"productName\": \"" << item.product.name << "\",\n"
                << "        \"productCode\": " << item.product.code << ",\n"
                << "        \"quantity\": " << item.quantity << ",\n"
                << "        \"price\": " << item.product.price << "\n"
                << "      }";
            if (j < r.items.size() - 1) file << ",";
            file << "\n";
        }

        file << "    ],\n"
            << "    \"total_no_discount\": " << totalNoDiscount << ",\n"
            << "    \"total_with_discount\": " << totalWithDiscount << ",\n"
            << "    \"VAT\": " << vat << "\n"
            << "  }";
        if (i < size - 1) file << ",";
        file << "\n";
    }

    file << "]\n";
    file.close();

    cout << "\033[32mSaved " << size << " receipts to " << filename << "!\033[0m\n";
}

// =============================== LOAD FUNCTIONS ===============================

// Load products from JSON file
void loadProducts(const char* filename, Product*& arr, int& size, int& capacity) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\033[31mFile " << filename << " not found!\033[0m\n";
        size = 0;
        return;
    }

    size = 0;
    string line;
    Product current{};
    bool inObject = false;

    while (getline(file, line)) {
        if (line.find('{') != string::npos) {
            inObject = true;
            current = Product{};
        }
        if (!inObject) continue;

        if (line.find("\"code\"") != string::npos) {
            std::sscanf(line.c_str(), "    \"code\": %d,", &current.code);
        }
        else if (line.find("\"name\"") != string::npos) {
            size_t start = line.find('"', 12) + 1;
            size_t end = line.find('"', start);
            string name = line.substr(start, end - start);
            copyToBuffer(current.name, sizeof(current.name), name);
        }
        else if (line.find("\"price\"") != string::npos) {
            std::sscanf(line.c_str(), "    \"price\": %lf,", &current.price);
        }
        else if (line.find("\"quantityInStock\"") != string::npos) {
            std::sscanf(line.c_str(), "    \"quantityInStock\": %d,", &current.quantityInStock);
        }
        else if (line.find("\"category\"") != string::npos) {
            size_t start = line.find('"', 14) + 1;
            size_t end = line.find('"', start);
            string cat = line.substr(start, end - start);
            current.category = charToCategory(cat);

            arrayExtension(arr, size, capacity, current);
            inObject = false;
        }
    }

    file.close();
    cout << "\033[32mLoaded " << size << " products from " << filename << "\033[0m\n";
}

// Load employees from JSON file
void loadEmployees(const char* filename, Employee*& arr, int& size, int& capacity) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\033[31mFile " << filename << " not found!\033[0m\n";
        size = 0;
        return;
    }

    size = 0;
    string line;
    Employee current{};
    bool inObject = false;

    while (getline(file, line)) {
        if (line.find('{') != string::npos) {
            inObject = true;
            current = Employee{};
        }
        if (!inObject) continue;

        if (line.find("\"id\"") != string::npos) {
            std::sscanf(line.c_str(), "    \"id\": %d,", &current.id);
        }
        else if (line.find("\"firstName\"") != string::npos) {
            size_t start = line.find('"', line.find(':')) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            copyToBuffer(current.firstName, sizeof(current.firstName), s);
        }
        else if (line.find("\"lastName\"") != string::npos) {
            size_t start = line.find('"', line.find(':')) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            copyToBuffer(current.lastName, sizeof(current.lastName), s);
        }
        else if (line.find("\"department\"") != string::npos) {
            size_t start = line.find('"', line.find(':')) + 1;
            size_t end = line.find('"', start);
            string dep = line.substr(start, end - start);
            current.department = charToCategory(dep);

            arrayExtension(arr, size, capacity, current);
            inObject = false;
        }
    }

    file.close();
    cout << "\033[32mLoaded " << size << " employees from " << filename << "\033[0m\n";
}

// Load discount cards from JSON file
void loadDiscountCards(const char* filename, DiscountCard*& arr, int& size, int& capacity) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\033[31mFile " << filename << " not found!\033[0m\n";
        size = 0;
        return;
    }

    size = 0;
    string line;
    DiscountCard current{};
    bool inObject = false;

    while (getline(file, line)) {
        if (line.find('{') != string::npos) {
            inObject = true;
            current = DiscountCard{};
        }
        if (!inObject) continue;

        if (line.find("\"cardNumber\"") != string::npos) {
            std::sscanf(line.c_str(), "    \"cardNumber\": %d,", &current.cardNumber);
        }
        else if (line.find("\"ownerFirstName\"") != string::npos) {
            size_t start = line.find('"', line.find(':')) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            copyToBuffer(current.ownerFirstName, sizeof(current.ownerFirstName), s);
        }
        else if (line.find("\"ownerLastName\"") != string::npos) {
            size_t start = line.find('"', line.find(':')) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            copyToBuffer(current.ownerLastName, sizeof(current.ownerLastName), s);
        }
        else if (line.find("\"type\"") != string::npos) {
            size_t start = line.find('"', line.find(':')) + 1;
            size_t end = line.find('"', start);
            string t = line.substr(start, end - start);
            current.type = charToCardType(t);

            arrayExtension(arr, size, capacity, current);
            inObject = false;
        }
    }

    file.close();
    cout << "\033[32mLoaded " << size << " discount cards from " << filename << "\033[0m\n";
}

// Load receipts from JSON file
void loadReceipts(
    const char* filename,
    Receipt*& arr, int& size,
    Product* products, int productSize,
    DiscountCard* cards, int cardSize,
    int& capacity
) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\033[31mFile " << filename << " not found!\033[0m\n";
        size = 0;
        return;
    }

    size = 0;
    string line;
    Receipt current{};
    bool inReceipt = false;
    bool inItems = false;

    while (getline(file, line)) {
        if (line.find('{') != string::npos && !inReceipt) {
            current = Receipt{};
            current.items.clear();
            inReceipt = true;
            continue;
        }

        if (!inReceipt) continue;

        if (line.find("\"receiptNumber\"") != string::npos) {
            std::sscanf(line.c_str(), "    \"receiptNumber\": %d,", &current.receiptNumber);
        }
        else if (line.find("\"date\"") != string::npos) {
            size_t start = line.find('"', line.find(':')) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            copyToBuffer(current.date, sizeof(current.date), s);
        }
        else if (line.find("\"discountCard\"") != string::npos) {
            int cardNum;
            std::sscanf(line.c_str(), "    \"discountCard\": %d,", &cardNum);
            for (int i = 0; i < cardSize; ++i) {
                if (cards[i].cardNumber == cardNum) {
                    current.card = cards[i];
                    break;
                }
            }
        }
        else if (line.find("\"items\"") != string::npos) {
            inItems = true;
            continue;
        }
        else if (inItems) {
            if (line.find(']') != string::npos) {
                inItems = false;
            }
            else if (line.find('{') != string::npos) {
                PurchasedProduct item{};
                string pname, pcodeLine, qtyLine, priceLine;

                getline(file, pname);
                getline(file, pcodeLine);
                getline(file, qtyLine);
                getline(file, priceLine);

                size_t start = pname.find('"', pname.find(':')) + 1;
                size_t end = pname.find('"', start);
                string productName = pname.substr(start, end - start);

                for (int i = 0; i < productSize; ++i) {
                    if (products[i].name == productName) {
                        item.product = products[i];
                        break;
                    }
                }

                std::sscanf(qtyLine.c_str(), "        \"quantity\": %d,", &item.quantity);
                current.items.push_back(item);
            }
        }

        if (line.find('}') != string::npos && !inItems && inReceipt) {
            arrayExtension(arr, size, capacity, current);
            inReceipt = false;
        }
    }

    file.close();
    cout << "\033[32mLoaded " << size << " receipts from " << filename << "\033[0m\n";
}

// =============================== ADD FUNCTIONS =============================== //

// Add Product
void addProduct() {
    Product newProduct;
    cout << "\n=== ADD NEW PRODUCT ===\n";

    newProduct.code = intValidator("Enter product code (0 to cancel, max 4 digits): ", true);
    if (newProduct.code == 0) return;

    stringValidator(newProduct.name, 31, "Enter name (max 30 chars): ");
    newProduct.price = doubleValidator("Enter product price (max 4 digits): ");
    newProduct.quantityInStock = intValidator("Enter product quantity in stock (max 4 digits): ");

    int category;
    cout << "Select category (0-Food, 1-Clothes, 2-Electronics, 3-Books, 4-HomeAndGarden): ";
    while (!(cin >> category) || category < 0 || category > 4) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Choose 0-4: \033[0m";
    }
    newProduct.category = static_cast<Category>(category);

    arrayExtension(loadedProducts, loadedProductCount, loadedProductCapacity, newProduct);
    cout << "\033[32mProduct added successfully!\033[0m\n";
}

// Add Employee
void addEmployee() {
    Employee newEmployee;
    cout << "\n=== ADD NEW EMPLOYEE ===\n";

    newEmployee.id = intValidator("Enter employee ID (0 to cancel, max 4 digits): ", true);
    if (newEmployee.id == 0)  return;

    stringValidator(newEmployee.firstName, 11, "Enter first name (max 10 chars): ");
    stringValidator(newEmployee.lastName, 11, "Enter last name (max 10 chars): ");

    int dep;
    cout << "Select department (0-Food, 1-Clothes, 2-Electronics, 3-Books, 4-HomeAndGarden): ";
    while (!(cin >> dep) || dep < 0 || dep > 4) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Choose 0-4: \033[0m";
    }
    newEmployee.department = static_cast<Category>(dep);

    arrayExtension(loadedEmployees, loadedEmployeeCount, loadedEmployeeCapacity, newEmployee);
    cout << "\033[32mEmployee added successfully!\033[0m\n";
}

// Add Discount Card
void addDiscountCard() {
    DiscountCard card;
    cout << "\n=== ADD NEW DISCOUNT CARD ===\n";

    card.cardNumber = intValidator("Enter card number (0 to cancel, max 4 digits): ", true);
    if (card.cardNumber == 0) return;

    stringValidator(card.ownerFirstName, 11, "Enter owner's first name (max 10 chars): ");
    stringValidator(card.ownerLastName, 11, "Enter last name (max 10 chars): ");

    int type;
    cout << "Select card type (0-Bronze, 1-Silver, 2-Gold): ";
    while (!(cin >> type) || type < 0 || type > 2) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Choose 0-2: \033[0m";
    }
    card.type = static_cast<DiscountCardType>(type);

    arrayExtension(loadedCards, loadedCardCount, loadedCardCapacity, card);
    cout << "\033[32mDiscount card added!\033[0m\n";
}

// Add Receipt
void addReceipt() {
    Receipt receipt;
    cout << "\n=== ADD NEW RECEIPT ===\n";

    receipt.receiptNumber = intValidator("Enter receipt number (0 to cancel, max 4 digits): ", true);
    if (receipt.receiptNumber == 0) return;

    string input;
    while (true) {
        cout << "Enter date (YYYY-MM-DD): ";
        getline(cin, input);
        string checkedDate = dateValidCheck(input);
        if (!checkedDate.empty()) {
            copyToBuffer(receipt.date, sizeof(receipt.date), checkedDate);
            break;
        }
        cout << "Please try again.\n";
    }
    // Add purchased products
    while (true) {
        PurchasedProduct item = inputNewProduct();
        receipt.items.push_back(item);

        cout << "Enter 0 to finish, -1 to add new product: ";
        int prodChoice;
        while (!(cin >> prodChoice) || (prodChoice != 0 && prodChoice != -1)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\033[31mInvalid input. Enter 0 to finish or -1 to add new: \033[0m";
        }
        cin.ignore();

        if (prodChoice == 0) break; 
    }

 
    // Select discount card
    displayDiscountCards(loadedCards, loadedCardCount);
    cout << "\nSelect discount card index: ";

    int cardIndex;
    while (!(cin >> cardIndex) || cardIndex < 1 || cardIndex > loadedCardCount) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid selection. Choose 1-" << loadedCardCount << ": \033[0m";
    }
    receipt.card = loadedCards[cardIndex - 1];

    // Save receipt
    arrayExtension(loadedReceipts, loadedReceiptCount, loadedReceiptCapacity, receipt);
    cout << "\033[32mReceipt added!\033[0m\n";
}

// =============================== EDIT FUNCTIONS =============================== //

// Edit Product
void editProduct(Product* arr, int size) {
    if (size == 0) {
        cout << "\033[31mNo products to edit.\033[0m\n";
        return;
    }

    displayProducts(arr, size);

    int prodIndex = indexValidator(size, "Select product index (0 to cancel): ");
    if (prodIndex == 0) {
        cout << "\033[33mEdit cancelled.\033[0m\n";
        return;
    }


    Product& p = arr[prodIndex - 1];
    cout << "\n=== EDIT PRODUCT #" << prodIndex << ": " << p.name << " ===\n";

	editIntValidator(p.code, "code");
    editStringValidator(p.name, 31, "name");
	editDoubleValidator(p.price, "price");
    editIntValidator(p.quantityInStock, "quantity in stock");

    cout << "Current category: " << categoryToChar(p.category) << endl;
    cout << "Press Enter to keep current value.\n";

    while (true) {
        cout << "Select new category (0-Food, 1-Clothes, 2-Electronics, 3-Books, 4-HomeAndGarden): ";
        string catInput;
        getline(cin, catInput);

        if (catInput.empty()) {
            break;
        }

        try {
            int catVal = stoi(catInput);
            if (catVal >= 0 && catVal <= 4) {
                p.category = static_cast<Category>(catVal);
                break; 
            }
            else {
                cout << "\033[31mInvalid category. Enter a number 0-4 or press Enter to keep old value.\033[0m\n";
            }
        }
        catch (...) {
            cout << "\033[31mInvalid input. Enter a number 0-4 or press Enter to keep old value.\033[0m\n";
        }
    }

    cout << "\n\033[32mProduct updated successfully!\033[0m\n";
}

// Edit Employee
void editEmployee(Employee* arr, int size) {
    if (size == 0) {
        cout << "\033[31mNo products to edit.\033[0m\n";
        return;
    }

    displayEmployees(arr, size);

    int employeIndex = indexValidator(size, "Select employee index (0 to cancel): ");
    if (employeIndex == 0) {
        cout << "\033[33mEdit cancelled.\033[0m\n";
        return;
    }

    Employee& e = arr[employeIndex - 1];
    cout << "\n=== EDIT EMPLOYEE #" << employeIndex << ": " << e.firstName << " ===\n";

	editIntValidator(e.id, "ID");
    editStringValidator(e.firstName, 11, "name");
    editStringValidator(e.lastName, 11, "last name");
  

    cout << "Current category: " << categoryToChar(e.department) << endl;
    cout << "Press Enter to keep current value.\n";

    while (true) {
        cout << "Select new category (0-Food, 1-Clothes, 2-Electronics, 3-Books, 4-HomeAndGarden): ";
        string catInput;
        getline(cin, catInput);

        if (catInput.empty()) {
            break;
        }

        try {
            int catVal = stoi(catInput);
            if (catVal >= 0 && catVal <= 4) {
                e.department = static_cast<Category>(catVal);
                break;
            }
            else {
                cout << "\033[31mInvalid depaetment. Enter a number 0-4 or press Enter to keep old value.\033[0m\n";
            }
        }
        catch (...) {
            cout << "\033[31mInvalid input. Enter a number 0-4 or press Enter to keep old value.\033[0m\n";
        }
    }

    cout << "\n\033[32mEmploye updated successfully!\033[0m\n";
}

// Edit Discount Card
void editDiscountCard(DiscountCard* arr, int size) {
    if (size == 0) {
        cout << "\033[31mNo products to edit.\033[0m\n";
        return;
    }
 
    displayDiscountCards(arr, size);

    int discountIndex = indexValidator(size, "Select discount card index (0 to cancel): ");
    if (discountIndex == 0) {
        cout << "\033[33mEdit cancelled.\033[0m\n";
        return;
    }

    DiscountCard& d = arr[discountIndex - 1];
    cout << "\n=== EDIT DISCOUNT CARD #" << discountIndex << ": " << d.cardNumber << " ===\n";

    editIntValidator(d.cardNumber, " card number");
    editStringValidator(d.ownerFirstName, 11, "name");
    editStringValidator(d.ownerLastName, 11, "last name");

    cout << "Current category: " << cardToChar(d.type) << endl;
    cout << "Press Enter to keep current value.\n";

    while (true) {
        cout << "Select new type (0-Bronze, 1-Silver, 2-Gold: ";
        string catInput;
        getline(cin, catInput);

        if (catInput.empty()) {
            break;
        }

        try {
            int catVal = stoi(catInput);
            if (catVal >= 0 && catVal <= 2) {
                d.type = static_cast<DiscountCardType>(catVal);
                break;
            }
            else {
                cout << "\033[31mInvalid type. Enter a number 0-2 or press Enter to keep old value.\033[0m\n";
            }
        }
        catch (...) {
            cout << "\033[31mInvalid input. Enter a number 0-4 or press Enter to keep old value.\033[0m\n";
        }
    }
    cout << "\n\033[32mDiscount card updated successfully!\033[0m\n";
    
}

// Edit Receipt 
void editReceipt(Receipt* arr, int size) {
    if (size == 0) {
        cout << "\033[31mNo products to edit.\033[0m\n";
        return;
    }

    displayReceipts(arr, size);

    cout << "Enter receipt number to edit (0 to cancel): ";
    int number;
    while (!(cin >> number)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number: \033[0m";
    }
    cin.ignore();

    if (number == 0) {
        cout << "\033[33mEdit cancelled.\033[0m\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (arr[i].receiptNumber == number) {
            found = true;
            cout << "\nEditing receipt " << arr[i].receiptNumber << endl;

            editIntValidator(arr[i].receiptNumber, "receipt number");

            string input;
            // Edit date
            while (true) {
                cout << "Enter new date (" << arr[i].date << ") or press Enter to keep: ";
                getline(cin, input);
                if (input.empty()) break;
                string checkedDate = dateValidCheck(input);
                if (!checkedDate.empty()) {
                    copyToBuffer(arr[i].date, sizeof(arr[i].date), checkedDate);
                    break;
                }
            }

            // Edit purchased products
            while (true) {
                cout << "\nPurchased products in this receipt:\n";
                for (size_t j = 0; j < arr[i].items.size(); j++) {
                    cout << j + 1 << ". " << arr[i].items[j].product.name
                        << " (Qty: " << arr[i].items[j].quantity << ")\n";
                }

                cout << "Enter product index to edit (0 to finish, -1 to add new): ";
                int prodChoice;
                while (!(cin >> prodChoice)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\033[31mInvalid input. Enter a number: \033[0m";
                }
                cin.ignore();

                if (prodChoice == 0) break;

                // Add new product
                if (prodChoice == -1) {
                    displayProducts(loadedProducts, loadedProductCount);
                    PurchasedProduct item = inputNewProduct();
                    arr[i].items.push_back(item);
                    continue;
                }

                // Edit existing product
                if (prodChoice > 0 && prodChoice <= static_cast<int>(arr[i].items.size())) {
                    PurchasedProduct& item = arr[i].items[prodChoice - 1];

                    // Restore old quantity to stock
                    for (int k = 0; k < loadedProductCount; k++) {
                        if (loadedProducts[k].code == item.product.code) {
                            loadedProducts[k].quantityInStock += item.quantity;
                            break;
                        }
                    }

                    displayProducts(loadedProducts, loadedProductCount);

                    int newIndex = indexValidator(loadedProductCount, "Enter new product index: ");
                    item.product = loadedProducts[newIndex - 1];

                    // Edit quantity with stock check
                    while (true) {
                        cout << "Enter new quantity (" << item.quantity << "): ";
                        getline(cin, input);
                        if (input.empty()) break;

                        int newQty = stoi(input);
                        if (deductStock(item.product.code, newQty)) {
                            item.quantity = newQty;
                            break;
                        }
                        else {
                            cout << "Enter a smaller quantity.\n";
                        }
                    }
                }
            }

            // Edit discount card
            displayDiscountCards(loadedCards, loadedCardCount);




            int newIndex = indexValidator(loadedCardCount, "Enter card index: ");
                for (int i = 0; i < loadedCardCount; i++) {
                    arr[i].card = loadedCards[newIndex - 1];
                }
           

            cout << "\n\033[32mReceipt updated successfully!\033[0m\n";
            break;
        }
    }

    if (!found)
        cout << "\033[31mReceipt not found.\033[0m\n";
}

// =============================== SORT FUNCTIONS ===============================

// By name
void sortProductsByName(Product* arr, int size) {
    if (size == 0) {
        cout << "\033[31mNo products to display.\033[0m\n";
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (std::string(arr[j].name) > std::string(arr[j + 1].name)) {
                Product temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    displayProducts(loadedProducts, loadedProductCount);
    cout << "\033[32mProduct sorted successfully!\033[0m\n";
}

// By price ascending
void sortProductsByPriceAscending(Product* arr, int size) {
    if (size == 0) {
        cout << "\033[31mNo products to display.\033[0m\n";
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].price > arr[j + 1].price) {
                Product temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    displayProducts(loadedProducts, loadedProductCount);
    cout << "\033[32mProduct sorted successfully!\033[0m\n";
}

// By price descending
void sortProductsByPriceDescending(Product* arr, int size) {
    if (size == 0) {
        cout << "\033[31mNo products to display.\033[0m\n";
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].price < arr[j + 1].price) {
                Product temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    displayProducts(loadedProducts, loadedProductCount);
    cout << "\033[32mProduct sorted successfully!\033[0m\n";
}

// By quantity ascending
void sortProductsByQuantityAscending(Product* arr, int size) {
    if (size == 0) {
        cout << "\033[31mNo products to display.\033[0m\n";
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].quantityInStock > arr[j + 1].quantityInStock) {
                Product temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    displayProducts(loadedProducts, loadedProductCount);
    cout << "\033[32mProduct sorted successfully!\033[0m\n";
}

// By quantity descending
void sortProductsByQuantityDescending(Product* arr, int size) {
    if (size == 0) {
        cout << "\033[31mNo products to display.\033[0m\n";
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].quantityInStock < arr[j + 1].quantityInStock) {
                Product temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    displayProducts(loadedProducts, loadedProductCount);
    cout << "\033[32mProduct sorted successfully!\033[0m\n";
}

// =============================== PROGRAM MENU ===============================//

// Main program menu loop
void runProgramMenu() {
    int choice;
    do {
        showMainMenu();
        while (!(cin >> choice)) { 
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\033[1;31mInvalid input! Enter a number: \033[0m";
        }

        switch (choice) {
        case 1: { 
            // View Data
            int viewChoice;
            do {
                showViewDataSubMenu();
                while (!(cin >> viewChoice)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\033[1;31mInvalid input! Enter a number: \033[0m";
                }

                switch (viewChoice) {
                case 1: 
                    // Display all data
                    if (loadedProductCount == 0 && loadedEmployeeCount == 0 &&
                        loadedCardCount == 0 && loadedReceiptCount == 0) {
                        cout << "\033[1;31m\nNo data available to display!\033[0m\n";
                    }
                    else displayFullDataResponse();
                    break;
                case 2: { 
                    // Display part of data
                    int subChoice;
                    do {
                        showViewPartDataSubMenu();
                        while (!(cin >> subChoice)) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "\033[1;31mInvalid input! Enter a number: \033[0m";
                        }

                        switch (subChoice) {
                        case 1: displayProducts(loadedProducts, loadedProductCount); break;
                        case 2: displayEmployees(loadedEmployees, loadedEmployeeCount); break;
                        case 3: displayDiscountCards(loadedCards, loadedCardCount); break;
                        case 4: displayReceipts(loadedReceipts, loadedReceiptCount); break;
                        default:
                            if (subChoice != 5) cout << "\033[1;31m\nInvalid choice!\033[0m\n";
                        }
                        cout << endl;
                    } while (subChoice != 5);
                    break;
                }
                default:
                    if (viewChoice != 3) cout << "\033[1;31m\nInvalid choice!\033[0m\n";
                }
                cout << endl;
            } while (viewChoice != 3);
            break;
        }

        case 2: { 
            // Add Data
            int addChoice;
            do {
                showAddDataSubMenu();
                while (!(cin >> addChoice)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\033[1;31mInvalid input! Enter a number: \033[0m";
                }

                switch (addChoice) {
                case 1: addProduct(); break;
                case 2: addEmployee(); break;
                case 3: addDiscountCard(); break;
                case 4: addReceipt(); break;
                default:
                    if (addChoice != 5) cout << "\033[1;31m\nInvalid choice!\033[0m\n";
                }
                cout << endl;
            } while (addChoice != 5);
            break;
        }

        case 3: { 
            // Edit Data
            int editChoice;
            do {
                showEditDataMenu();
                while (!(cin >> editChoice)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\033[1;31mInvalid input! Enter a number: \033[0m";
                }

                switch (editChoice) {
                case 1:
                    if (loadedProductCount > 0) editProduct(loadedProducts, loadedProductCount);
                    else cout << "\033[1;31m\nNo products available!\033[0m\n";
                    break;
                case 2:
                    if (loadedEmployeeCount > 0) editEmployee(loadedEmployees, loadedEmployeeCount);
                    else cout << "\033[1;31m\nNo employees available!\033[0m\n";
                    break;
                case 3:
                    if (loadedCardCount > 0) editDiscountCard(loadedCards, loadedCardCount);
                    else cout << "\033[1;31m\nNo discount cards available!\033[0m\n";
                    break;
                case 4:
                    if (loadedReceiptCount > 0) editReceipt(loadedReceipts, loadedReceiptCount);
                    else cout << "\033[1;31m\nNo receipts available!\033[0m\n";
                    break;
                default:
                    if (editChoice != 5) cout << "\033[1;31m\nInvalid choice!\033[0m\n";
                }
            } while (editChoice != 5);
            break;
        }

        case 4: { 
            // Remove Data
            int removeChoice;
            do {
                showRemoveDataMenu();
                while (!(cin >> removeChoice)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\033[1;31mInvalid input! Enter a number: \033[0m";
                }

                switch (removeChoice) {
                case 1:
                    if (loadedProductCount > 0) deleteItem(loadedProducts, loadedProductCount, displayProducts, "product");
                    else cout << "\033[1;31m\nNo products available!\033[0m\n";
                    break;
                case 2:
                    if (loadedEmployeeCount > 0) deleteItem(loadedEmployees, loadedEmployeeCount, displayEmployees, "employee");
                    else cout << "\033[1;31m\nNo employees available!\033[0m\n";
                    break;
                case 3:
                    if (loadedCardCount > 0) deleteItem(loadedCards, loadedCardCount, displayDiscountCards, "discount card");
                    else cout << "\033[1;31m\nNo discount cards available!\033[0m\n";
                    break;
                     case 4:
                    if (loadedReceiptCount > 0) deleteItem(loadedReceipts, loadedReceiptCount, displayReceipts, "receipt");
                    else cout << "\033[1;31m\nNo receipts available!\033[0m\n";
                    break;
                default:
                    if (removeChoice != 5) cout << "\033[1;31m\nInvalid choice!\033[0m\n";
                }
            } while (removeChoice != 5);
            break;
        }
        case 5: searchReceipts(loadedReceipts, loadedReceiptCount); break;
        case 6: { 
            // Sort Data
            int sortChoice;
            do {
                showSortDataMenu();
                while (!(cin >> sortChoice)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\033[1;31mInvalid input! Enter a number: \033[0m";
                }

                switch (sortChoice) {
                case 1: sortProductsByName(loadedProducts, loadedProductCount); break;
                case 2: sortProductsByPriceAscending(loadedProducts, loadedProductCount); break;
                case 3: sortProductsByPriceDescending(loadedProducts, loadedProductCount); break;
                case 4: sortProductsByQuantityAscending(loadedProducts, loadedProductCount); break;
                case 5: sortProductsByQuantityDescending(loadedProducts, loadedProductCount); break;
                default:
                    if (sortChoice != 6) cout << "\033[1;31m\nInvalid choice!\033[0m\n";
                }
            } while (sortChoice != 6);
            break;
        }
        case 7: 
            // Save and Exit
            saveAndExit();
            cout << "\033[1;31m\nExiting program...\033[0m\n";
            break;

        default:
            cout << "\033[1;31m\nInvalid choice!\033[0m\n";
        }
    } while (choice != 7);
}

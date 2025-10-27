#include "Function.h"
#include <regex> 
#include <fstream>
#include <iomanip>
#include "menu.h"
#include <iostream>
#include "dataView.h"
#include "globals.h"
#include "vector"
using namespace std;

// =============================== SAVE FUNCTIONS ===============================

// Save products to JSON file
void saveProducts(const Product* arr, int size, const char* filename) {
    ofstream file(filename);
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
    cout << "\033[32mSaved " << size << " products to " << filename << "!\033[0m" << endl;
}

// Save employees to a JSON file
void saveEmployees(const Employee* arr, int size, const char* filename) {
    ofstream file(filename);
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
    cout << "\033[32mSaved " << size << " employees to " << filename << "!\033[0m" << endl;
}

// Save discount cards to a JSON file
void saveDiscountCards(const DiscountCard* arr, int size, const char* filename) {
    ofstream file(filename);
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
    cout << "\033[32mSaved " << size << " discount cards to " << filename << "!\033[0m" << endl;
}

// Save receipts to a JSON file
void saveReceipts(const Receipt* arr, int size, const char* filename) {
    ofstream file(filename);
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
    cout << "\033[32mSaved " << size << " receipts to " << filename << "!\033[0m" << endl;
}

// =============================== HELPER FUNCTIONS ===============================

// Expand dynamic array if needed
template<typename T>
void arrayExtension(T*& arr, int& size, int& capacity, const T& element) {
    if (size >= capacity) {
        int newCapacity = (capacity == 0) ? 4 : capacity * 2;
        T* temp = new T[newCapacity];
        for (int i = 0; i < size; ++i) temp[i] = arr[i];
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
    cout << "Enter number of " << itemName << " to delete (1-" << size << "), (0 to cancel): ";
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
    for (int i = index - 1; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }

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
    int inputNumber;
    double minPrice, maxPrice;
    string categoryStr;
    vector<Receipt> foundReceipts;

    cout << "\n=== Search Receipts ===\n";

    cout << "Enter card number (0 to skip): ";
    cin >> inputNumber;
    cout << "Enter min price (or -1 to skip): ";
    cin >> minPrice;
    cout << "Enter max price (or -1 to skip): ";
    cin >> maxPrice;
    cin.ignore();

    cout << "Enter product category (Food, Clothes, Electronics, Books, HomeAndGarden or leave empty): ";
    getline(cin, categoryStr);

    Category category;
    bool categoryFilter = false;
    if (!categoryStr.empty()) {
        category = charToCategory(categoryStr);
        categoryFilter = true;
    }

    vector<Receipt> found;

    for (int i = 0; i < count; ++i) {
        const Receipt& r = receipts[i];
        bool match = true;

        if (inputNumber != 0 && r.card.cardNumber != inputNumber) match = false;

        double total = r.getTotalWithDiscount();
        if (minPrice >= 0 && total < minPrice) match = false;
        if (maxPrice >= 0 && total > maxPrice) match = false;

        if (categoryFilter && r.product.category != category) match = false;

        if (match) foundReceipts.push_back(r);
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
bool fileExists(const string& filename) {
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


// =============================== SORT FUNCTIONS ===============================

// By name
static void sortProductsByName(Product* arr, int size) {
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
static void sortProductsByPriceAscending(Product* arr, int size) {
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
static void sortProductsByPriceDescending(Product* arr, int size) {
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
static void sortProductsByQuantityAscending(Product* arr, int size) {
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
static void sortProductsByQuantityDescending(Product* arr, int size) {
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
            int code;
            sscanf_s(line.c_str(), "    \"code\": %d,", &code);
            current.code = code;
        }
        else if (line.find("\"name\"") != string::npos) {
            size_t start = line.find('"', 12) + 1;
            size_t end = line.find('"', start);
            string name = line.substr(start, end - start);
            strcpy_s(current.name, sizeof(current.name), name.c_str());
        }
        else if (line.find("\"price\"") != string::npos) {
            double price;
            sscanf_s(line.c_str(), "    \"price\": %lf,", &price);
            current.price = price;
        }
        else if (line.find("\"quantityInStock\"") != string::npos) {
            int qty;
            sscanf_s(line.c_str(), "    \"quantityInStock\": %d,", &qty);
            current.quantityInStock = qty;
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
            int id;
            sscanf_s(line.c_str(), "    \"id\": %d,", &id);
            current.id = id;
        }
        else if (line.find("\"firstName\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strncpy_s(current.firstName, sizeof(current.firstName), s.c_str(), _TRUNCATE);
        }
        else if (line.find("\"lastName\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strncpy_s(current.lastName, sizeof(current.lastName), s.c_str(), _TRUNCATE);
        }
        else if (line.find("\"department\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
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
            int num;
            sscanf_s(line.c_str(), "    \"cardNumber\": %d,", &num);
            current.cardNumber = num;
        }
        else if (line.find("\"ownerFirstName\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strcpy_s(current.ownerFirstName, sizeof(current.ownerFirstName), s.c_str());
        }
        else if (line.find("\"ownerLastName\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strcpy_s(current.ownerLastName, sizeof(current.ownerLastName), s.c_str());
        }
        else if (line.find("\"type\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
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
void loadReceipts(const char* filename, Receipt*& arr, int& size,
    Product* products, int productSize,
    DiscountCard* cards, int cardSize,
    int& capacity) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\033[31mFile " << filename << " not found!\033[0m\n";
        size = 0;
        return;
    }

    size = 0;
    string line;
    Receipt current{};
    bool inObject = false;

    while (getline(file, line)) {
        if (line.find('{') != string::npos) {
            inObject = true;
            current = Receipt{};
        }
        if (!inObject) continue;

        if (line.find("\"receiptNumber\"") != string::npos) {
            int num;
            sscanf_s(line.c_str(), "    \"receiptNumber\": %d,", &num);
            current.receiptNumber = num;
        }
        else if (line.find("\"date\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strcpy_s(current.date, sizeof(current.date), s.c_str());
        }
        else if (line.find("\"product\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            for (int i = 0; i < productSize; ++i) {
                if (s == products[i].name) {
                    current.product = products[i];
                    break;
                }
            }
        }
        else if (line.find("\"quantity\"") != string::npos) {
            int q;
            sscanf_s(line.c_str(), "    \"quantity\": %d,", &q);
            current.quantity = q;
        }
        else if (line.find("\"discountCard\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            int cardNum = stoi(line.substr(start, end - start));
            for (int i = 0; i < cardSize; ++i) {
                if (cards[i].cardNumber == cardNum) {
                    current.card = cards[i];
                    break;
                }
            }

            arrayExtension(arr, size, capacity, current);
            inObject = false;
        }
    }

    file.close();
    cout << "\033[32mLoaded " << size << " receipts from " << filename << "\033[0m\n";
}

// =============================== ADD FUNCTIONS =============================== // 

// Add Product
static void addProduct() {
    Product newProduct;
    cout << "\n=== ADD NEW PRODUCT ===\n";

    cout << "Enter product code (0 to cancel): ";
    while (!(cin >> newProduct.code)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number: \033[0m";
    }
    cin.ignore();

    if (newProduct.code == 0) {
        cout << "\033[33mAdd product cancelled.\033[0m\n";
        return;
    }

    cout << "Enter name: ";
    cin.getline(newProduct.name, 50);

    cout << "Enter price: ";
    while (!(cin >> newProduct.price)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number: \033[0m";
    }

    cout << "Enter quantity in stock: ";
    while (!(cin >> newProduct.quantityInStock)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number: \033[0m";
    }

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
static void addEmployee() {
    Employee newEmployee;
    cout << "\n=== ADD NEW EMPLOYEE ===\n";

    cout << "Enter employee ID (0 to cancel): ";
    while (!(cin >> newEmployee.id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number: \033[0m";
    }
    cin.ignore();

    if (newEmployee.id == 0) {
        cout << "\033[33mAdd employee cancelled.\033[0m\n";
        return;
    }

    cout << "Enter first name: ";
    cin.getline(newEmployee.firstName, 10);

    cout << "Enter last name: ";
    cin.getline(newEmployee.lastName, 20);

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
static void addDiscountCard() {
    DiscountCard card;
    cout << "\n=== ADD NEW DISCOUNT CARD ===\n";

    cout << "Enter card number (0 to cancel): ";
    while (!(cin >> card.cardNumber)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number: \033[0m";
    }
    cin.ignore();

    if (card.cardNumber == 0) {
        cout << "\033[33mAdd discount card cancelled.\033[0m\n";
        return;
    }

    cout << "Enter owner's first name: ";
    cin.getline(card.ownerFirstName, 20);

    cout << "Enter owner's last name: ";
    cin.getline(card.ownerLastName, 30);

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
static void addReceipt() {
    Receipt receipt;
    cout << "\n=== ADD NEW RECEIPT ===\n";

    cout << "Enter receipt number (0 to cancel): ";
    while (!(cin >> receipt.receiptNumber)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number: \033[0m";
    }
    cin.ignore();

    if (receipt.receiptNumber == 0) {
        cout << "\033[33mAdd receipt cancelled.\033[0m\n";
        return;
    }

    string input;
    while (true) {
        cout << "Enter date (YYYY-MM-DD): ";
        getline(cin, input);
        string checkedDate = dateValidCheck(input);
        if (!checkedDate.empty()) {
            strcpy_s(receipt.date, checkedDate.c_str());
            break;
        }
        cout << "Please try again.\n";
    }

    cout << "Select product:\n";
    for (int i = 0; i < loadedProductCount; i++)
        cout << i + 1 << ". " << loadedProducts[i].name << endl;

    int prodIndex;
    while (!(cin >> prodIndex) || prodIndex < 1 || prodIndex > loadedProductCount) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid selection. Choose 1-" << loadedProductCount << ": \033[0m";
    }
    receipt.product = loadedProducts[prodIndex - 1];

    cout << "Enter quantity: ";
    while (!(cin >> receipt.quantity) || receipt.quantity < 1) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid quantity. Enter a positive number: \033[0m";
    }

    cout << "Select discount card:\n";
    for (int i = 0; i < loadedCardCount; i++)
        cout << i + 1 << ". " << loadedCards[i].cardNumber << " (" << loadedCards[i].ownerFirstName << ")\n";

    int cardIndex;
    while (!(cin >> cardIndex) || cardIndex < 1 || cardIndex > loadedCardCount) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid selection. Choose 1-" << loadedCardCount << ": \033[0m";
    }
    receipt.card = loadedCards[cardIndex - 1];

    arrayExtension(loadedReceipts, loadedReceiptCount, loadedReceiptCapacity, receipt);
    cout << "\033[32mReceipt added!\033[0m\n";
}

// =============================== EDIT FUNCTIONS =============================== //

// Edit Product
static void editProduct(Product* arr, int size) {
    displayProducts(arr, size);

    cout << "Enter product code to edit (0 to cancel): ";
    int code;
    while (!(cin >> code)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number: \033[0m";
    }
    cin.ignore();

    if (code == 0) {
        cout << "\033[33mEdit cancelled.\033[0m\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (arr[i].code == code) {
            found = true;
            cout << "\nEditing product: " << arr[i].name << endl;

            cout << "Enter new name (" << arr[i].name << "): ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) strcpy_s(arr[i].name, newName.c_str());

            cout << "Enter new price (" << arr[i].price << "): ";
            string input;
            getline(cin, input);
            if (!input.empty()) arr[i].price = stod(input);

            cout << "Enter new quantity (" << arr[i].quantityInStock << "): ";
            getline(cin, input);
            if (!input.empty()) arr[i].quantityInStock = stoi(input);

            cout << "\n\033[32mProduct updated successfully!\033[0m\n";
            break;
        }
    }

    if (!found)
        cout << "\033[31mProduct not found.\033[0m\n";
}

// Edit Employee
static void editEmployee(Employee* arr, int size) {
    displayEmployees(arr, size);

    cout << "Enter employee ID to edit (0 to cancel): ";
    int id;
    while (!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\033[31mInvalid input. Enter a number: \033[0m";
    }
    cin.ignore();

    if (id == 0) {
        cout << "\033[33mEdit cancelled.\033[0m\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            found = true;
            cout << "\nEditing employee: " << arr[i].firstName << " " << arr[i].lastName << endl;

            cout << "Enter new first name (" << arr[i].firstName << "): ";
            string fn;
            getline(cin, fn);
            if (!fn.empty()) strcpy_s(arr[i].firstName, fn.c_str());

            cout << "Enter new last name (" << arr[i].lastName << "): ";
            string ln;
            getline(cin, ln);
            if (!ln.empty()) strcpy_s(arr[i].lastName, ln.c_str());

            cout << "Select new department (" << static_cast<int>(arr[i].department) << "):\n";
            cout << "0 - Food\n1 - Clothes\n2 - Electronics\n3 - Books\n4 - HomeAndGarden\n";
            cout << "Enter choice (press Enter to skip): ";
            string depInput;
            getline(cin, depInput);
            if (!depInput.empty()) {
                int dep = stoi(depInput);
                if (dep >= 0 && dep <= 4)
                    arr[i].department = static_cast<Category>(dep);
                else
                    cout << "\033[31mInvalid department, unchanged.\033[0m\n";
            }

            cout << "\n\033[32mEmployee updated successfully!\033[0m\n";
            break;
        }
    }

    if (!found)
        cout << "\033[31mEmployee not found.\033[0m\n";
}

// Edit Discount Card
static void editDiscountCard(DiscountCard* arr, int size) {
    displayDiscountCards(arr, size);

    cout << "Enter discount card number to edit (0 to cancel): ";
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
        if (arr[i].cardNumber == number) {
            found = true;
            cout << "\nEditing discount card " << arr[i].cardNumber << endl;

            cout << "Enter new owner first name (" << arr[i].ownerFirstName << "): ";
            string firstName;
            getline(cin, firstName);
            if (!firstName.empty()) strcpy_s(arr[i].ownerFirstName, firstName.c_str());

            cout << "Enter new owner last name (" << arr[i].ownerLastName << "): ";
            string lastName;
            getline(cin, lastName);
            if (!lastName.empty()) strcpy_s(arr[i].ownerLastName, lastName.c_str());

            cout << "Select new card type (" << static_cast<int>(arr[i].type) << "):\n";
            cout << "0 - Bronze\n1 - Silver\n2 - Gold\nEnter choice: ";
            string typeInput;
            getline(cin, typeInput);
            if (!typeInput.empty()) {
                int t = stoi(typeInput);
                if (t >= 0 && t <= 2)
                    arr[i].type = static_cast<DiscountCardType>(t);
                else
                    cout << "\033[31mInvalid card type, unchanged.\033[0m\n";
            }

            cout << "\n\033[32mDiscount card updated successfully!\033[0m\n";
            break;
        }
    }

    if (!found)
        cout << "\033[31mDiscount card not found.\033[0m\n";
}

// Edit Receipt
static void editReceipt(Receipt* arr, int size) {
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

            string input;

            displayProducts(loadedProducts, loadedProductCount);
            cout << "Enter new product code (" << arr[i].product.code << "): ";
            getline(cin, input);
            if (!input.empty()) {
                int newCode = stoi(input);
                for (int j = 0; j < loadedProductCount; j++) {
                    if (loadedProducts[j].code == newCode) {
                        arr[i].product = loadedProducts[j];
                        break;
                    }
                }
            }

            cout << "Enter new quantity (" << arr[i].quantity << "): ";
            getline(cin, input);
            if (!input.empty()) arr[i].quantity = stoi(input);

            while (true) {
                cout << "Enter new date (" << arr[i].date << ") or press Enter to keep: ";
                getline(cin, input);
                if (input.empty()) break;
                string checkedDate = dateValidCheck(input);
                if (!checkedDate.empty()) {
                    strcpy_s(arr[i].date, checkedDate.c_str());
                    break;
                }
            }

            displayDiscountCards(loadedCards, loadedCardCount);
            cout << "Enter new discount card number (" << arr[i].card.cardNumber << "): ";
            getline(cin, input);
            if (!input.empty()) {
                int cardNum = stoi(input);
                for (int j = 0; j < loadedCardCount; j++) {
                    if (loadedCards[j].cardNumber == cardNum) {
                        arr[i].card = loadedCards[j];
                        break;
                    }
                }
            }

            cout << "\n\033[32mReceipt updated successfully!\033[0m\n";
            break;
        }
    }

    if (!found)
        cout << "\033[31mReceipt not found.\033[0m\n";
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

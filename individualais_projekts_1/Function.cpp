#include "Function.h"
#include <fstream>
#include <iomanip>
#include "menu.h"
#include <iostream>
#include "dataView.h"
#include "globals.h"

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

// Save  employees to a JSON file
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

// Save  discount cards to a JSON file
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
    cout << "\033[32mSaved " << size << " discount сards to " << filename << "!\033[0m" << endl;
}

// Save  receipts to a JSON file
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
    cout << "\033[32mSaved " << size << " receipts сards to " << filename << "!\033[0m" << endl;
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


// Check if file exists
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

static void saveAndExit() {
    saveProducts(loadedProducts, loadedProductCount, "products.json");
    saveEmployees(loadedEmployees, loadedEmployeeCount, "employees.json");
    saveDiscountCards(loadedCards, loadedCardCount, "discountCards.json");
    saveReceipts(loadedReceipts, loadedReceiptCount, "Receipts.json");   
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
    Product* products, int productSize, DiscountCard* cards, int cardSize,
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


// =============================== ADD FUNCTIONS ===============================// 

// Add Product
static void addProduct() {
    Product newProduct;
    cout << "\n=== ADD NEW PRODUCT ===\n";
    cout << "Enter product code ( 0 to cancel): ";
    cin >> newProduct.code;
    cin.ignore();

    if (newProduct.code == 0) {
        cout << "\033[33mAdd product cancelled.\033[0m\n";
        return;
    }

    cout << "Enter name: ";
    cin.getline(newProduct.name, 50);

    cout << "Enter price: ";
    cin >> newProduct.price;

    cout << "Enter quantity in stock: ";
    cin >> newProduct.quantityInStock;

    int category;
    cout << "Select category (0-Food, 1-Clothes, 2-Electronics, 3-Books, 4-HomeAndGarden): ";
    cin >> category;
    newProduct.category = static_cast<Category>(category);

    arrayExtension(loadedProducts, loadedProductCount, loadedProductCapacity, newProduct);
    cout << "\033[32mProduct added successfully!\033[0m\n";
}

static void addEmployee() {
    Employee newEmployee;
    cout << "\n=== ADD NEW EMPLOYEE ===\n";
    cout << "Enter employee ID ( 0 to cancel): ";
    cin >> newEmployee.id;
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
    cout << "Select department (0-Food,1-Clothes,2-Electronics,3-Books,4-HomeAndGarden): ";
    cin >> dep;
    newEmployee.department = static_cast<Category>(dep);

    arrayExtension(loadedEmployees, loadedEmployeeCount, loadedEmployeeCapacity, newEmployee);
    cout << "\033[32mEmployee added successfully!\033[0m\n";
}

// Add DiscountCard
static void addDiscountCard() {
    DiscountCard card;
    cout << "\n=== ADD NEW DISCOUNT CARD ===\n";
    cout << "Enter card number ( 0 to cancel): ";
    cin >> card.cardNumber;
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
    cout << "Select card type (0-Bronze,1-Silver,2-Gold): ";
    cin >> type;
    card.type = static_cast<DiscountCardType>(type);

    arrayExtension(loadedCards, loadedCardCount, loadedCardCapacity, card);
    cout << "\033[32mDiscount card added!\033[0m\n";
}

// Add Receipt
static void addReceipt() {
    Receipt receipt;
    cout << "\n=== ADD NEW RECEIPT ===\n";
    cout << "Enter receipt number ( 0 to cancel): ";
    cin >> receipt.receiptNumber;
    cin.ignore();

    if (receipt.receiptNumber == 0) {
        cout << "\033[33mAdd receipt cancelled.\033[0m\n";
        return;
    }
    cout << "Enter date (YYYY-MM-DD): ";
    cin.getline(receipt.date, 12);

    cout << "Select product:\n";
    for (int i = 0; i < loadedProductCount; i++)
        cout << i + 1 << ". " << loadedProducts[i].name << endl;
    int prodIndex; cin >> prodIndex;
    receipt.product = loadedProducts[prodIndex - 1];

    cout << "Enter quantity: ";
    cin >> receipt.quantity;

    cout << "Select discount card:\n";
    for (int i = 0; i < loadedCardCount; i++)
        cout << i + 1 << ". " << loadedCards[i].cardNumber << " (" << loadedCards[i].ownerFirstName << ")\n";
    int cardIndex; cin >> cardIndex;
    receipt.card = loadedCards[cardIndex - 1];

    arrayExtension(loadedReceipts, loadedReceiptCount, loadedReceiptCapacity, receipt);
    cout << "\033[32mReceipt added!\033[0m\n";
}

// =============================== EDIT FUNCTIONS ===============================

// Edit Product
static void editProduct(Product* arr, int size) {
    displayProducts(loadedProducts, loadedProductCount);
    int code;
    cout << "Enter product Code to edit (0 to cancel): ";
    cin >> code;

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
            cin.ignore();
            string newName;
            getline(cin, newName);
            if (!newName.empty()) strcpy_s(arr[i].name, newName.c_str());

            cout << "Enter new price (" << arr[i].price << "): ";
            double newPrice;
            if (cin >> newPrice) arr[i].price = newPrice;
            else {
                cin.clear();
                cin.ignore(1000, '\n');
            }

            cout << "Enter new quantity (" << arr[i].quantityInStock << "): ";
            int newQty;
            if (cin >> newQty) arr[i].quantityInStock = newQty;
            else {
                cin.clear();
                cin.ignore(1000, '\n');
            }

            cout << "\n\033[32mProduct updated successfully!\033[0m\n";
            break;
        }
    } 
    if (!found) 
        cout << "\033[31mProduct not found.\033[0m\n";
}

// Edit Employee
static void editEmployee(Employee* arr, int size) {
    displayEmployees(loadedEmployees, loadedEmployeeCount);
    int id;
    cout << "Enter employee ID to edit (0 to cancel): ";
    cin >> id;

    if (id == 0) {
        cout << "\033[33mEdit cancelled.\033[0m\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            found = true;
            cout << "\nEditing employee: " << arr[i].firstName << " " << arr[i].lastName << endl;
            cin.ignore();

            cout << "Enter new first name (" << arr[i].firstName << "): ";
            string fn;
            getline(cin, fn);
            if (!fn.empty()) strcpy_s(arr[i].firstName, fn.c_str());

            cout << "Enter new last name (" << arr[i].lastName << "): ";
            string ln;
            getline(cin, ln);
            if (!ln.empty()) strcpy_s(arr[i].lastName, ln.c_str());

            cout << "Select new department (" << static_cast<int>(arr[i].department) << "):\n";
            cout << "0 - Food\n";
            cout << "1 - Clothes\n";
            cout << "2 - Electronics\n";
            cout << "3 - Books\n";
            cout << "4 - HomeAndGarden\n";
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
    displayDiscountCards(loadedCards, loadedCardCount);
    int number;
    cout << "Enter discount card number to edit (0 to cancel): ";
    cin >> number;

    if (number == 0) {
        cout << "\033[33mEdit cancelled.\033[0m\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (arr[i].cardNumber == number) {
            found = true;
            cout << "\nEditing discount card " << arr[i].cardNumber << endl; 
            cin.ignore();

            cout << "Enter new owner first name (" << arr[i].ownerFirstName << "): ";
            string firstName;
            getline(cin, firstName);
            if (!firstName.empty()) strcpy_s(arr[i].ownerFirstName, firstName.c_str());

            cout << "Enter new owner last name (" << arr[i].ownerLastName << "): ";
            string lastName;
            getline(cin, lastName);
            if (!lastName.empty()) strcpy_s(arr[i].ownerLastName, lastName.c_str());

            cout << "\nSelect new card type (" << static_cast<int>(arr[i].type) << "):\n";
            cout << "0 - Bronze\n";
            cout << "1 - Silver\n";
            cout << "2 - Gold\n";
            cout << "Enter choice: ";

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
    displayReceipts(loadedReceipts, loadedReceiptCount);
    int number;
    cout << "Enter receipt number to edit (0 to cancel): ";
    cin >> number;

    if (number == 0) {
        cout << "\033[33mEdit cancelled.\033[0m\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (arr[i].receiptNumber == number) {
            found = true;
            cout << "\nEditing receipt " << arr[i].receiptNumber << endl;
            cin.ignore();

            string input;

            displayProducts(loadedProducts, loadedProductCount);

            cout << "Enter new product Code (" << arr[i].product.code << "): ";
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

            cout << "Enter new Product quantity (" << arr[i].quantity << "): ";
            getline(cin, input);
            if (!input.empty()) arr[i].quantity = stoi(input);

            cout << "Enter new date (" << arr[i].date << "): ";
            getline(cin, input);
            if (!input.empty()) strcpy_s(arr[i].date, input.c_str());

            displayDiscountCards(loadedCards, loadedCardCount);

            cout << "Enter new discount card number (" << arr[i].card.cardNumber << "): ";
            getline(cin, input);
            if (!input.empty()) arr[i].card.cardNumber = stoi(input);

            saveReceipts(loadedReceipts, loadedReceiptCount, "Receipts.json");
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
        cin >> choice;

        switch (choice) {
        case 1: {
            int viewChoice;
            do {
                showViewDataSubMenu();
                cin >> viewChoice;

                switch (viewChoice) {
                case 1:
                    // Display all data
                    if (loadedProductCount == 0 && loadedEmployeeCount == 0 && loadedCardCount == 0 && loadedReceiptCount == 0) {
                        cout << "\033[1;31m\nNo data available to display!\033[0m\n";
                    }
                    else  displayFullDataResponse(); 
                    break;
                case 2: {
                    // Display part of data
                    int subChoice;
                    do {
                        showViewPartDataSubMenu();
                        cin >> subChoice;

                        switch (subChoice) {
                        case 1:
                            if (loadedProductCount > 0) displayProducts(loadedProducts, loadedProductCount);
                            else cout << "\033[1;31m\nNo products available!\033[0m\n";
                            break;
                        case 2:
                            if (loadedEmployeeCount > 0) displayEmployees(loadedEmployees, loadedEmployeeCount);
                            else cout << "\033[1;31m\nNo employees available!\033[0m\n";
                            break;
                        case 3:
                            if (loadedCardCount > 0) displayDiscountCards(loadedCards, loadedCardCount);
                            else cout << "\033[1;31m\nNo discount cards available!\033[0m\n";
                            break;
                        case 4:
                            if (loadedReceiptCount > 0) displayReceipts(loadedReceipts, loadedReceiptCount);
                            else cout << "\033[1;31m\nNo receipts available!\033[0m\n";
                            break;
                        default:
                            if (subChoice != 5) cout << "\033[1;31m\nInvalid choice!\033[0m\n" << endl;
                        }
                        cout << endl;
                    } while (subChoice != 5);
                    break;
                }
                default:
                    if (viewChoice != 3) cout << "\033[1;31m\nInvalid choice!\033[0m\n" << endl;
                }
                cout << endl;
            } while (viewChoice != 3);
            break;
        }
		case 2: {
			// Display add data submenu
            int addChoice;
            do {
                showAddDataSubMenu();
                cin >> addChoice;
                switch (addChoice) {
                case 1: addProduct(); break;
                case 2: addEmployee(); break;
                case 3: addDiscountCard(); break;
                case 4: addReceipt(); break;
                default:
                    if (addChoice != 5) cout << "\033[1;31m\nInvalid choice!\033[0m\n" << endl;
                }
                cout << endl;
            } while (addChoice != 5);
            break;
        }
        case 3: {
            // Display edit data submenu
            int editChoice;
            do {
                showEditDataMenu();
                cin >> editChoice;

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
                    if (loadedReceiptCount > 0)  editReceipt(loadedReceipts, loadedReceiptCount);
                    else cout << "\033[1;31m\nNo receipts available!\033[0m\n";
                    break;
                default:
                    if (editChoice != 5) cout << "\033[1;31m\nInvalid choice. Try again.\033[0m\n";
                    break;
                }
            } while (editChoice != 5);
            break;
        }
        case 4:
            // Display remove data menu
            int removeChoice;
            do {
                showRemoveDataMenu();
                cin >> removeChoice;

                switch (removeChoice) {
                case 1:
                    if (loadedProductCount > 0) deleteItem(loadedProducts, loadedProductCount, displayProducts, "product");
                    else cout << "\033[1;31m\nNo products available!\033[0m\n";
                    break;
                case 2:
                    if (loadedProductCount > 0) deleteItem(loadedEmployees, loadedEmployeeCount, displayEmployees, "employee");
                    else cout << "\033[1;31m\nNo products available!\033[0m\n";
                    break;
                case 3:
                    if (loadedProductCount > 0) deleteItem(loadedCards, loadedCardCount, displayDiscountCards, "discount card");
                    else cout << "\033[1;31m\nNo products available!\033[0m\n";
                    break;
                case 4:
                    if (loadedProductCount > 0) deleteItem(loadedReceipts, loadedReceiptCount, displayReceipts, "receipt");
                    else cout << "\033[1;31m\nNo products available!\033[0m\n";
                    break;
                default:
                    if (removeChoice != 5) cout << "\033[1;31m\nInvalid choice. Try again.\033[0m\n";
                    break;
                }
            } while (removeChoice != 5);
            break;
		case 5:
			// Search data
        case 6:
			// Save to file and exit
            saveAndExit();
            cout << "\033[1;31m\nExiting program...\033[0m\n" << endl;
            break;
        default:
            cout << "\033[1;31m\nInvalid choice!\033[0m\n" << endl;
        }
        cout << endl;
    } while (choice != 6);
}

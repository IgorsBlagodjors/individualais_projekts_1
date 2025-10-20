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
}

// =============================== HELPER FUNCTIONS ===============================

// Convert string to Category enum
static Category charToCategory(const string& s) {
    if (s == "Food") return Category::Food;
    if (s == "Clothes") return Category::Clothes;
    if (s == "Electronics") return Category::Electronics;
    if (s == "Books") return Category::Books;
    if (s == "HomeAndGarden") return Category::HomeAndGarden;
    return Category::Food;
}

// Convert string to DiscountCardType enum
inline static DiscountCardType charToCardType(const string& s) {
    if (s == "Bronze") return DiscountCardType::Bronze;
    if (s == "Silver") return DiscountCardType::Silver;
    if (s == "Gold") return DiscountCardType::Gold;
    return DiscountCardType::Bronze;
}

// =============================== LOAD FUNCTIONS ===============================

// Load products from JSON file
void loadProducts(const char* filename, Product* arr, int& size) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File " << filename << " not found!\n";
        size = 0;
        return;
    }

    string line;
    int index = 0;

    while (getline(file, line)) {
        if (line.find("\"code\"") != string::npos) {
            int code;
            sscanf_s(line.c_str(), "    \"code\": %d,", &code);
            arr[index].code = code;
        }
        else if (line.find("\"name\"") != string::npos) {
            size_t start = line.find('"', 12) + 1;
            size_t end = line.find('"', start);
            string name = line.substr(start, end - start);
            strcpy_s(arr[index].name, sizeof(arr[index].name), name.c_str());
        }
        else if (line.find("\"price\"") != string::npos) {
            double price;
            sscanf_s(line.c_str(), "    \"price\": %lf,", &price);
            arr[index].price = price;
        }
        else if (line.find("\"quantityInStock\"") != string::npos) {
            int qty;
            sscanf_s(line.c_str(), "    \"quantityInStock\": %d,", &qty);
            arr[index].quantityInStock = qty;
        }
        else if (line.find("\"category\"") != string::npos) {
            size_t start = line.find('"', 14) + 1;
            size_t end = line.find('"', start);
            string cat = line.substr(start, end - start);
            arr[index].category = charToCategory(cat);
            index++;
        }
    }

    size = index;
    cout << "Loaded " << size << " products from " << filename << "\n";
}

// Load employees from JSON file
void loadEmployees(const char* filename, Employee* arr, int& size) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File " << filename << " not found!\n";
        size = 0;
        return;
    }

    string line;
    int index = 0;

    while (getline(file, line)) {
        if (line.find("\"id\"") != string::npos) {
            int id;
            sscanf_s(line.c_str(), "    \"id\": %d,", &id);
            arr[index].id = id;
        }
        else if (line.find("\"firstName\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strcpy_s(arr[index].firstName, sizeof(arr[index].firstName), s.c_str());
        }
        else if (line.find("\"lastName\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strcpy_s(arr[index].lastName, sizeof(arr[index].lastName), s.c_str());
        }
        else if (line.find("\"department\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string dep = line.substr(start, end - start);
            arr[index].department = charToCategory(dep);
            index++;
        }
    }

    size = index;
    cout << "Loaded " << size << " employees from " << filename << "\n";
}

// Load discount cards from JSON file
void loadDiscountCards(const char* filename, DiscountCard* arr, int& size) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File " << filename << " not found!\n";
        size = 0;
        return;
    }

    string line;
    int index = 0;

    while (getline(file, line)) {
        if (line.find("\"cardNumber\"") != string::npos) {
            int num;
            sscanf_s(line.c_str(), "    \"cardNumber\": %d,", &num);
            arr[index].cardNumber = num;
        }
        else if (line.find("\"ownerFirstName\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strcpy_s(arr[index].ownerFirstName, sizeof(arr[index].ownerFirstName), s.c_str());
        }
        else if (line.find("\"ownerLastName\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strcpy_s(arr[index].ownerLastName, sizeof(arr[index].ownerLastName), s.c_str());
        }
        else if (line.find("\"type\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string t = line.substr(start, end - start);

            arr[index].type = charToCardType(t);
            index++;
        }
    }

    size = index;
    cout << "Loaded " << size << " discountCards from " << filename << "\n";
}

// Load receipts from JSON file
void loadReceipts(const char* filename, Receipt* arr, int& size, Product* products, int productSize, DiscountCard* cards, int cardSize) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File " << filename << " not found!\n";
        size = 0;
        return;
    }

    string line;
    int index = 0;

    while (getline(file, line)) {
        if (line.find("\"receiptNumber\"") != string::npos) {
            int num;
            sscanf_s(line.c_str(), "    \"receiptNumber\": %d,", &num);
            arr[index].receiptNumber = num;
        }
        else if (line.find("\"date\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);
            strcpy_s(arr[index].date, sizeof(arr[index].date), s.c_str());
        }
        else if (line.find("\"product\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            string s = line.substr(start, end - start);

            // Find product in array by name
            for (int i = 0; i < productSize; i++) {
                if (s == products[i].name) {
                    arr[index].product = products[i];
                    break;
                }
            }
        }
        else if (line.find("\"quantity\"") != string::npos) {
            int q;
            sscanf_s(line.c_str(), "    \"quantity\": %d,", &q);
            arr[index].quantity = q;
        }
        else if (line.find("\"discountCard\"") != string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            int cardNum = stoi(line.substr(start, end - start));

            // Find discount card in array by number
            for (int i = 0; i < cardSize; i++) {
                if (cards[i].cardNumber == cardNum) {
                    arr[index].card = cards[i];
                    break;
                }
            }
            index++;
        }
    }

    size = index;
    cout << "Loaded " << size << " receipts from " << filename << "\n";
}
// =============================== ARRAY EXPANSION FUNCTIONS ===============================// 

// Products expansion
void expandProductsArray(int newCapacity) {
    Product* temp = new Product[newCapacity];
    for (int i = 0; i < loadedProductCount; i++) temp[i] = loadedProducts[i];
    delete[] loadedProducts;
    loadedProducts = temp;
    loadedProductCapacity = newCapacity;
    cout << "Product array expanded to " << newCapacity << " items!\n";
}

// Employees expansion
void expandEmployeesArray(int newCapacity) {
    Employee* temp = new Employee[newCapacity];
    for (int i = 0; i < loadedEmployeeCount; i++) temp[i] = loadedEmployees[i];
    delete[] loadedEmployees;
    loadedEmployees = temp;
    loadedEmployeeCapacity = newCapacity;
    cout << "Employee array expanded to " << newCapacity << " items!\n";
}

// Discount Cards expansion
void expandCardsArray(int newCapacity) {
    DiscountCard* temp = new DiscountCard[newCapacity];
    for (int i = 0; i < loadedCardCount; i++) temp[i] = loadedCards[i];
    delete[] loadedCards;
    loadedCardCapacity = newCapacity;
    loadedCards = temp;
    cout << "DiscountCard array expanded to " << newCapacity << " items!\n";
}

// Receipts expansion
void expandReceiptsArray(int newCapacity) {
    Receipt* temp = new Receipt[newCapacity];
    for (int i = 0; i < loadedReceiptCount; i++) temp[i] = loadedReceipts[i];
    delete[] loadedReceipts;
    loadedReceiptCapacity = newCapacity;
    loadedReceipts = temp;
    cout << "Receipt array expanded to " << newCapacity << " items!\n";
}

// =============================== ADD FUNCTIONS ===============================// 

// Add Product
void addProduct() {
    if (loadedProductCount >= loadedProductCapacity) {
        expandProductsArray(loadedProductCapacity + 1); 
    }

    Product newProduct;
    cout << "Enter product code: ";
    cin >> newProduct.code;
    cin.ignore();

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

    loadedProducts[loadedProductCount++] = newProduct;
    cout << "Product added successfully!\n";

    saveProducts(loadedProducts, loadedProductCount, "products.json");
    cout << "Products saved to 'products.json' successfully!\n";
}

void addEmployee() {
    if (loadedEmployeeCount >= loadedEmployeeCapacity) {
        expandEmployeesArray(loadedEmployeeCapacity + 1); // увеличиваем на 5
    }

    Employee e;
    cout << "\n=== ADD NEW EMPLOYEE ===\n";
    cout << "Enter employee ID: ";
    cin >> e.id;
    cin.ignore();

    cout << "Enter first name: ";
    cin.getline(e.firstName, 10);

    cout << "Enter last name: ";
    cin.getline(e.lastName, 20);

    int dep;
    cout << "Select department (0-Food,1-Clothes,2-Electronics,3-Books,4-HomeAndGarden): ";
    cin >> dep;
    e.department = static_cast<Category>(dep);

    loadedEmployees[loadedEmployeeCount++] = e;

    cout << "Employee added successfully!\n";
    saveEmployees(loadedEmployees, loadedEmployeeCount, "employees.json");
    cout << "Employees saved to file!\n";
}


// Add DiscountCard
void addDiscountCard() {
    if (loadedCardCount >= loadedCardCapacity) expandCardsArray(loadedCardCapacity + 1);

    DiscountCard c;
    cout << "\nEnter card number: ";
    cin >> c.cardNumber;
    cin.ignore();
    cout << "Enter owner's first name: ";
    cin.getline(c.ownerFirstName, 20);
    cout << "Enter owner's last name: ";
    cin.getline(c.ownerLastName, 30);
    cout << "Select card type (0-Bronze,1-Silver,2-Gold): ";
    int t; cin >> t;
    c.type = static_cast<DiscountCardType>(t);

    loadedCards[loadedCardCount++] = c;
    cout << "Discount card added!\n";
    saveDiscountCards(loadedCards, loadedCardCount, "discountCards.json");
    cout << "Discount cards saved to file!\n";
}

// Add Receipt
void addReceipt() {
    if (loadedReceiptCount >= loadedReceiptCapacity) expandReceiptsArray(loadedReceiptCapacity + 1);

    Receipt r;
    cout << "\nEnter receipt number: ";
    cin >> r.receiptNumber;
    cin.ignore();
    cout << "Enter date (YYYY-MM-DD): ";
    cin.getline(r.date, 12);

    cout << "Select product:\n";
    for (int i = 0; i < loadedProductCount; i++) cout << i + 1 << ". " << loadedProducts[i].name << endl;
    int prodIndex; cin >> prodIndex; r.product = loadedProducts[prodIndex - 1];

    cout << "Enter quantity: ";
    cin >> r.quantity;

    cout << "Select discount card:\n";
    for (int i = 0; i < loadedCardCount; i++) cout << i + 1 << ". " << loadedCards[i].cardNumber << " (" << loadedCards[i].ownerFirstName << ")\n";
    int cardIndex; cin >> cardIndex; r.card = loadedCards[cardIndex - 1];

    loadedReceipts[loadedReceiptCount++] = r;
    cout << "Receipt added!\n";
    saveReceipts(loadedReceipts, loadedReceiptCount, "Receipts.json");
    cout << "Receipts saved to file!\n";
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
                        cout << "\nNo data available to display!\n" << endl;
                    }
                    else {
                        displayFullDataResponse();
                    }
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
                            else cout << "\nNo products available!\n" << endl;
                            break;
                        case 2:
                            if (loadedEmployeeCount > 0) displayEmployees(loadedEmployees, loadedEmployeeCount);
                            else cout << "\nNo employees available!\n" << endl;
                            break;
                        case 3:
                            if (loadedReceiptCount > 0) displayReceipts(loadedReceipts, loadedReceiptCount);
                            else cout << "\nNo receipts available!\n" << endl;
                            break;
                        case 4:
                            if (loadedCardCount > 0) displayDiscountCards(loadedCards, loadedCardCount);
                            else cout << "\nNo discount cards available!\n" << endl;
                            break;
                        default:
                            if (subChoice != 5) cout << "Invalid choice!" << endl;
                        }
                        cout << endl;
                    } while (subChoice != 5);
                    break;
                }

                default:
                    if (viewChoice != 3) cout << "Invalid choice!" << endl;
                }
                cout << endl;
            } while (viewChoice != 3);
            break;
        }
		case 2: {
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
                    if (addChoice != 5) cout << "Invalid choice!" << endl;
                }
                cout << endl;
            } while (addChoice != 5);
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

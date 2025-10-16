#include "Function.h"
#include <fstream>
#include <iomanip>
#include "menu.h"
#include <iostream>
#include "dataView.h"
#include "FakeData.h"
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
static Category charToCategory(const std::string& s) {
    if (s == "Food") return Category::Food;
    if (s == "Clothes") return Category::Clothes;
    if (s == "Electronics") return Category::Electronics;
    if (s == "Books") return Category::Books;
    if (s == "HomeAndGarden") return Category::HomeAndGarden;
    return Category::Food;  
}

inline static DiscountCardType charToCardType(const std::string& s) {
    if (s == "Bronze") return DiscountCardType::Bronze;
    if (s == "Silver") return DiscountCardType::Silver;
    if (s == "Gold") return DiscountCardType::Gold;
    return DiscountCardType::Bronze; 
}

static void loadProducts(const char* filename, Product* arr, int& size) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    int index = 0;

    while (std::getline(file, line)) {
        if (line.find("\"code\"") != std::string::npos) {
            int code;
            sscanf_s(line.c_str(), "    \"code\": %d,", &code);
            arr[index].code = code;
        }
        else if (line.find("\"name\"") != std::string::npos) {
            size_t start = line.find('"', 12) + 1;
            size_t end = line.find('"', start);
            std::string name = line.substr(start, end - start);
            strcpy_s(arr[index].name, sizeof(arr[index].name), name.c_str());
        }
        else if (line.find("\"price\"") != std::string::npos) {
            double price;
            sscanf_s(line.c_str(), "    \"price\": %lf,", &price);
            arr[index].price = price;
        }
        else if (line.find("\"quantityInStock\"") != std::string::npos) {
            int qty;
            sscanf_s(line.c_str(), "    \"quantityInStock\": %d,", &qty);
            arr[index].quantityInStock = qty;
        }
        else if (line.find("\"category\"") != std::string::npos) {
            size_t start = line.find('"', 14) + 1;
            size_t end = line.find('"', start);
            std::string cat = line.substr(start, end - start);
            arr[index].category = charToCategory(cat);
            index++;
        }
    }

    size = index;
}

static void loadEmployees(const char* filename, Employee* arr, int& size) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    int index = 0;

    while (std::getline(file, line)) {
        if (line.find("\"id\"") != std::string::npos) {
            int id;
            sscanf_s(line.c_str(), "    \"id\": %d,", &id);
            arr[index].id = id;
        }
        else if (line.find("\"firstName\"") != std::string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            std::string s = line.substr(start, end - start);
            strcpy_s(arr[index].firstName, sizeof(arr[index].firstName), s.c_str());
        }
        else if (line.find("\"lastName\"") != std::string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            std::string s = line.substr(start, end - start);
            strcpy_s(arr[index].lastName, sizeof(arr[index].lastName), s.c_str());
        }
        else if (line.find("\"department\"") != std::string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            std::string dep = line.substr(start, end - start);
            arr[index].department = charToCategory(dep);
            index++;
        }
    }

    size = index;
}

static void loadDiscountCards(const char* filename, DiscountCard* arr, int& size) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    int index = 0;

    while (std::getline(file, line)) {
        if (line.find("\"cardNumber\"") != std::string::npos) {
            int num;
            sscanf_s(line.c_str(), "    \"cardNumber\": %d,", &num);
            arr[index].cardNumber = num;
        }
        else if (line.find("\"ownerFirstName\"") != std::string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            std::string s = line.substr(start, end - start);
            strcpy_s(arr[index].ownerFirstName, sizeof(arr[index].ownerFirstName), s.c_str());
        }
        else if (line.find("\"ownerLastName\"") != std::string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            std::string s = line.substr(start, end - start);
            strcpy_s(arr[index].ownerLastName, sizeof(arr[index].ownerLastName), s.c_str());
        }
        else if (line.find("\"type\"") != std::string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            std::string t = line.substr(start, end - start);

            if (t == "Bronze") arr[index].type = DiscountCardType::Bronze;
            else if (t == "Silver") arr[index].type = DiscountCardType::Silver;
            else if (t == "Gold") arr[index].type = DiscountCardType::Gold;

            index++;
        }
    }

    size = index;
}

static void loadReceipts(const char* filename, Receipt* arr, int& size, Product* products, int productSize, DiscountCard* cards, int cardSize) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    int index = 0;

    while (std::getline(file, line)) {
        if (line.find("\"receiptNumber\"") != std::string::npos) {
            int num;
            sscanf_s(line.c_str(), "    \"receiptNumber\": %d,", &num);
            arr[index].receiptNumber = num;
        }
        else if (line.find("\"date\"") != std::string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            std::string s = line.substr(start, end - start);
            strcpy_s(arr[index].date, sizeof(arr[index].date), s.c_str());
        }
        else if (line.find("\"product\"") != std::string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            std::string s = line.substr(start, end - start);

            for (int i = 0; i < productSize; i++) {
                if (s == products[i].name) {
                    arr[index].product = products[i];
                    break;
                }
            }
        }
        else if (line.find("\"quantity\"") != std::string::npos) {
            int q;
            sscanf_s(line.c_str(), "    \"quantity\": %d,", &q);
            arr[index].quantity = q;
        }
        else if (line.find("\"discountCard\"") != std::string::npos) {
            size_t colon = line.find(':');
            size_t start = line.find('"', colon) + 1;
            size_t end = line.find('"', start);
            int cardNum = std::stoi(line.substr(start, end - start));

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
}

void runProgramMenu()
{
    loadProducts("products.txt", productss, productSize);
    loadEmployees("employees.txt", employeess, employeeSize);
    loadDiscountCards("discountCards.txt", cardss, cardSize);
    loadReceipts("Receipts.txt", receiptss, receiptSize, productss, productSize, cardss, cardSize);

    std::cout << "Data has been loaded from files!" << std::endl;   
    
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
					displayFullDataResponse();
                    break;
                case 2: {
                    int subChoice;
                    do {
                        showViewPartDataSubMenu();
                        cin >> subChoice;
                        switch (subChoice) {
                        case 1:
							displayProducts(productss, productSize);
                            break;
                        case 2:
							displayEmployees(employeess, employeeSize);
                            break;
                        case 3:
							displayReceipts(receiptss, receiptSize);
                            break;
                        case 4:
							displayDiscountCards(cardss, cardSize);
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

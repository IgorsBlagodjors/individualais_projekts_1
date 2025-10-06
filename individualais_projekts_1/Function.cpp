#include "Function.h"
#include <fstream>
#include <iomanip>

void saveProducts(const Product* arr, int size, const std::string& filename) {
    std::ofstream file(filename);
    file << "[\n";
    for (int i = 0; i < size; i++) {
        file << "  {\n"
            << "    \"code\": " << arr[i].code << ",\n"
            << "    \"name\": \"" << arr[i].name << "\",\n"
            << "    \"price\": " << arr[i].price << ",\n"
            << "    \"category\": \"" << categoryToChar(arr[i].category) << "\"\n"
            << "  }";
        if (i < size - 1) file << ",";
        file << "\n";
    }
    file << "]";
}

void saveEmployees(const Employee* arr, int size, const std::string& filename) {
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

void saveClients(const Client* arr, int size, const std::string& filename) {
    std::ofstream file(filename);
    file << "[\n";
    for (int i = 0; i < size; i++) {
        file << "  {\n"
            << "    \"id\": " << arr[i].id << ",\n"
            << "    \"firstName\": \"" << arr[i].firstName << "\",\n"
            << "    \"lastName\": \"" << arr[i].lastName << "\",\n"
            << "    \"card\": \"" << cardToChar(arr[i].card) << "\"\n"
            << "  }";
        if (i < size - 1) file << ",";
        file << "\n";
    }
    file << "]";
}

void savePurchases(const Purchase* arr, int size, const std::string& filename) {
    std::ofstream file(filename);
    file << "[\n";
    for (int i = 0; i < size; i++) {
        double total = arr[i].product.price * arr[i].quantity;
        double totalWithDiscount = arr[i].getTotal();

        file << "  {\n"
            << "    \"code\": " << arr[i].code << ",\n"
            << "    \"product_name\": \"" << arr[i].product.name << "\",\n"
            << "    \"quantity\": " << arr[i].quantity << ",\n"
            << "    \"date\": \"" << arr[i].date << "\",\n"
            << "    \"total\": " << total << ",\n"
            << "    \"total_with_discount\": " << totalWithDiscount << ",\n"
            << "    \"client\": {\n"
            << "       \"firstName\": \"" << arr[i].client.firstName << "\",\n"
            << "       \"lastName\": \"" << arr[i].client.lastName << "\",\n"
            << "       \"card\": \"" << cardToChar(arr[i].client.card) << "\"\n"
            << "    }\n"
            << "  }";
        if (i < size - 1) file << ",";
        file << "\n";
    }
    file << "]";
}

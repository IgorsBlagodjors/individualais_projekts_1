#pragma once
#include <string>
using namespace std;

enum struct Category : int {
    Food,
    Clothes,
    Electronics,
    Books,
    HomeAndGarden
};

enum struct DiscountCardType : int {
    Bronze,
    Silver,
    Gold
};

inline const char* categoryToChar(Category c) {
    switch (c) {
    case Category::Food: return "Food";
    case Category::Clothes: return "Clothes";
    case Category::Electronics: return "Electronics";
    case Category::Books: return "Books";
    case Category::HomeAndGarden: return "HomeAndGarden";
    default: return "Unknown";
    }
}

inline const char* cardToChar(DiscountCardType c) {
    switch (c) {
    case DiscountCardType::Bronze: return "Bronze";
    case DiscountCardType::Silver: return "Silver";
    case DiscountCardType::Gold: return "Gold";
    default: return "Unknown";
    }
}

inline Category charToCategory(const string& s) {
    if (s == "Food") return Category::Food;
    if (s == "Clothes") return Category::Clothes;
    if (s == "Electronics") return Category::Electronics;
    if (s == "Books") return Category::Books;
    if (s == "HomeAndGarden") return Category::HomeAndGarden;
    return Category::Food;
}

inline DiscountCardType charToCardType(const string& s) {
    if (s == "Bronze") return DiscountCardType::Bronze;
    if (s == "Silver") return DiscountCardType::Silver;
    if (s == "Gold") return DiscountCardType::Gold;
    return DiscountCardType::Bronze; 
}

inline double cardToDiscount(DiscountCardType c) {
    switch (c) {
    case DiscountCardType::Bronze: return 0.05;
    case DiscountCardType::Silver: return 0.07;
    case DiscountCardType::Gold: return 0.10;
    default: return 0.0;
    }
}

struct Product {
    int code;
    char name[50];
    double price;
    int quantityInStock;
    Category category;
};

struct DiscountCard {
    int cardNumber;
    char ownerFirstName[20];
    char ownerLastName[30];
    DiscountCardType type;
};

struct Employee {
    int id;
    char firstName[10];
    char lastName[20];
    Category department;
};

struct Receipt {
    int receiptNumber;
    DiscountCard card;
    Product product;
    int quantity;
    char date[12];

    double getTotalNoDiscount() const {
        return product.price * quantity;
    }

    double getTotalWithDiscount() const {
        double total = getTotalNoDiscount();
        double discount = total * cardToDiscount(card.type);
        return total - discount;
    }

    double getVAT(double rate = 0.21) const {
        return getTotalWithDiscount() * rate;
    }
};

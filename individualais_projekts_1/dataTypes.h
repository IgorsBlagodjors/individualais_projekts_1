#pragma once
#include <string>
#include <vector>
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
    char name[31];
    double price;
    int quantityInStock;
    Category category;
};

struct DiscountCard {
    int cardNumber;
    char ownerFirstName[11];
    char ownerLastName[11];
    DiscountCardType type;
};

struct Employee {
    int id;
    char firstName[11];
    char lastName[11];
    Category department;
};

struct PurchasedProduct {
    Product product;
    int quantity;
};

struct Receipt {
    int receiptNumber;
    DiscountCard card;
    vector<PurchasedProduct > items;
    char date[12];                
    
    // =============================== PROGRAMM CALCULATIONS ===============================

    double getTotalNoDiscount() const {
        double total = 0.0;
        for (const auto& item : items)
            total += item.product.price * item.quantity;
        return total;
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

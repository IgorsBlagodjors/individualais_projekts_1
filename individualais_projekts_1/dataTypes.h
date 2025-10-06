#pragma once
#include <string>

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
    Category category;
};

struct Client {
    int id;
    char firstName[20];
    char lastName[30];
    DiscountCardType card;
};

struct Employee {
    int id;
    char firstName[10];
    char lastName[20];
    Category department;
};

struct Purchase {
    int code;
    Client client;
    Product product;
    int quantity;
    char date[12];

    double getTotal() const {
        double total = product.price * quantity;
        double discount = total * cardToDiscount(client.card);
        return total - discount;
    }
};


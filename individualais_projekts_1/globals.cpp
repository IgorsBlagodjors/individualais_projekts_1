#include "globals.h"

// ======================= Initial Data =======================
Product initialProducts[20] = {
    {1001, "Arabica Coffee 250g", 4.99, 50, Category::Food},
    {1002, "Green Tea", 3.49, 80, Category::Food},
    {1003, "Milk 1L", 1.19, 120, Category::Food},
    {1004, "T-shirt 'Rock'", 19.99, 35, Category::Clothes},
    {1005, "Jeans BlueFit", 49.99, 40, Category::Clothes},
    {1006, "Winter Jacket", 79.99, 20, Category::Clothes},
    {1007, "Bluetooth Headphones", 59.90, 25, Category::Electronics},
    {1008, "Wireless Mouse", 24.50, 60, Category::Electronics},
    {1009, "Smartwatch X2", 99.00, 30, Category::Electronics},
    {1010, "Book 'C++ Basics'", 14.99, 45, Category::Books},
    {1011, "Novel 'Wind Island'", 11.50, 50, Category::Books},
    {1012, "Encyclopedia", 25.00, 15, Category::Books},
    {1013, "Kitchen Towels 3pcs", 5.49, 75, Category::HomeAndGarden},
    {1014, "Aromatic Candle", 3.99, 100, Category::HomeAndGarden},
    {1015, "Pot Set 3pcs", 29.99, 25, Category::HomeAndGarden},
    {1016, "Orange Juice 1L", 2.39, 90, Category::Food},
    {1017, "Chocolate Cookies", 2.99, 70, Category::Food},
    {1018, "Sports Shorts", 22.49, 30, Category::Clothes},
    {1019, "USB Charger", 9.99, 55, Category::Electronics},
    {1020, "Flower Pot", 7.50, 40, Category::HomeAndGarden}
};

DiscountCard initialCards[4] = {
    {10001, "Janis", "Ozols", DiscountCardType::Silver},
    {10002, "Anna", "Kalnina", DiscountCardType::Gold},
    {10003, "Marta", "Liepa", DiscountCardType::Bronze},
    {10004, "Andris", "Eglitis", DiscountCardType::Silver}
};

Employee initialEmployees[5] = {
    {11, "Janis", "Berzins", Category::Food},
    {23, "Anna", "Ozola", Category::Clothes},
    {36, "Martins", "Kalnins", Category::Electronics},
    {41, "Laura", "Liepa", Category::Books},
    {52, "Andris", "Eglitis", Category::HomeAndGarden}
};

Receipt defaultReceipts[4] = {
    {
        5001,
        initialCards[0],
        {
            { initialProducts[0], 2 },
            { initialProducts[16], 1 },
            { initialProducts[17], 3 }
        },
        "2025-09-30"
    },
    {
        5002,
        initialCards[1],
        {
            { initialProducts[7], 1 },
            { initialProducts[8], 1 }
        },
        "2025-10-01"
    },
    {
        5003,
        initialCards[2],
        {
            { initialProducts[10], 3 },
            { initialProducts[11], 1 }
        },
        "2025-10-02"
    },
    {
        5004,
        initialCards[3],
        {
            { initialProducts[18], 5 },
            { initialProducts[19], 2 }
        },
        "2025-10-03"
    }
};

// ======================= Dynamic Arrays =======================

Product* loadedProducts = new Product[20];
int loadedProductCount = 0;
int loadedProductCapacity = 20;

Employee* loadedEmployees = new Employee[5];
int loadedEmployeeCount = 0;
int loadedEmployeeCapacity = 5;

DiscountCard* loadedCards = new DiscountCard[4];
int loadedCardCount = 0;
int loadedCardCapacity = 4;

Receipt* loadedReceipts = new Receipt[4];
int loadedReceiptCount = 0;
int loadedReceiptCapacity = 4;

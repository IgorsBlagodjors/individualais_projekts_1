#include "FakeData.h"
Product products[20] = {
    {1001, "Arabica Coffee 250g", 4.99, Category::Food},
    {1002, "Green Tea", 3.49, Category::Food},
    {1003, "Milk 1L", 1.19, Category::Food},
    {1004, "T-shirt 'Rock'", 19.99, Category::Clothes},
    {1005, "Jeans BlueFit", 49.99, Category::Clothes},
    {1006, "Winter Jacket", 79.99, Category::Clothes},
    {1007, "Bluetooth Headphones", 59.90, Category::Electronics},
    {1008, "Wireless Mouse", 24.50, Category::Electronics},
    {1009, "Smartwatch X2", 99.00, Category::Electronics},
    {1010, "Book 'C++ Basics'", 14.99, Category::Books},
    {1011, "Novel 'Wind Island'", 11.50, Category::Books},
    {1012, "Encyclopedia", 25.00, Category::Books},
    {1013, "Kitchen Towels 3pcs", 5.49, Category::HomeAndGarden},
    {1014, "Aromatic Candle", 3.99, Category::HomeAndGarden},
    {1015, "Pot Set 3pcs", 29.99, Category::HomeAndGarden},
    {1016, "Orange Juice 1L", 2.39, Category::Food},
    {1017, "Chocolate Cookies", 2.99, Category::Food},
    {1018, "Sports Shorts", 22.49, Category::Clothes},
    {1019, "USB Charger", 9.99, Category::Electronics},
    {1020, "Flower Pot", 7.50, Category::HomeAndGarden}
};

Client clients[4] = {
    {1, "Janis", "Ozols", DiscountCardType::Silver},
    {2, "Anna", "Kalnina", DiscountCardType::Gold},
    {3, "Marta", "Liepa", DiscountCardType::Bronze},
    {4, "Andris", "Eglitis", DiscountCardType::Silver}
};

Employee employees[5] = {
    {1, "Janis", "Berzins", Category::Food},
    {2, "Anna", "Ozola", Category::Clothes},
    {3, "Martins", "Kalnins", Category::Electronics},
    {4, "Laura", "Liepa", Category::Books},
    {5, "Andris", "Eglitis", Category::HomeAndGarden}
};

Purchase purchases[4] = {
    {5001, clients[0], products[0], 2, "2025-09-30"},
    {5002, clients[1], products[7], 1, "2025-10-01"},
    {5003, clients[2], products[10], 3, "2025-10-02"},
    {5004, clients[3], products[18], 5, "2025-10-03"}
};

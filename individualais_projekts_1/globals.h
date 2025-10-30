#pragma once
#include "dataTypes.h"
#include <vector>

extern Product initialProducts[20];
extern Employee initialEmployees[5];
extern DiscountCard initialCards[4];
extern Receipt defaultReceipts[4];

extern Product* loadedProducts;
extern int loadedProductCount;
extern int loadedProductCapacity;

extern Employee* loadedEmployees;
extern int loadedEmployeeCount;
extern int loadedEmployeeCapacity;

extern DiscountCard* loadedCards;
extern int loadedCardCount;
extern int loadedCardCapacity;

extern Receipt* loadedReceipts;
extern int loadedReceiptCount;
extern int loadedReceiptCapacity;
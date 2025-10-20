#pragma once
#include "dataTypes.h"


extern Product defaultProducts[20];
extern Employee defaultEmployees[5];
extern DiscountCard defaultCards[4];
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
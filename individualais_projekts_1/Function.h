#pragma once
#include <string>
#include "dataTypes.h"

void saveProducts(const Product* arr, int size, const char* filename);
void saveEmployees(const Employee* arr, int size, const char* filename);
void saveDiscountCards(const DiscountCard* arr, int size, const char* filename);
void saveReceipts(const Receipt* arr, int size, const char* filename);
void runProgramMenu();
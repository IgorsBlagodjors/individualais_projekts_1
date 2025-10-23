#pragma once
#include <string>
#include <fstream>
#include "dataTypes.h"

using namespace std;

void expandEmployeesArray(int newCapacity);
bool fileExists(const string& filename);
void saveProducts(const Product* arr, int size, const char* filename);
void saveEmployees(const Employee* arr, int size, const char* filename);
void saveDiscountCards(const DiscountCard* arr, int size, const char* filename);
void saveReceipts(const Receipt* arr, int size, const char* filename);
void loadEmployees(const char* filename, Employee*& arr, int& size, int& capacity);
void loadProducts(const char* filename, Product*& arr, int& size, int& capacity);
void loadDiscountCards(const char* filename, DiscountCard*& arr, int& size, int& capacity);
void loadReceipts(const char* filename, Receipt*& arr, int& size,
    Product* products, int productSize, DiscountCard* cards, int cardSize,
    int& capacity);
void runProgramMenu();
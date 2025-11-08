#pragma once
#include "dataTypes.h"
#include <fstream>
#include <string>

bool fileExists(const std::string &filename);

void saveProducts(const Product *arr, int size, const char *filename);
void saveEmployees(const Employee *arr, int size, const char *filename);
void saveDiscountCards(const DiscountCard *arr, int size, const char *filename);
void saveReceipts(const Receipt *arr, int size, const char *filename);

void loadProducts(const char *filename, Product *&arr, int &size, int &capacity);
void loadEmployees(const char *filename, Employee *&arr, int &size, int &capacity);
void loadDiscountCards(const char *filename, DiscountCard *&arr, int &size, int &capacity);
void loadReceipts(const char *filename, Receipt *&arr, int &size,
                  Product *products, int productSize, DiscountCard *cards,
                  int cardSize, int &capacity);

void addProduct();
void addEmployee();
void addDiscountCard();
void addReceipt();

void editProduct(Product *arr, int size);
void editEmployee(Employee *arr, int size);
void editDiscountCard(DiscountCard *arr, int size);
void editReceipt(Receipt *arr, int size);

void sortProductsByName(Product *arr, int size);
void sortProductsByPriceAscending(Product *arr, int size);
void sortProductsByPriceDescending(Product *arr, int size);
void sortProductsByQuantityAscending(Product *arr, int size);
void sortProductsByQuantityDescending(Product *arr, int size);

void runProgramMenu();

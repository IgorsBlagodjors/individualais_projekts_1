#include <iostream>
#include <fstream>
#include <iomanip>
#include "Function.h"
#include "globals.h"
using namespace std;

int main() {
	// Save initial data to files
    if (!fileExists("products.json")) {
        saveProducts(initialProducts, 20, "products.json");
    }
    if (!fileExists("employees.json")) {
        saveEmployees(initialEmployees, 5, "employees.json"); 
    }
    if (!fileExists("discountCards.json")) {
        saveDiscountCards(initialCards, 4, "discountCards.json");
    }
    if (!fileExists("Receipts.json")) {
        saveReceipts(defaultReceipts, 4, "Receipts.json");
    }
  
	// Load data from files
    loadProducts("products.json", loadedProducts, loadedProductCount, loadedProductCapacity);
    loadEmployees("employees.json", loadedEmployees, loadedEmployeeCount, loadedEmployeeCapacity);
    loadDiscountCards("discountCards.json", loadedCards, loadedCardCount, loadedCardCapacity);
    loadReceipts("Receipts.json", loadedReceipts, loadedReceiptCount,
        loadedProducts, loadedProductCount,
        loadedCards, loadedCardCount,
        loadedReceiptCapacity);
  
   runProgramMenu();
   delete[] loadedProducts;
   delete[] loadedEmployees;
   delete[] loadedCards;
   delete[] loadedReceipts;
   return 0;
}

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Function.h"
#include "globals.h"

using namespace std;


int main() {
	// Save initial data to files
    saveProducts(defaultProducts, 20, "products.json");
    saveEmployees(defaultEmployees, 5, "employees.json");
    saveDiscountCards(defaultCards, 4, "discountCards.json");
    saveReceipts(defaultReceipts, 4, "Receipts.json");
    cout << "Data has been saved to files!" << endl;
    
	// Load data from files
    loadProducts("products.json", loadedProducts, loadedProductCount);
    loadEmployees("employees.json", loadedEmployees, loadedEmployeeCount);
    loadDiscountCards("discountCards.json", loadedCards, loadedCardCount);
    loadReceipts("Receipts.json", loadedReceipts, loadedReceiptCount, loadedProducts, loadedProductCount, loadedCards, loadedCardCount);


   runProgramMenu();
   return 0;
}

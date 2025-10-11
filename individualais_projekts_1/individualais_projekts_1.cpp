#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include "Function.h"
#include "FakeData.h"

int main() {

    saveProducts(products, 20, "products.txt");
    saveEmployees(employees, 5, "employees.txt");
    saveDiscountCards(cards, 4, "discountCards.txt");
    saveReceipts(receipts, 4, "Receipts.txt");
    cout << "Data has been saved to files!" << endl;


   runProgramMenu();
   return 0;
}

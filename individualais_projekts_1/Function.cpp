#include "Function.h"
#include <fstream>
#include <iomanip>

void savePreces(const Prece* arr, int size, const std::string& filename) {
    std::ofstream file(filename);
    for (int i = 0; i < size; i++) {
        file << arr[i].kods << ", "
            << arr[i].nosaukums << ", "
            << std::fixed << std::setprecision(2) << arr[i].cena << ", "
            << kategorijaToString(arr[i].kategorija) << "\n";
    }
}

void saveDarbinieki(const Darbinieks* arr, int size, const std::string& filename) {
    std::ofstream file(filename);
    for (int i = 0; i < size; i++) {
        file << arr[i].id << ", "
            << arr[i].vards << ", "
            << arr[i].uzvards << ", "
            << kategorijaToString(arr[i].kategorija) << "\n";
    }
}

void savePirkumi(const Pirkums* arr, int size, const std::string& filename) {
    std::ofstream file(filename);
    for (int i = 0; i < size; i++) {
        file << arr[i].kods << ", "
            << arr[i].prece.kods << ", "
            << arr[i].prece.nosaukums << ", "
            << arr[i].daudzums << ", "
            << arr[i].datums << ", "
            << std::fixed << std::setprecision(2) << arr[i].getSumma() << "\n";
    }
}

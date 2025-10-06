#pragma once
#include <string>
#include "dataTypes.h"

void saveProducts(const Product* arr, int size, const std::string& filename);
void saveEmployees(const Employee* arr, int size, const std::string& filename);
void saveClients(const Client* arr, int size, const std::string& filename);
void savePurchases(const Purchase* arr, int size, const std::string& filename);

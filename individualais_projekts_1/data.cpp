#include "data.h"

Prece preces[20] = {
    {1001, "Kafija Arabica 250g", 4.99, Kategorija::PartikasPreces},
    {1002, "Teja zala", 3.49, Kategorija::PartikasPreces},
    {1003, "Piens 1L", 1.19, Kategorija::PartikasPreces},
    {1004, "T-kreks 'Rock'", 19.99, Kategorija::Apgerbi},
    {1005, "Dzins BlueFit", 49.99, Kategorija::Apgerbi},
    {1006, "Jaka ziemas", 79.99, Kategorija::Apgerbi},
    {1007, "Bluetooth austinjas", 59.90, Kategorija::Elektronika},
    {1008, "Bezvadu pele", 24.50, Kategorija::Elektronika},
    {1009, "Viedpulkstenis X2", 99.00, Kategorija::Elektronika},
    {1010, "Gramata 'C++ pamati'", 14.99, Kategorija::Gramatas},
    {1011, "Romans 'Veja ena'", 11.50, Kategorija::Gramatas},
    {1012, "Enciklopedija", 25.00, Kategorija::Gramatas},
    {1013, "Virtuves dvieli 3gab", 5.49, Kategorija::MajaiUnDarzam},
    {1014, "Svece aromatiska", 3.99, Kategorija::MajaiUnDarzam},
    {1015, "Podu komplekts 3gab", 29.99, Kategorija::MajaiUnDarzam},
    {1016, "Sula apelsinu 1L", 2.39, Kategorija::PartikasPreces},
    {1017, "Cepumi ar sokoladi", 2.99, Kategorija::PartikasPreces},
    {1018, "Sporta sorti", 22.49, Kategorija::Apgerbi},
    {1019, "USB ladejajs", 9.99, Kategorija::Elektronika},
    {1020, "Ziedu pods", 7.50, Kategorija::MajaiUnDarzam}
};

Darbinieks darbinieki[5] = {
    {1, "Janis", "Berzins", Kategorija::PartikasPreces},
    {2, "Anna", "Ozola", Kategorija::Apgerbi},
    {3, "Martins", "Kalnins", Kategorija::Elektronika},
    {4, "Laura", "Liepa", Kategorija::Gramatas},
    {5, "Andris", "Eglitis", Kategorija::MajaiUnDarzam}
};

Pirkums pirkumi[4] = {
    {5001, preces[0], 2, "2025-09-30"},
    {5002, preces[7], 1, "2025-10-01"},
    {5003, preces[10], 3, "2025-10-02"},
    {5004, preces[18], 5, "2025-10-03"}
};

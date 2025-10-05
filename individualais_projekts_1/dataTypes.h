#pragma once
#include <string>

enum struct Kategorija : int {
    PartikasPreces,
    Apgerbi,
    Elektronika,
    Gramatas,
    MajaiUnDarzam
};

struct Prece {
    int kods;
    char nosaukums[50];
    double cena;
    Kategorija kategorija;
};

struct Darbinieks {
    int id;
    char vards[10];
    char uzvards[20];
    Kategorija kategorija;
};

struct Pirkums {
    int kods;
    Prece prece;
    int daudzums;
    char datums[12];

    double getSumma() const { return prece.cena * daudzums; }
};

// inline чтобы не было повторного определения
inline std::string kategorijaToString(Kategorija k) {
    switch (k) {
    case Kategorija::PartikasPreces: return "PartikasPreces";
    case Kategorija::Apgerbi: return "Apgerbi";
    case Kategorija::Elektronika: return "Elektronika";
    case Kategorija::Gramatas: return "Gramatas";
    case Kategorija::MajaiUnDarzam: return "MajaiUnDarzam";
    default: return "Nezinama";
    }
}

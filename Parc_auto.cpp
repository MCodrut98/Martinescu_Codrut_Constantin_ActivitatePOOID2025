#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Vehicul {
protected:
    char* marca;
    int anFabricatie;
    float vitezaMaxima;

public:
    Vehicul() {
        this->marca = new char[8];
        strcpy(this->marca, "Unknown");
        this->anFabricatie = 2000;
        this->vitezaMaxima = 0;
    }

    Vehicul(const char* marca, int an, float viteza) {
        this->marca = new char[strlen(marca) + 1];
        strcpy(this->marca, marca);
        this->anFabricatie = an;
        this->vitezaMaxima = viteza;
    }

    Vehicul(const Vehicul& v) {
        this->marca = new char[strlen(v.marca) + 1];
        strcpy(this->marca, v.marca);
        this->anFabricatie = v.anFabricatie;
        this->vitezaMaxima = v.vitezaMaxima;
    }

    Vehicul& operator=(const Vehicul& v) {
        if (this != &v) {
            if (this->marca != NULL) delete[] this->marca;
            this->marca = new char[strlen(v.marca) + 1];
            strcpy(this->marca, v.marca);
            this->anFabricatie = v.anFabricatie;
            this->vitezaMaxima = v.vitezaMaxima;
        }
        return *this;
    }

    virtual ~Vehicul() {
        if (this->marca != NULL) {
            delete[] this->marca;
        }
        cout << "Destructor Vehicul apelat." << endl;
    }

    virtual void afiseazaDetalii() {
        cout << "Vehicul Marca: " << this->marca
            << " | An: " << this->anFabricatie
            << " | Viteza Max: " << this->vitezaMaxima << " km/h";
    }

    virtual float calculeazaImpozit() {
        return 50.0f;
    }
};

class Automobil : public Vehicul {
private:
    int nrUsi;
    bool esteElectric;

public:
    Automobil() : Vehicul() {
        this->nrUsi = 4;
        this->esteElectric = false;
    }

    Automobil(const char* marca, int an, float viteza, int usi, bool electric)
        : Vehicul(marca, an, viteza) {
        this->nrUsi = usi;
        this->esteElectric = electric;
    }

    Automobil(const Automobil& a) : Vehicul(a) {
        this->nrUsi = a.nrUsi;
        this->esteElectric = a.esteElectric;
    }

    ~Automobil() {
        cout << "Destructor Automobil apelat." << endl;
    }

    Automobil& operator=(const Automobil& a) {
        if (this != &a) {
            Vehicul::operator=(a);
            this->nrUsi = a.nrUsi;
            this->esteElectric = a.esteElectric;
        }
        return *this;
    }

    void afiseazaDetalii() override {
        Vehicul::afiseazaDetalii();
        cout << " | Tip: Automobil | Usi: " << this->nrUsi
            << " | Motor: " << (this->esteElectric ? "Electric" : "Termic") << endl;
    }

    float calculeazaImpozit() override {
        if (this->esteElectric) return 0.0f;
        return 150.0f;
    }
};

class Camion : public Vehicul {
private:
    float tonaj;
    int nrAxe;

public:
    Camion() : Vehicul() {
        this->tonaj = 0;
        this->nrAxe = 2;
    }

    Camion(const char* marca, int an, float viteza, float tonaj, int axe)
        : Vehicul(marca, an, viteza) {
        this->tonaj = tonaj;
        this->nrAxe = axe;
    }

    Camion(const Camion& c) : Vehicul(c) {
        this->tonaj = c.tonaj;
        this->nrAxe = c.nrAxe;
    }

    ~Camion() {
        cout << "Destructor Camion apelat." << endl;
    }

    Camion& operator=(const Camion& c) {
        if (this != &c) {
            Vehicul::operator=(c);
            this->tonaj = c.tonaj;
            this->nrAxe = c.nrAxe;
        }
        return *this;
    }

    void afiseazaDetalii() override {
        Vehicul::afiseazaDetalii();
        cout << " | Tip: Camion | Tonaj: " << this->tonaj
            << " tone | Axe: " << this->nrAxe << endl;
    }

    float calculeazaImpozit() override {
        return 100.0f * this->tonaj;
    }
};

void main() {
    Vehicul* parcAuto[3];

    parcAuto[0] = new Automobil("Tesla Model 3", 2022, 230, 4, true);
    parcAuto[1] = new Automobil("BMW Seria 3", 2018, 240, 4, false);
    parcAuto[2] = new Camion("Volvo FH", 2020, 110, 20.5, 4);

    cout << "=== AFISARE PARC AUTO (POLIMORFISM) ===" << endl;
    for (int i = 0; i < 3; i++) {
        parcAuto[i]->afiseazaDetalii();
    }

    cout << endl << "=== CALCUL IMPOZITE ===" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Impozit vehicul " << i + 1 << ": " << parcAuto[i]->calculeazaImpozit() << " RON" << endl;
    }

    cout << endl << "=== DEZALOCARE MEMORIE (DESTRUCTOR VIRTUAL) ===" << endl;
    for (int i = 0; i < 3; i++) {
        delete parcAuto[i];
        cout << "---" << endl;
    }
}
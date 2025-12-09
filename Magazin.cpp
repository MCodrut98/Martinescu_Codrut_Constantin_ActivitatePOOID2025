#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Produs {
private:
    char* denumire;
    float pret;
    int stoc;

public:
    Produs() {
        this->denumire = new char[8];
        strcpy(this->denumire, "Anonim");
        this->pret = 0;
        this->stoc = 0;
    }

    Produs(const char* denumire, float pret, int stoc) {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy(this->denumire, denumire);
        this->pret = pret;
        this->stoc = stoc;
    }

    Produs(const Produs& p) {
        this->denumire = new char[strlen(p.denumire) + 1];
        strcpy(this->denumire, p.denumire);
        this->pret = p.pret;
        this->stoc = p.stoc;
    }

    ~Produs() {
        if (this->denumire != NULL) {
            delete[] this->denumire;
        }
    }

    Produs& operator=(const Produs& p) {
        if (this != &p) {
            if (this->denumire != NULL) {
                delete[] this->denumire;
            }
            this->denumire = new char[strlen(p.denumire) + 1];
            strcpy(this->denumire, p.denumire);
            this->pret = p.pret;
            this->stoc = p.stoc;
        }
        return *this;
    }

    void salvareFisierText(const char* numeFisier) {
        ofstream f(numeFisier);
        if (f.is_open()) {
            f << this->denumire << endl;
            f << this->pret << endl;
            f << this->stoc << endl;
            f.close();
        }
    }

    void citireFisierText(const char* numeFisier) {
        ifstream f(numeFisier);
        if (f.is_open()) {
            char buffer[100];
            f >> buffer;
            if (this->denumire != NULL) {
                delete[] this->denumire;
            }
            this->denumire = new char[strlen(buffer) + 1];
            strcpy(this->denumire, buffer);

            f >> this->pret;
            f >> this->stoc;
            f.close();
        }
    }

    friend ostream& operator<<(ostream& out, const Produs& p) {
        out << "Produs: " << p.denumire << " | Pret: " << p.pret << " | Stoc: " << p.stoc;
        return out;
    }
};

class Client {
private:
    char* nume;
    int puncteFidelitate;

public:
    Client() {
        this->nume = new char[8];
        strcpy(this->nume, "ClientX");
        this->puncteFidelitate = 0;
    }

    Client(const char* nume, int puncte) {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->puncteFidelitate = puncte;
    }

    Client(const Client& c) {
        this->nume = new char[strlen(c.nume) + 1];
        strcpy(this->nume, c.nume);
        this->puncteFidelitate = c.puncteFidelitate;
    }

    ~Client() {
        if (this->nume != NULL) {
            delete[] this->nume;
        }
    }

    Client& operator=(const Client& c) {
        if (this != &c) {
            if (this->nume != NULL) {
                delete[] this->nume;
            }
            this->nume = new char[strlen(c.nume) + 1];
            strcpy(this->nume, c.nume);
            this->puncteFidelitate = c.puncteFidelitate;
        }
        return *this;
    }

    void salvareFisierBinar(const char* numeFisier) {
        ofstream f(numeFisier, ios::binary);
        if (f.is_open()) {
            int lungime = strlen(this->nume) + 1;
            f.write((char*)&lungime, sizeof(int));
            f.write(this->nume, lungime);
            f.write((char*)&this->puncteFidelitate, sizeof(int));
            f.close();
        }
    }

    void citireFisierBinar(const char* numeFisier) {
        ifstream f(numeFisier, ios::binary);
        if (f.is_open()) {
            int lungime;
            f.read((char*)&lungime, sizeof(int));

            if (this->nume != NULL) {
                delete[] this->nume;
            }
            this->nume = new char[lungime];
            f.read(this->nume, lungime);

            f.read((char*)&this->puncteFidelitate, sizeof(int));
            f.close();
        }
    }

    friend ostream& operator<<(ostream& out, const Client& c) {
        out << "Client: " << c.nume << " | Puncte: " << c.puncteFidelitate;
        return out;
    }
};

class Magazin {
private:
    char* locatie;
    int nrProduse;
    Produs* listaProduse;

public:
    Magazin() {
        this->locatie = new char[7];
        strcpy(this->locatie, "Online");
        this->nrProduse = 0;
        this->listaProduse = NULL;
    }

    Magazin(const char* locatie, int nr, Produs* produse) {
        this->locatie = new char[strlen(locatie) + 1];
        strcpy(this->locatie, locatie);
        this->nrProduse = nr;
        this->listaProduse = new Produs[nr];
        for (int i = 0; i < nr; i++) {
            this->listaProduse[i] = produse[i];
        }
    }

    ~Magazin() {
        if (this->locatie != NULL) delete[] this->locatie;
        if (this->listaProduse != NULL) delete[] this->listaProduse;
    }

    friend ostream& operator<<(ostream& out, const Magazin& m) {
        out << "Magazin " << m.locatie << " are " << m.nrProduse << " produse.";
        return out;
    }
};

void main() {
    Produs p1("Laptop", 2500.5, 10);
    Produs p2;

    cout << "--- TESTARE FISIER TEXT ---" << endl;
    cout << "Original: " << p1 << endl;

    p1.salvareFisierText("produs.txt");
    p2.citireFisierText("produs.txt");

    cout << "Citit din fisier: " << p2 << endl;
    cout << endl;

    Client c1("Ion Popescu", 500);
    Client c2;

    cout << "--- TESTARE FISIER BINAR ---" << endl;
    cout << "Original: " << c1 << endl;

    c1.salvareFisierBinar("client.bin");
    c2.citireFisierBinar("client.bin");

    cout << "Citit din binar: " << c2 << endl;
    cout << endl;

    Produs vectorProduse[] = { p1, p2 };
    Magazin m1("Bucuresti", 2, vectorProduse);
    cout << "--- TESTARE MAGAZIN ---" << endl;
    cout << m1 << endl;
}
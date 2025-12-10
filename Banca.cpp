#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class ContBancar {
protected:
    char* iban;
    char* titular;
    float sold;

public:
    ContBancar() {
        this->iban = new char[5];
        strcpy(this->iban, "None");
        this->titular = new char[8];
        strcpy(this->titular, "Anonim");
        this->sold = 0;
    }

    ContBancar(const char* iban, const char* titular, float sold) {
        this->iban = new char[strlen(iban) + 1];
        strcpy(this->iban, iban);
        this->titular = new char[strlen(titular) + 1];
        strcpy(this->titular, titular);
        this->sold = sold;
    }

    ContBancar(const ContBancar& c) {
        this->iban = new char[strlen(c.iban) + 1];
        strcpy(this->iban, c.iban);
        this->titular = new char[strlen(c.titular) + 1];
        strcpy(this->titular, c.titular);
        this->sold = c.sold;
    }

    ~ContBancar() {
        if (this->iban != NULL) delete[] this->iban;
        if (this->titular != NULL) delete[] this->titular;
    }

    ContBancar& operator=(const ContBancar& c) {
        if (this != &c) {
            if (this->iban != NULL) delete[] this->iban;
            if (this->titular != NULL) delete[] this->titular;

            this->iban = new char[strlen(c.iban) + 1];
            strcpy(this->iban, c.iban);
            this->titular = new char[strlen(c.titular) + 1];
            strcpy(this->titular, c.titular);
            this->sold = c.sold;
        }
        return *this;
    }

    void afisare() {
        cout << "Cont IBAN: " << this->iban << " | Titular: " << this->titular << " | Sold: " << this->sold << " RON" << endl;
    }

    float getSold() { return this->sold; }
};

class ContEconomii : public ContBancar {
private:
    float rataDobanda;
    int perioadaLuni;

public:
    ContEconomii() : ContBancar() {
        this->rataDobanda = 0;
        this->perioadaLuni = 0;
    }

    ContEconomii(const char* iban, const char* titular, float sold, float dobanda, int luni)
        : ContBancar(iban, titular, sold) {
        this->rataDobanda = dobanda;
        this->perioadaLuni = luni;
    }

    ContEconomii(const ContEconomii& c) : ContBancar(c) {
        this->rataDobanda = c.rataDobanda;
        this->perioadaLuni = c.perioadaLuni;
    }

    ~ContEconomii() {
    }

    ContEconomii& operator=(const ContEconomii& c) {
        if (this != &c) {
            ContBancar::operator=(c);
            this->rataDobanda = c.rataDobanda;
            this->perioadaLuni = c.perioadaLuni;
        }
        return *this;
    }

    void adaugaDobanda() {
        this->sold += this->sold * (this->rataDobanda / 100);
        cout << "Dobanda aplicata! Sold nou: " << this->sold << endl;
    }

    void afisareDetaliiEconomii() {
        this->afisare();
        cout << "   -> Tip: Economii | Dobanda: " << this->rataDobanda << "% | Perioada: " << this->perioadaLuni << " luni" << endl;
    }
};

class ContCredit : public ContBancar {
private:
    float limitaCredit;
    float comisionRetragere;

public:
    ContCredit() : ContBancar() {
        this->limitaCredit = 0;
        this->comisionRetragere = 0;
    }

    ContCredit(const char* iban, const char* titular, float sold, float limita, float comision)
        : ContBancar(iban, titular, sold) {
        this->limitaCredit = limita;
        this->comisionRetragere = comision;
    }

    ContCredit(const ContCredit& c) : ContBancar(c) {
        this->limitaCredit = c.limitaCredit;
        this->comisionRetragere = c.comisionRetragere;
    }

    ~ContCredit() {
    }

    ContCredit& operator=(const ContCredit& c) {
        if (this != &c) {
            ContBancar::operator=(c);
            this->limitaCredit = c.limitaCredit;
            this->comisionRetragere = c.comisionRetragere;
        }
        return *this;
    }

    void retrageNumerar(float suma) {
        if (suma + this->comisionRetragere <= this->sold + this->limitaCredit) {
            this->sold -= (suma + this->comisionRetragere);
            cout << "Retragere reusita: " << suma << ". Sold ramas: " << this->sold << endl;
        }
        else {
            cout << "Fonduri insuficiente (inclusiv credit)!" << endl;
        }
    }

    void afisareDetaliiCredit() {
        this->afisare();
        cout << "   -> Tip: Credit | Limita: " << this->limitaCredit << " | Comision: " << this->comisionRetragere << endl;
    }
};

void main() {
    cout << "=== CONT BANCAR (BAZA) ===" << endl;
    ContBancar cb1("RO01GEN", "Ion Popescu", 1000);
    cb1.afisare();
    cout << endl;

    cout << "=== CONT ECONOMII (DERIVATA) ===" << endl;
    ContEconomii ce1("RO02ECO", "Maria Ionescu", 5000, 3.5, 12);
    ce1.afisareDetaliiEconomii();
    ce1.adaugaDobanda();
    cout << endl;

    cout << "=== CONT CREDIT (DERIVATA) ===" << endl;
    ContCredit cc1("RO03CRD", "Andrei Radu", 200, 1000, 5);
    cc1.afisareDetaliiCredit();
    cc1.retrageNumerar(500);
    cout << endl;

    cout << "=== UPCASTING ===" << endl;
    ContBancar* pointerBaza;
    ContEconomii economiiUp("RO99UP", "Test Upcast", 2000, 5.0, 24);

    pointerBaza = &economiiUp;

    pointerBaza->afisare();

    cout << "Sold accesat prin pointer baza: " << pointerBaza->getSold() << endl;
}
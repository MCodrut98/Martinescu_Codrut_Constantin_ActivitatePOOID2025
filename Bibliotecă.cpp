#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Autor {
private:
    char* nume;
    int varsta;

public:
    Autor() {
        this->nume = new char[8];
        strcpy(this->nume, "Anonim");
        this->varsta = 0;
    }

    Autor(const char* nume, int varsta) {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->varsta = varsta;
    }

    Autor(const Autor& a) {
        this->nume = new char[strlen(a.nume) + 1];
        strcpy(this->nume, a.nume);
        this->varsta = a.varsta;
    }

    ~Autor() {
        if (this->nume != NULL) delete[] this->nume;
    }

    Autor& operator=(const Autor& a) {
        if (this != &a) {
            if (this->nume != NULL) delete[] this->nume;
            this->nume = new char[strlen(a.nume) + 1];
            strcpy(this->nume, a.nume);
            this->varsta = a.varsta;
        }
        return *this;
    }

    const char* getNume() { return this->nume; }

    void setNume(const char* numeNou) {
        if (strlen(numeNou) >= 3) {
            if (this->nume != NULL) delete[] this->nume;
            this->nume = new char[strlen(numeNou) + 1];
            strcpy(this->nume, numeNou);
        }
    }

    int getVarsta() { return this->varsta; }

    friend ostream& operator<<(ostream& out, const Autor& a) {
        out << a.nume << " (" << a.varsta << " ani)";
        return out;
    }
};

class Carte {
private:
    char* titlu;
    float pret;
    int anPublicare;

public:
    Carte() {
        this->titlu = new char[11];
        strcpy(this->titlu, "Fara Titlu");
        this->pret = 0;
        this->anPublicare = 2000;
    }

    Carte(const char* titlu, float pret, int an) {
        this->titlu = new char[strlen(titlu) + 1];
        strcpy(this->titlu, titlu);
        this->pret = pret;
        this->anPublicare = an;
    }

    Carte(const Carte& c) {
        this->titlu = new char[strlen(c.titlu) + 1];
        strcpy(this->titlu, c.titlu);
        this->pret = c.pret;
        this->anPublicare = c.anPublicare;
    }

    ~Carte() {
        if (this->titlu != NULL) delete[] this->titlu;
    }

    Carte& operator=(const Carte& c) {
        if (this != &c) {
            if (this->titlu != NULL) delete[] this->titlu;
            this->titlu = new char[strlen(c.titlu) + 1];
            strcpy(this->titlu, c.titlu);
            this->pret = c.pret;
            this->anPublicare = c.anPublicare;
        }
        return *this;
    }

    float getPret() { return this->pret; }

    void setPret(float pretNou) {
        if (pretNou >= 0) this->pret = pretNou;
    }

    const char* getTitlu() { return this->titlu; }

    friend ostream& operator<<(ostream& out, const Carte& c) {
        out << "'" << c.titlu << "' - " << c.pret << " RON";
        return out;
    }
};

class Biblioteca {
private:
    char* adresa;
    Autor fondator;
    Carte* colectieCarti;
    int nrCarti;

public:
    Biblioteca() : fondator("Necunoscut", 0) {
        this->adresa = new char[10];
        strcpy(this->adresa, "Online");
        this->nrCarti = 0;
        this->colectieCarti = NULL;
    }

    Biblioteca(const char* adresa, Autor a) : fondator(a) {
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
        this->nrCarti = 0;
        this->colectieCarti = NULL;
    }

    Biblioteca(const Biblioteca& b) : fondator(b.fondator) {
        this->adresa = new char[strlen(b.adresa) + 1];
        strcpy(this->adresa, b.adresa);
        this->nrCarti = b.nrCarti;

        if (b.nrCarti > 0) {
            this->colectieCarti = new Carte[b.nrCarti];
            for (int i = 0; i < b.nrCarti; i++) {
                this->colectieCarti[i] = b.colectieCarti[i];
            }
        }
        else {
            this->colectieCarti = NULL;
        }
    }

    ~Biblioteca() {
        if (this->adresa != NULL) delete[] this->adresa;
        if (this->colectieCarti != NULL) delete[] this->colectieCarti;
    }

    Biblioteca& operator=(const Biblioteca& b) {
        if (this != &b) {
            if (this->adresa != NULL) delete[] this->adresa;
            if (this->colectieCarti != NULL) delete[] this->colectieCarti;

            this->adresa = new char[strlen(b.adresa) + 1];
            strcpy(this->adresa, b.adresa);
            this->fondator = b.fondator;
            this->nrCarti = b.nrCarti;

            if (b.nrCarti > 0) {
                this->colectieCarti = new Carte[b.nrCarti];
                for (int i = 0; i < b.nrCarti; i++) {
                    this->colectieCarti[i] = b.colectieCarti[i];
                }
            }
            else {
                this->colectieCarti = NULL;
            }
        }
        return *this;
    }

    Biblioteca& operator+=(const Carte& c) {
        Carte* temp = new Carte[this->nrCarti + 1];
        for (int i = 0; i < this->nrCarti; i++) {
            temp[i] = this->colectieCarti[i];
        }
        temp[this->nrCarti] = c;

        if (this->colectieCarti != NULL) delete[] this->colectieCarti;
        this->colectieCarti = temp;
        this->nrCarti++;
        return *this;
    }

    Autor getFondator() { return this->fondator; }

    void setFondator(Autor a) {
        this->fondator = a;
    }

    void afisareInventar() {
        cout << "---------------------------------------" << endl;
        cout << "Biblioteca din: " << this->adresa << endl;
        cout << "Fondator: " << this->fondator << endl;
        cout << "Carti disponibile (" << this->nrCarti << "):" << endl;
        for (int i = 0; i < this->nrCarti; i++) {
            cout << "  " << i + 1 << ". " << this->colectieCarti[i] << endl;
        }
        cout << "---------------------------------------" << endl;
    }
};

void main() {
    Autor a1("Mihai Eminescu", 39);
    Carte c1("Poezii", 45.5, 1883);
    Carte c2("Fat-Frumos din lacrima", 30.0, 1870);

    cout << "=== CREARE BIBLIOTECA ===" << endl;
    Biblioteca b1("Bucuresti, Centrul Vechi", a1);

    b1 += c1;
    b1 += c2;
    b1 += Carte("Luceafarul", 25.0, 1883);

    b1.afisareInventar();

    cout << endl << "=== MODIFICARE FONDATOR ===" << endl;
    Autor a2("Ion Creanga", 52);
    b1.setFondator(a2);

    Autor f = b1.getFondator();
    cout << "Noul fondator extras: " << f.getNume() << endl;

    cout << endl << "=== TESTARE COPIE BIBLIOTECA ===" << endl;
    Biblioteca b2 = b1;
    b2 += Carte("Amintiri din copilarie", 50.0, 1892);

    cout << "Inventar B1 (Original):" << endl;
    b1.afisareInventar();

    cout << endl << "Inventar B2 (Copie cu o carte in plus):" << endl;
    b2.afisareInventar();
}
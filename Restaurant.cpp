#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Preparat {
private:
    const int idPreparat;
    static int contorPreparate;
    char* denumire;
    float pret;
    int calorii;

public:
    Preparat() : idPreparat(++contorPreparate) {
        this->denumire = new char[11];
        strcpy(this->denumire, "Necunoscut");
        this->pret = 0;
        this->calorii = 0;
    }

    Preparat(const char* denumire, float pret, int calorii) : idPreparat(++contorPreparate) {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy(this->denumire, denumire);
        this->pret = pret;
        this->calorii = calorii;
    }

    Preparat(const Preparat& p) : idPreparat(++contorPreparate) {
        this->denumire = new char[strlen(p.denumire) + 1];
        strcpy(this->denumire, p.denumire);
        this->pret = p.pret;
        this->calorii = p.calorii;
    }

    ~Preparat() {
        if (this->denumire != NULL) {
            delete[] this->denumire;
        }
    }

    const char* getDenumire() {
        return this->denumire;
    }

    void setDenumire(const char* nouaDenumire) {
        if (strlen(nouaDenumire) > 2) {
            if (this->denumire != NULL) {
                delete[] this->denumire;
            }
            this->denumire = new char[strlen(nouaDenumire) + 1];
            strcpy(this->denumire, nouaDenumire);
        }
    }

    float getPret() {
        return this->pret;
    }

    void setPret(float pretNou) {
        if (pretNou > 0) {
            this->pret = pretNou;
        }
    }

    int getCalorii() {
        return this->calorii;
    }

    static int getContor() {
        return contorPreparate;
    }

    friend void aplicaReducere(Preparat& p, int procent);
};
int Preparat::contorPreparate = 0;

class Bucatar {
private:
    const int idAngajat;
    static float salariuBaza;
    char* nume;
    int steleMichelin;

public:
    Bucatar() : idAngajat(0) {
        this->nume = new char[7];
        strcpy(this->nume, "Anonim");
        this->steleMichelin = 0;
    }

    Bucatar(int id, const char* nume, int stele) : idAngajat(id) {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->steleMichelin = stele;
    }

    Bucatar(const Bucatar& b) : idAngajat(b.idAngajat) {
        this->nume = new char[strlen(b.nume) + 1];
        strcpy(this->nume, b.nume);
        this->steleMichelin = b.steleMichelin;
    }

    ~Bucatar() {
        if (this->nume != NULL) {
            delete[] this->nume;
        }
    }

    const char* getNume() {
        return this->nume;
    }

    void setNume(const char* numeNou) {
        if (strlen(numeNou) > 2) {
            if (this->nume != NULL) {
                delete[] this->nume;
            }
            this->nume = new char[strlen(numeNou) + 1];
            strcpy(this->nume, numeNou);
        }
    }

    int getStele() {
        return this->steleMichelin;
    }

    static void setSalariuBaza(float salariu) {
        if (salariu > 0) {
            salariuBaza = salariu;
        }
    }

    static float getSalariuBaza() {
        return salariuBaza;
    }

    friend void promoveazaBucatar(Bucatar& b);
};
float Bucatar::salariuBaza = 4000.0;

class Meniu {
private:
    const int anValabilitate;
    static int meniuriCreate;
    float* preturi;
    int nrPreparate;
    bool esteVegetarian;

public:
    Meniu() : anValabilitate(2023) {
        this->preturi = NULL;
        this->nrPreparate = 0;
        this->esteVegetarian = false;
        meniuriCreate++;
    }

    Meniu(int an, int nr, float* preturiNoi, bool veg) : anValabilitate(an) {
        this->nrPreparate = nr;
        this->preturi = new float[nr];
        for (int i = 0; i < nr; i++) {
            this->preturi[i] = preturiNoi[i];
        }
        this->esteVegetarian = veg;
        meniuriCreate++;
    }

    Meniu(const Meniu& m) : anValabilitate(m.anValabilitate) {
        this->nrPreparate = m.nrPreparate;
        this->preturi = new float[m.nrPreparate];
        for (int i = 0; i < m.nrPreparate; i++) {
            this->preturi[i] = m.preturi[i];
        }
        this->esteVegetarian = m.esteVegetarian;
        meniuriCreate++;
    }

    ~Meniu() {
        if (this->preturi != NULL) {
            delete[] this->preturi;
        }
        meniuriCreate--;
    }

    int getNrPreparate() {
        return this->nrPreparate;
    }

    void setPreturi(int nr, float* vectorPreturi) {
        if (nr > 0 && vectorPreturi != NULL) {
            if (this->preturi != NULL) {
                delete[] this->preturi;
            }
            this->nrPreparate = nr;
            this->preturi = new float[nr];
            for (int i = 0; i < nr; i++) {
                this->preturi[i] = vectorPreturi[i];
            }
        }
    }

    float* getPreturi() {
        return this->preturi;
    }

    static int getMeniuriCreate() {
        return meniuriCreate;
    }
};
int Meniu::meniuriCreate = 0;

void aplicaReducere(Preparat& p, int procent) {
    if (procent > 0 && procent < 50) {
        p.pret = p.pret - (p.pret * (procent / 100.0f));
    }
}

void promoveazaBucatar(Bucatar& b) {
    b.steleMichelin++;
}

void main() {
    Preparat p1("Paste Carbonara", 45.5, 800);
    Preparat p2 = p1;
    p2.setDenumire("Paste Bolognese");
    p2.setPret(50.0);

    cout << p1.getDenumire() << " " << p1.getPret() << endl;
    cout << p2.getDenumire() << " " << p2.getPret() << endl;

    aplicaReducere(p1, 20);
    cout << p1.getPret() << endl;

    cout << endl;

    Bucatar b1(101, "Gordon Ramsay", 3);
    Bucatar b2 = b1;
    b2.setNume("Jamie Oliver");

    cout << b1.getNume() << " " << b1.getStele() << endl;
    cout << b2.getNume() << " " << b2.getStele() << endl;

    promoveazaBucatar(b1);
    cout << b1.getStele() << endl;

    cout << endl;

    float listaPreturi[] = { 15.5, 20.0, 100.0 };
    Meniu m1(2023, 3, listaPreturi, false);
    Meniu m2 = m1;

    float preturiNoi[] = { 50.0, 60.0 };
    m2.setPreturi(2, preturiNoi);

    cout << m1.getNrPreparate() << endl;
    cout << m1.getPreturi()[0] << endl;

    cout << m2.getNrPreparate() << endl;
    cout << m2.getPreturi()[0] << endl;

    cout << endl;
    cout << Preparat::getContor() << endl;
    cout << Meniu::getMeniuriCreate() << endl;
}
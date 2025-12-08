#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Medicament {
public:
    const int idMedicament;
    static int contorMedicamente;
    char* nume;
    float pret;
    bool necesitaReteta;

    Medicament() : idMedicament(++contorMedicamente) {
        this->nume = new char[strlen("Necunoscut") + 1];
        strcpy(this->nume, "Necunoscut");
        this->pret = 0;
        this->necesitaReteta = false;
    }

    Medicament(const char* nume, float pret) : idMedicament(++contorMedicamente) {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->pret = pret;
        this->necesitaReteta = true;
    }

    Medicament(const char* nume, float pret, bool reteta) : idMedicament(++contorMedicamente) {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->pret = pret;
        this->necesitaReteta = reteta;
    }

    static void afiseazaTotalMedicamente() {
        cout << contorMedicamente << endl;
    }
};
int Medicament::contorMedicamente = 0;

class Farmacist {
public:
    const int codAngajat;
    static float salariuMinim;
    char* numeComplet;
    int vechimeAni;

    Farmacist() : codAngajat(0) {
        this->numeComplet = new char[7];
        strcpy(this->numeComplet, "Anonim");
        this->vechimeAni = 0;
    }

    Farmacist(int cod, const char* nume) : codAngajat(cod) {
        this->numeComplet = new char[strlen(nume) + 1];
        strcpy(this->numeComplet, nume);
        this->vechimeAni = 0;
    }

    Farmacist(int cod, const char* nume, int vechime) : codAngajat(cod) {
        this->numeComplet = new char[strlen(nume) + 1];
        strcpy(this->numeComplet, nume);
        this->vechimeAni = vechime;
    }

    static void modificaSalariuMinim(float nouSalariu) {
        if (nouSalariu > 0) {
            salariuMinim = nouSalariu;
        }
    }
};
float Farmacist::salariuMinim = 3500.50;

class Reteta {
public:
    const int idReteta;
    static int reteteProcesateAzi;
    float* preturiMedicamente;
    int nrMedicamente;
    bool esteCompensata;

    Reteta() : idReteta(0) {
        this->nrMedicamente = 0;
        this->preturiMedicamente = NULL;
        this->esteCompensata = false;
    }

    Reteta(int id, float pretUnic) : idReteta(id) {
        this->nrMedicamente = 1;
        this->preturiMedicamente = new float[1];
        this->preturiMedicamente[0] = pretUnic;
        this->esteCompensata = false;
        reteteProcesateAzi++;
    }

    Reteta(int id, int nr, float* preturi, bool compensata) : idReteta(id) {
        this->nrMedicamente = nr;
        this->preturiMedicamente = new float[nr];
        for (int i = 0; i < nr; i++) {
            this->preturiMedicamente[i] = preturi[i];
        }
        this->esteCompensata = compensata;
        reteteProcesateAzi++;
    }

    static void resetContorZi() {
        reteteProcesateAzi = 0;
    }
};
int Reteta::reteteProcesateAzi = 0;

void main() {
    Medicament m1;
    Medicament m2("Paracetamol", 15.5);
    Medicament m3("Antibiotic", 45.0, true);

    cout << m1.nume << " " << m1.pret << endl;
    cout << m2.nume << " " << m2.pret << endl;
    cout << m3.nume << " " << m3.pret << endl;

    Medicament::afiseazaTotalMedicamente();
    cout << endl;

    Farmacist f1;
    Farmacist f2(101, "Popescu Ion");
    Farmacist f3(102, "Ionescu Maria", 10);

    cout << f1.numeComplet << " " << f1.vechimeAni << endl;
    cout << f2.numeComplet << " " << f2.vechimeAni << endl;
    cout << f3.numeComplet << " " << f3.vechimeAni << endl;

    Farmacist::modificaSalariuMinim(4000);
    cout << endl;

    Reteta r1;
    Reteta r2(500, 120.5);

    float preturi[] = { 20.5, 100, 15.2 };
    Reteta r3(501, 3, preturi, true);

    cout << r1.nrMedicamente << endl;
    cout << r2.idReteta << " " << r2.preturiMedicamente[0] << endl;
    cout << r3.idReteta << " " << r3.esteCompensata << endl;

    for (int i = 0; i < r3.nrMedicamente; i++) {
        cout << r3.preturiMedicamente[i] << " ";
    }
    cout << endl;

    cout << Reteta::reteteProcesateAzi << endl;
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Locuinta {
private:
    const int idLocuinta;
    static int contor;
    char* adresa;
    float suprafata;
    int anConstructie;

public:
    Locuinta() : idLocuinta(++contor) {
        this->adresa = new char[12];
        strcpy(this->adresa, "Necunoscuta");
        this->suprafata = 0;
        this->anConstructie = 2000;
    }

    Locuinta(const char* adresa, float suprafata, int an) : idLocuinta(++contor) {
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
        this->suprafata = suprafata;
        this->anConstructie = an;
    }

    Locuinta(const Locuinta& l) : idLocuinta(++contor) {
        this->adresa = new char[strlen(l.adresa) + 1];
        strcpy(this->adresa, l.adresa);
        this->suprafata = l.suprafata;
        this->anConstructie = l.anConstructie;
    }

    ~Locuinta() {
        if (this->adresa != NULL) {
            delete[] this->adresa;
        }
    }

    Locuinta& operator=(const Locuinta& l) {
        if (this != &l) {
            if (this->adresa != NULL) {
                delete[] this->adresa;
            }
            this->adresa = new char[strlen(l.adresa) + 1];
            strcpy(this->adresa, l.adresa);
            this->suprafata = l.suprafata;
            this->anConstructie = l.anConstructie;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Locuinta& l) {
        out << "ID: " << l.idLocuinta << " | Adresa: " << l.adresa
            << " | Suprafata: " << l.suprafata << " mp | An: " << l.anConstructie;
        return out;
    }

    friend istream& operator>>(istream& in, Locuinta& l) {
        cout << "Introduceti adresa: ";
        char buffer[100];
        in >> buffer;
        if (l.adresa != NULL) {
            delete[] l.adresa;
        }
        l.adresa = new char[strlen(buffer) + 1];
        strcpy(l.adresa, buffer);

        cout << "Introduceti suprafata: ";
        in >> l.suprafata;
        cout << "Introduceti an constructie: ";
        in >> l.anConstructie;
        return in;
    }
};
int Locuinta::contor = 0;

class Agent {
private:
    const int idAgent;
    static int contorAgenti;
    char* nume;
    float comisionProcent;

public:
    Agent() : idAgent(++contorAgenti) {
        this->nume = new char[7];
        strcpy(this->nume, "Anonim");
        this->comisionProcent = 0;
    }

    Agent(const char* nume, float comision) : idAgent(++contorAgenti) {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->comisionProcent = comision;
    }

    Agent(const Agent& a) : idAgent(++contorAgenti) {
        this->nume = new char[strlen(a.nume) + 1];
        strcpy(this->nume, a.nume);
        this->comisionProcent = a.comisionProcent;
    }

    ~Agent() {
        if (this->nume != NULL) {
            delete[] this->nume;
        }
    }

    Agent& operator=(const Agent& a) {
        if (this != &a) {
            if (this->nume != NULL) {
                delete[] this->nume;
            }
            this->nume = new char[strlen(a.nume) + 1];
            strcpy(this->nume, a.nume);
            this->comisionProcent = a.comisionProcent;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Agent& a) {
        out << "Agent: " << a.nume << " (ID: " << a.idAgent << ") - Comision: " << a.comisionProcent << "%";
        return out;
    }

    friend istream& operator>>(istream& in, Agent& a) {
        cout << "Nume agent: ";
        char buffer[100];
        in >> buffer;
        if (a.nume != NULL) delete[] a.nume;
        a.nume = new char[strlen(buffer) + 1];
        strcpy(a.nume, buffer);

        cout << "Comision (%): ";
        in >> a.comisionProcent;
        return in;
    }
};
int Agent::contorAgenti = 0;

class Agentie {
private:
    char* denumire;
    int nrFiliale;
    float* venituriFiliale;

public:
    Agentie() {
        this->denumire = new char[9];
        strcpy(this->denumire, "Standard");
        this->nrFiliale = 0;
        this->venituriFiliale = NULL;
    }

    Agentie(const char* denumire, int nr, float* venituri) {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy(this->denumire, denumire);
        this->nrFiliale = nr;
        this->venituriFiliale = new float[nr];
        for (int i = 0; i < nr; i++) {
            this->venituriFiliale[i] = venituri[i];
        }
    }

    Agentie(const Agentie& a) {
        this->denumire = new char[strlen(a.denumire) + 1];
        strcpy(this->denumire, a.denumire);
        this->nrFiliale = a.nrFiliale;
        this->venituriFiliale = new float[a.nrFiliale];
        for (int i = 0; i < a.nrFiliale; i++) {
            this->venituriFiliale[i] = a.venituriFiliale[i];
        }
    }

    ~Agentie() {
        if (this->denumire != NULL) delete[] this->denumire;
        if (this->venituriFiliale != NULL) delete[] this->venituriFiliale;
    }

    Agentie& operator=(const Agentie& a) {
        if (this != &a) {
            if (this->denumire != NULL) delete[] this->denumire;
            if (this->venituriFiliale != NULL) delete[] this->venituriFiliale;

            this->denumire = new char[strlen(a.denumire) + 1];
            strcpy(this->denumire, a.denumire);
            this->nrFiliale = a.nrFiliale;
            this->venituriFiliale = new float[a.nrFiliale];
            for (int i = 0; i < a.nrFiliale; i++) {
                this->venituriFiliale[i] = a.venituriFiliale[i];
            }
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Agentie& a) {
        out << "Agentie: " << a.denumire << " | Filiale: " << a.nrFiliale << " -> Venituri: ";
        if (a.venituriFiliale != NULL) {
            for (int i = 0; i < a.nrFiliale; i++) out << a.venituriFiliale[i] << " ";
        }
        return out;
    }

    friend istream& operator>>(istream& in, Agentie& a) {
        cout << "Denumire agentie: ";
        char buffer[100];
        in >> buffer;
        if (a.denumire != NULL) delete[] a.denumire;
        a.denumire = new char[strlen(buffer) + 1];
        strcpy(a.denumire, buffer);

        cout << "Numar filiale: ";
        in >> a.nrFiliale;

        if (a.venituriFiliale != NULL) delete[] a.venituriFiliale;
        a.venituriFiliale = new float[a.nrFiliale];

        cout << "Introduceti veniturile pentru cele " << a.nrFiliale << " filiale:" << endl;
        for (int i = 0; i < a.nrFiliale; i++) {
            cout << "Filiala " << i + 1 << ": ";
            in >> a.venituriFiliale[i];
        }
        return in;
    }
};

void main() {
    int n = 2;
    Locuinta* vectorLocuinte = new Locuinta[n];
    Agent* vectorAgenti = new Agent[n];
    Agentie* vectorAgentii = new Agentie[n];

    cout << "=== CITIRE VECTOR AGENTI ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Agentul " << i + 1 << ":" << endl;
        cin >> vectorAgenti[i];
        cout << endl;
    }

    cout << "=== AFISARE VECTOR AGENTI ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << vectorAgenti[i] << endl;
    }
    cout << endl;

    vectorLocuinte[0] = Locuinta("Str. Victoriei", 55.5, 1980);
    vectorLocuinte[1] = Locuinta("Bd. Unirii", 80.0, 2010);

    cout << "=== AFISARE VECTOR LOCUINTE ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << vectorLocuinte[i] << endl;
    }
    cout << endl;

    int linii = 2;
    int coloane = 2;

    cout << "=== CREARE SI AFISARE MATRICE LOCUINTE ===" << endl;
    Locuinta** matriceLocuinte = new Locuinta * [linii];

    for (int i = 0; i < linii; i++) {
        matriceLocuinte[i] = new Locuinta[coloane];
    }

    matriceLocuinte[0][0] = Locuinta("Cartier A - Str 1", 40, 1970);
    matriceLocuinte[0][1] = Locuinta("Cartier A - Str 2", 45, 1975);
    matriceLocuinte[1][0] = Locuinta("Cartier B - Str 1", 100, 2020);
    matriceLocuinte[1][1] = Locuinta("Cartier B - Str 2", 120, 2022);

    for (int i = 0; i < linii; i++) {
        cout << "Cartier " << i + 1 << ":" << endl;
        for (int j = 0; j < coloane; j++) {
            cout << "  " << matriceLocuinte[i][j] << endl;
        }
    }

    for (int i = 0; i < linii; i++) {
        delete[] matriceLocuinte[i];
    }
    delete[] matriceLocuinte;

    delete[] vectorLocuinte;
    delete[] vectorAgenti;
    delete[] vectorAgentii;
}
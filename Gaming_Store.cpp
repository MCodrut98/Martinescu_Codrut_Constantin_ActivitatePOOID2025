#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

template <class T>
class Colectie {
private:
    T* elemente;
    int dimensiune;
    int capacitate;

public:
    Colectie() {
        this->dimensiune = 0;
        this->capacitate = 2;
        this->elemente = new T[this->capacitate];
    }

    Colectie(const Colectie& c) {
        this->dimensiune = c.dimensiune;
        this->capacitate = c.capacitate;
        this->elemente = new T[this->capacitate];
        for (int i = 0; i < this->dimensiune; i++) {
            this->elemente[i] = c.elemente[i];
        }
    }

    ~Colectie() {
        if (this->elemente != NULL) {
            delete[] this->elemente;
        }
    }

    void adauga(T elem) {
        if (this->dimensiune == this->capacitate) {
            this->capacitate *= 2;
            T* temp = new T[this->capacitate];
            for (int i = 0; i < this->dimensiune; i++) {
                temp[i] = this->elemente[i];
            }
            delete[] this->elemente;
            this->elemente = temp;
        }
        this->elemente[this->dimensiune] = elem;
        this->dimensiune++;
    }

    T& operator[](int index) {
        if (index >= 0 && index < this->dimensiune) {
            return this->elemente[index];
        }
        throw "Index in afara limitelor!";
    }

    int getDimensiune() { return this->dimensiune; }

    void sorteaza() {
        for (int i = 0; i < this->dimensiune - 1; i++) {
            for (int j = 0; j < this->dimensiune - i - 1; j++) {
                if (this->elemente[j] > this->elemente[j + 1]) {
                    T aux = this->elemente[j];
                    this->elemente[j] = this->elemente[j + 1];
                    this->elemente[j + 1] = aux;
                }
            }
        }
    }
};

class Joc {
protected:
    char* titlu;
    float pret;

public:
    Joc(const char* titlu, float pret) {
        this->titlu = new char[strlen(titlu) + 1];
        strcpy(this->titlu, titlu);
        this->pret = pret;
    }

    virtual ~Joc() {
        if (this->titlu != NULL) delete[] this->titlu;
    }

    virtual void descriere() = 0;
    virtual char* getGen() = 0;

    float getPret() { return this->pret; }
    const char* getTitlu() { return this->titlu; }
};

class JocRPG : public Joc {
private:
    int oreGameplay;
    bool esteOpenWorld;

public:
    JocRPG(const char* titlu, float pret, int ore, bool openWorld)
        : Joc(titlu, pret), oreGameplay(ore), esteOpenWorld(openWorld) {
    }

    void descriere() override {
        cout << "[RPG] " << this->titlu << " | Pret: " << this->pret
            << " RON | Ore: " << this->oreGameplay
            << " | Lume: " << (this->esteOpenWorld ? "Open-World" : "Linear") << endl;
    }

    char* getGen() override {
        char* gen = new char[4];
        strcpy(gen, "RPG");
        return gen;
    }

    void cresteNivel() {
        cout << ">> Jucatorul a crescut in nivel in " << this->titlu << endl;
    }
};

class JocShooter : public Joc {
private:
    int nrHarti;
    char* modJoc;

public:
    JocShooter(const char* titlu, float pret, int harti, const char* mod)
        : Joc(titlu, pret), nrHarti(harti) {
        this->modJoc = new char[strlen(mod) + 1];
        strcpy(this->modJoc, mod);
    }

    ~JocShooter() {
        if (this->modJoc != NULL) delete[] this->modJoc;
    }

    void descriere() override {
        cout << "[SHOOTER] " << this->titlu << " | Pret: " << this->pret
            << " RON | Harti: " << this->nrHarti
            << " | Mod: " << this->modJoc << endl;
    }

    char* getGen() override {
        char* gen = new char[8];
        strcpy(gen, "Shooter");
        return gen;
    }
};

void main() {
    cout << "=== TESTARE COLECTIE TEMPLATE (int) ===" << endl;
    Colectie<int> scoruri;
    scoruri.adauga(500);
    scoruri.adauga(100);
    scoruri.adauga(350);

    scoruri.sorteaza();

    cout << "Scoruri sortate: ";
    for (int i = 0; i < scoruri.getDimensiune(); i++) {
        cout << scoruri[i] << " ";
    }
    cout << endl << endl;

    cout << "=== TESTARE COLECTIE JOCURI (Polimorfism) ===" << endl;

    Colectie<Joc*> librarie;

    librarie.adauga(new JocRPG("The Witcher 3", 150.0, 100, true));
    librarie.adauga(new JocShooter("CS:GO 2", 0.0, 20, "Competitive"));
    librarie.adauga(new JocRPG("Elden Ring", 250.0, 120, true));
    librarie.adauga(new JocShooter("Call of Duty", 300.0, 15, "Team Deathmatch"));

    for (int i = 0; i < librarie.getDimensiune(); i++) {
        librarie[i]->descriere();
    }

    cout << "\n=== DETECTARE TIP SI ACTIUNI SPECIFICE ===" << endl;
    for (int i = 0; i < librarie.getDimensiune(); i++) {
        char* gen = librarie[i]->getGen();

        if (strcmp(gen, "RPG") == 0) {
            JocRPG* rpg = (JocRPG*)librarie[i];
            rpg->cresteNivel();
        }
        delete[] gen;
    }

    cout << "\n=== SORTARE JOCURI DUPA PRET ===" << endl;
    for (int i = 0; i < librarie.getDimensiune() - 1; i++) {
        for (int j = 0; j < librarie.getDimensiune() - i - 1; j++) {
            if (librarie[j]->getPret() > librarie[j + 1]->getPret()) {
                Joc* temp = librarie[j];
                librarie[j] = librarie[j + 1];
                librarie[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < librarie.getDimensiune(); i++) {
        cout << librarie[i]->getTitlu() << " - " << librarie[i]->getPret() << " RON" << endl;
    }

    for (int i = 0; i < librarie.getDimensiune(); i++) {
        delete librarie[i];
    }
}
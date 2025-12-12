#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Dispozitiv {
protected:
    const int id;
    static int contor;
    char* locatie;
    bool estePornit;

public:
    Dispozitiv() : id(++contor) {
        this->locatie = new char[8];
        strcpy(this->locatie, "Unknown");
        this->estePornit = false;
    }

    Dispozitiv(const char* loc) : id(++contor) {
        this->locatie = new char[strlen(loc) + 1];
        strcpy(this->locatie, loc);
        this->estePornit = false;
    }

    Dispozitiv(const Dispozitiv& d) : id(++contor) {
        this->locatie = new char[strlen(d.locatie) + 1];
        strcpy(this->locatie, d.locatie);
        this->estePornit = d.estePornit;
    }

    virtual ~Dispozitiv() {
        if (this->locatie != NULL) {
            delete[] this->locatie;
        }
    }

    Dispozitiv& operator=(const Dispozitiv& d) {
        if (this != &d) {
            if (this->locatie != NULL) delete[] this->locatie;
            this->locatie = new char[strlen(d.locatie) + 1];
            strcpy(this->locatie, d.locatie);
            this->estePornit = d.estePornit;
        }
        return *this;
    }

    void switchPower() {
        this->estePornit = !this->estePornit;
    }

    virtual void afiseazaStatus() = 0;
    virtual void executaActiune() = 0;
    virtual char* getTip() = 0;
};
int Dispozitiv::contor = 0;

class BecIntelligent : public Dispozitiv {
private:
    int intensitate;
    char* culoare;

public:
    BecIntelligent() : Dispozitiv() {
        this->intensitate = 100;
        this->culoare = new char[4];
        strcpy(this->culoare, "Alb");
    }

    BecIntelligent(const char* loc, int intensitate, const char* col) : Dispozitiv(loc) {
        this->intensitate = intensitate;
        this->culoare = new char[strlen(col) + 1];
        strcpy(this->culoare, col);
    }

    BecIntelligent(const BecIntelligent& b) : Dispozitiv(b) {
        this->intensitate = b.intensitate;
        this->culoare = new char[strlen(b.culoare) + 1];
        strcpy(this->culoare, b.culoare);
    }

    ~BecIntelligent() {
        if (this->culoare != NULL) delete[] this->culoare;
    }

    BecIntelligent& operator=(const BecIntelligent& b) {
        if (this != &b) {
            Dispozitiv::operator=(b);
            if (this->culoare != NULL) delete[] this->culoare;
            this->culoare = new char[strlen(b.culoare) + 1];
            strcpy(this->culoare, b.culoare);
            this->intensitate = b.intensitate;
        }
        return *this;
    }

    void afiseazaStatus() override {
        cout << "[BEC] Locatie: " << this->locatie
            << " | Power: " << (this->estePornit ? "ON" : "OFF")
            << " | Culoare: " << this->culoare
            << " | Intensitate: " << this->intensitate << "%" << endl;
    }

    void executaActiune() override {
        if (this->estePornit) {
            cout << "Becul din " << this->locatie << " lumineaza in culoarea " << this->culoare << "." << endl;
        }
        else {
            cout << "Becul este stins. Nu poate lumina." << endl;
        }
    }

    char* getTip() override {
        char* tip = new char[4];
        strcpy(tip, "Bec");
        return tip;
    }
};

class Termostat : public Dispozitiv {
private:
    float temperaturaAmbientala;
    float temperaturaTarget;

public:
    Termostat() : Dispozitiv() {
        this->temperaturaAmbientala = 20.0;
        this->temperaturaTarget = 22.0;
    }

    Termostat(const char* loc, float tempAmb, float tempTarget) : Dispozitiv(loc) {
        this->temperaturaAmbientala = tempAmb;
        this->temperaturaTarget = tempTarget;
    }

    Termostat(const Termostat& t) : Dispozitiv(t) {
        this->temperaturaAmbientala = t.temperaturaAmbientala;
        this->temperaturaTarget = t.temperaturaTarget;
    }

    ~Termostat() {
    }

    Termostat& operator=(const Termostat& t) {
        if (this != &t) {
            Dispozitiv::operator=(t);
            this->temperaturaAmbientala = t.temperaturaAmbientala;
            this->temperaturaTarget = t.temperaturaTarget;
        }
        return *this;
    }

    void afiseazaStatus() override {
        cout << "[TERMOSTAT] Locatie: " << this->locatie
            << " | Power: " << (this->estePornit ? "ON" : "OFF")
            << " | Actual: " << this->temperaturaAmbientala
            << "C -> Target: " << this->temperaturaTarget << "C" << endl;
    }

    void executaActiune() override {
        if (!this->estePornit) {
            cout << "Termostat oprit." << endl;
            return;
        }

        if (temperaturaAmbientala < temperaturaTarget) {
            cout << "Centrala pornita. Se incalzeste..." << endl;
            temperaturaAmbientala += 0.5;
        }
        else if (temperaturaAmbientala > temperaturaTarget) {
            cout << "AC pornit. Se raceste..." << endl;
            temperaturaAmbientala -= 0.5;
        }
        else {
            cout << "Temperatura optima mentinuta." << endl;
        }
    }

    char* getTip() override {
        char* tip = new char[10];
        strcpy(tip, "Termostat");
        return tip;
    }
};

class HubCentral {
private:
    char* numeHub;
    Dispozitiv** listaDispozitive;
    int nrDispozitive;

public:
    HubCentral(const char* nume) {
        this->numeHub = new char[strlen(nume) + 1];
        strcpy(this->numeHub, nume);
        this->nrDispozitive = 0;
        this->listaDispozitive = NULL;
    }

    ~HubCentral() {
        if (this->numeHub != NULL) delete[] this->numeHub;
        if (this->listaDispozitive != NULL) {
            for (int i = 0; i < this->nrDispozitive; i++) {
                delete this->listaDispozitive[i];
            }
            delete[] this->listaDispozitive;
        }
    }

    void adaugaDispozitiv(Dispozitiv* d) {
        Dispozitiv** temp = new Dispozitiv * [this->nrDispozitive + 1];
        for (int i = 0; i < this->nrDispozitive; i++) {
            temp[i] = this->listaDispozitive[i];
        }
.
        temp[this->nrDispozitive] = d;

        if (this->listaDispozitive != NULL) delete[] this->listaDispozitive;
        this->listaDispozitive = temp;
        this->nrDispozitive++;
    }

    void raportStatusCasa() {
        cout << "=== RAPORT HUB: " << this->numeHub << " ===" << endl;
        for (int i = 0; i < this->nrDispozitive; i++) {
            cout << i + 1 << ". ";
            this->listaDispozitive[i]->afiseazaStatus();
        }
        cout << "=============================" << endl;
    }

    void pornesteTot() {
        for (int i = 0; i < this->nrDispozitive; i++) {
            this->listaDispozitive[i]->switchPower();
            this->listaDispozitive[i]->executaActiune();
        }
    }
};

void main() {

    BecIntelligent* b1 = new BecIntelligent("Living", 80, "Galben");
    BecIntelligent* b2 = new BecIntelligent("Dormitor", 50, "Rosu");
    Termostat* t1 = new Termostat("Hol", 19.5, 23.0);

    HubCentral hub("Google Home");

    hub.adaugaDispozitiv(b1);
    hub.adaugaDispozitiv(b2);
    hub.adaugaDispozitiv(t1);

    cout << "--- Initial Status ---" << endl;
    hub.raportStatusCasa();

    cout << endl << "--- Actionare Generala ---" << endl;
    hub.pornesteTot();

    cout << endl << "--- Status Final ---" << endl;
    hub.raportStatusCasa();
}
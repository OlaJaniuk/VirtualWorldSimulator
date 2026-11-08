#ifndef SWIAT_H
#define SWIAT_H

#include <vector> // Musimy użyć vectora do trzymania organizmów
#include <iostream>
#include "Organizm.h"
#include "Czlowiek.h"

class Swiat
{
public:
    Swiat(int N, int M);
    ~Swiat();

    void wykonajTure();
    void rysujSwiat();
    void dodajOrganizm(Organizm *organizm);

    int getN() const { return N; }
    int getM() const { return M; }
    int getTura() const { return tura; }
    std::vector<Organizm *> &getOrganizmy() { return organizmy; }
    Organizm *getOrganizmNaPolu(int x, int y);

    void dodajKomunikat(std::string komunikat);
    bool czyCzlowiekZyje();
    void losujPozycje(int &x, int &y);

    void
    zapiszSwiat(std::string nazwaPliku);
    void wczytajSwiat(std::string nazwaPliku);

    // żeby main odzyskał kontrolę nad człowiekiem po wczytaniu
    Czlowiek *getCzlowiek();

private:
    int N; // Szerokość świata
    int M; // Wysokość świata
    int tura;

    std::vector<Organizm *> organizmy;
    std::vector<std::string> dziennik;
};

#endif
#ifndef CZLOWIEK_H
#define CZLOWIEK_H

#include "Zwierze.h"
#include <iostream>

class Czlowiek : public Zwierze
{
public:
    Czlowiek(int x, int y, Swiat *swiat);
    ~Czlowiek() override;

    void akcja() override;
    void wykonajCalopalenie();
    void rysowanie() override;
    std::string getNazwa() const override { return "Czlowiek"; }
    int getLicznikUmiejetnosci() const { return licznikUmiejetnosci; }

    void ustawKierunek(int kierunek);
    void aktywujUmiejetnosc();

    void zapisz(std::ostream &plik) const override;
    void setLicznik(int l) { licznikUmiejetnosci = l; }

protected:
    Organizm *stworzNowy(int x, int y) const override { return nullptr; }
    
private:
    int kierunekRuchu;
    int licznikUmiejetnosci;
    
};

#endif
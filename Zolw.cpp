#include "Zolw.h"
#include <iostream>

Zolw::Zolw(int x, int y, Swiat *swiat)
    : Zwierze(2, 1, x, y, swiat)
{
}
Zolw::~Zolw()
{
}

void Zolw::rysowanie()
{
    std::cout << KOLOR_ZOLW << " Z " << KOLOR_TEKST;
}

void Zolw::akcja()
{
    // dla 1,2,3 nie ruszamy sie, zeby bylo 75% szans na pozostanie na polu
    if (rand() % 4 != 0)
    {
        return;
    }
    Zwierze::akcja();
}
bool Zolw::czyOdbilAtak(Organizm *atakujacy)
{
    int silaAtakujacy = atakujacy->getSila();
    if (silaAtakujacy < 5)
    {
        return true;
    }
    return false;
}
Organizm *Zolw::stworzNowy(int x, int y) const
{
    return new Zolw(x, y, this->swiat);
}

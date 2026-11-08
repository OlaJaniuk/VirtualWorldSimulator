#include "Guarana.h"
#include "Swiat.h"
#include <iostream>

Guarana::Guarana(int x, int y, Swiat *swiat)
    : Roslina(0, x, y, swiat) // Siła 0
{
}
Guarana::~Guarana()
{
}

Organizm *Guarana::stworzNowy(int x, int y) const
{
    return new Guarana(x, y, swiat);
}

void Guarana::rysowanie()
{
    std::cout << KOLOR_GUARANA << " g " << KOLOR_TEKST;
}

void Guarana::kolizja(Organizm *atakujacy)
{
    // Zwiększamy siłę atakującego o 3
    int staraSila = atakujacy->getSila();
    atakujacy->setSila(staraSila + 3);
    swiat->dodajKomunikat(atakujacy->getNazwa() + " zjada Guarane (+3 sily).");
    this->zabij();
}
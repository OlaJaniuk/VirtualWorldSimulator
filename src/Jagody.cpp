#include "Jagody.h"
#include "Swiat.h"
#include <iostream>

Jagody::Jagody(int x, int y, Swiat *swiat)
    : Roslina(99, x, y, swiat) // Siła 0
{
}
Jagody::~Jagody()
{
}

Organizm *Jagody::stworzNowy(int x, int y) const
{
    return new Jagody(x, y, swiat);
}

void Jagody::kolizja(Organizm *atakujacy)
{
    // Zwierzę, które zjadło jagody roślinę, ginie
    std::string wpis = atakujacy->getNazwa() + " zjada Wilcze Jagody i umiera.";
    swiat->dodajKomunikat(wpis);
    atakujacy->zabij();

    this->zabij();
}

void Jagody::rysowanie()
{
    std::cout << KOLOR_JAGODY << " j " << KOLOR_TEKST;
}
#include "Trawa.h"
#include <iostream>

Trawa::Trawa(int x, int y, Swiat *swiat)
    : Roslina(0, x, y, swiat) // Siła 0
{
}
Trawa::~Trawa()
{
}

Organizm *Trawa::stworzNowy(int x, int y) const
{
    return new Trawa(x, y, swiat);
}

void Trawa::rysowanie()
{
    std::cout << KOLOR_TRAWA << " t " << KOLOR_TEKST;
}
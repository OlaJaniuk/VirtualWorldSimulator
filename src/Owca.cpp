#include "Owca.h"
#include <iostream>

Owca::Owca(int x, int y, Swiat *swiat)
    : Zwierze(4, 4, x, y, swiat)
{
}
Owca::~Owca()
{
}
void Owca::rysowanie()
{
    std::cout << KOLOR_OWCA << " O " << KOLOR_TEKST;
}

Organizm *Owca::stworzNowy(int x, int y) const
{
    return new Owca(x, y, this->swiat);
}

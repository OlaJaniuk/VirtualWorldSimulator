#include "Lis.h"
#include <iostream>

Lis::Lis(int x, int y, Swiat *swiat)
    : Zwierze(3, 7, x, y, swiat)
{
}
Lis::~Lis()
{
}
void Lis::rysowanie()
{
    std::cout << KOLOR_LIS << " L " << KOLOR_TEKST;
}

bool Lis::czyRuchJestBezpieczny(Organizm *cel) const
{
    if (cel == NULL)
    {
        return true;
    }
    if (cel->getSila() > this->getSila())
    {
        return false;
    }

    return true;
}

Organizm *Lis::stworzNowy(int x, int y) const
{
    return new Lis(x, y, this->swiat);
}

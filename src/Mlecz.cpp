#include "Mlecz.h"
#include <iostream>

Mlecz::Mlecz(int x, int y, Swiat *swiat)
    : Roslina(0, x, y, swiat) // Siła 0
{
}
Mlecz::~Mlecz()
{
}

Organizm *Mlecz::stworzNowy(int x, int y) const
{
    return new Mlecz(x, y, swiat);
}

void Mlecz::rysowanie()
{
    std::cout << KOLOR_MLECZ << " m " << KOLOR_TEKST;
}

void Mlecz::akcja()
{
    // mlecz próbuje rozsiać się 3 razy
    for (int i = 0; i < 3; i++)
    {

        Roslina::akcja();
    }
}
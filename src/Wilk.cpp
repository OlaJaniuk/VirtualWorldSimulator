#include "Wilk.h"
#include <iostream>

Wilk::Wilk(int x, int y, Swiat *swiat)
    : Zwierze(9, 5, x, y, swiat)
{
}
Wilk::~Wilk()
{
}
void Wilk::rysowanie()
{
    std::cout << KOLOR_WILK << " W " << KOLOR_TEKST;
}

Organizm *Wilk::stworzNowy(int x, int y) const
{
    return new Wilk(x, y, this->swiat);
}

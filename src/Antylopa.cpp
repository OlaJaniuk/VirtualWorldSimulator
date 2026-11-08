#include "Antylopa.h"
#include "Swiat.h"
#include <iostream>

Antylopa::Antylopa(int x, int y, Swiat *swiat)
    : Zwierze(4, 4, x, y, swiat)
{
}
Antylopa::~Antylopa()
{
}
void Antylopa::rysowanie()
{
    std::cout << KOLOR_ANTYLOPA << " A " << KOLOR_TEKST;
}

bool Antylopa::czyOdbilAtak(Organizm *atakujacy)
{
    if (rand() % 2 == 0)
    {
        return false;
    }

    int ucieczkaX, ucieczkaY;

    if (this->znajdzWolnePole(ucieczkaX, ucieczkaY))
    {
        // Przesuwamy antylopę na znalezione wolne pole
        this->x = ucieczkaX;
        this->y = ucieczkaY;

        return true;
    }

    // jesli sie nie udalo znalezc wolnego pola, to znaczy ze walka
    return false;
}

Organizm *Antylopa::stworzNowy(int x, int y) const
{
    return new Antylopa(x, y, this->swiat);
}
#include "Roslina.h"
#include "Swiat.h"
#include <iostream>
#include <cstdlib>

Roslina::Roslina(int sila, int x, int y, Swiat *swiat)
    : Organizm(sila, 0, x, y, swiat)
{
}

Roslina::~Roslina()
{
}

void Roslina::akcja()
{
    // losujemy, czy roślina sie rozsieje
    if (rand() % 100 < getSzanseRozsiania())
    {
        int noweX, noweY;

        if (znajdzWolnePole(noweX, noweY))
        {
            Organizm *dziecko = stworzNowy(noweX, noweY);
            swiat->dodajOrganizm(dziecko);
        }
    }
}

void Roslina::kolizja(Organizm *atakujacy)
{
    if (this->getSila() < atakujacy->getSila())
    {
        swiat->dodajKomunikat(atakujacy->getNazwa() + " zjada " + this->getNazwa());
        this->zabij();
    }
}
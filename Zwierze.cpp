#include "Zwierze.h"
#include "Swiat.h"
#include <iostream>
#include <cstdlib>
#include <typeinfo>

using namespace std;

Zwierze::Zwierze(int sila, int inicjatywa, int x, int y, Swiat *swiat)
    : Organizm(sila, inicjatywa, x, y, swiat)
{
}

Zwierze::~Zwierze()
{
}

void Zwierze::akcja()
{
    int kierunek = rand() % 4;
    // Obliczamy współrzędne, używając ZASIĘGU (domyślnie 1, dla Antylopy 2)
    int zasieg = this->getZasiegRuchu();
    int noweX = x;
    int noweY = y;
    if (kierunek == 0)
    {
        noweY -= zasieg;
    }
    else if (kierunek == 1)
    {
        noweY += zasieg;
    }
    else if (kierunek == 2)
    {
        noweX -= zasieg;
    }
    else
    {
        noweX += zasieg;
    }

    // sprawdzenie granic swiata
    int N = swiat->getN();
    int M = swiat->getM();

    if (noweX >= 0 && noweX < N && noweY >= 0 && noweY < M)
    {
        Organizm *kolizyjny = swiat->getOrganizmNaPolu(noweX, noweY);

        // warunek dla lisa, zeby nie musiec tam napisywac calej metody akcja()
        if (!this->czyRuchJestBezpieczny(kolizyjny))
        {
            return;
        }

        if (kolizyjny != NULL)
        {
            kolizyjny->kolizja(this);
            // Jeśli wygraliśmy walkę (my żyjemy, przeciwnik nie), zajmujemy pole
            if (this->czyZyje() && !kolizyjny->czyZyje())
            {
                x = noweX;
                y = noweY;
            }
        }
        else
        {
            // Pole puste, po prostu się przesuwamy
            x = noweX;
            y = noweY;
        }
    }
}

void Zwierze::kolizja(Organizm *atakujacy)
{
    // jesli ten sam gatunek to rozmnazamy
    if (typeid(*this) == typeid(*atakujacy))
    {
        this->rozmnozSie();
        // swiat->dodajKomunikat(this->getNazwa() + " rozmnaza sie.");
        return;
    }

    if (this->czyOdbilAtak(atakujacy))
    {
        return;
    }

    if (this->getSila() > atakujacy->getSila())
    {
        swiat->dodajKomunikat(this->getNazwa() + " zabija " + atakujacy->getNazwa());
        atakujacy->zabij();
    }
    else
    {
        swiat->dodajKomunikat(atakujacy->getNazwa() + " zabija " + this->getNazwa());
        this->zabij();
    }
}
void Zwierze::rozmnozSie()
{
    int dzieckoX, dzieckoY;

    if (this->znajdzWolnePole(dzieckoX, dzieckoY))
    {
        Organizm *dziecko = this->stworzNowy(dzieckoX, dzieckoY);
        swiat->dodajOrganizm(dziecko);
    }
}
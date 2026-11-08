#include "Barszcz.h"
#include "Swiat.h"
#include "Zwierze.h"
#include <iostream>

Barszcz::Barszcz(int x, int y, Swiat *swiat)
    : Roslina(10, x, y, swiat) // Siła 0
{
}
Barszcz::~Barszcz()
{
}

Organizm *Barszcz::stworzNowy(int x, int y) const
{
    return new Barszcz(x, y, swiat);
}

void Barszcz::rysowanie()
{
    std::cout << KOLOR_BARSZCZ << " b " << KOLOR_TEKST;
}

void Barszcz::akcja()
{
    // specjalna akcja: zabijanie sąsiadów
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    int N = swiat->getN();
    int M = swiat->getM();

    for (int i = 0; i < 4; i++)
    {
        int sasiadX = x + dx[i];
        int sasiadY = y + dy[i];

        if (sasiadX >= 0 && sasiadX < N && sasiadY >= 0 && sasiadY < M)
        {
            Organizm *sasiad = swiat->getOrganizmNaPolu(sasiadX, sasiadY);

            // sprawdzamy, czy sąsiad istnieje i czy jest zwierzęciem
            Zwierze *zwierzeSasiad = dynamic_cast<Zwierze *>(sasiad);

            if (zwierzeSasiad != nullptr)
            {
                std::string wpis = "Barszcz Sosnowskiego zabija blisko stojacego " + zwierzeSasiad->getNazwa();
                swiat->dodajKomunikat(wpis);
                zwierzeSasiad->zabij();
            }
        }
    }

    Roslina::akcja();
}

void Barszcz::kolizja(Organizm *atakujacy)
{
    std::string wpis = "Barszcz Sosnowskiego zatruwa i zabija " + atakujacy->getNazwa();
    swiat->dodajKomunikat(wpis);
    atakujacy->zabij();
    this->zabij();
}
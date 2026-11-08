#include "Organizm.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

Organizm::Organizm(int sila, int inicjatywa, int x, int y, Swiat *swiat)
    : sila(sila), inicjatywa(inicjatywa), x(x), y(y), swiat(swiat), zyje(true), wiek(0)
{
}

Organizm::~Organizm()
{
}

bool Organizm::znajdzWolnePole(int &destX, int &destY) const
{
    int N = swiat->getN();
    int M = swiat->getM();

    // sprawdzamy po kolei każde pole czy jest wolne
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    // tablica indeksow do losowania kolejnosci sprawdzania
    int order[] = {0, 1, 2, 3};

    // Mieszamy kolejność indeksow kierunkow (prosty shuffle)
    // Dzięki temu za każdym razem sprawdzimy sąsiadów w innej kolejności
    for (int i = 0; i < 4; i++)
    {
        int r = rand() % 4;
        swap(order[i], order[r]);
    }

    for (int i = 0; i < 4; i++)
    {
        int idx = order[i];
        int checkX = this->x + dx[idx];
        int checkY = this->y + dy[idx];

        // sprawdzamy czy miesci sie na planszy
        if (checkX >= 0 && checkX < N && checkY >= 0 && checkY < M)
        {

            // sprawdzamy czy pole puste
            if (swiat->getOrganizmNaPolu(checkX, checkY) == nullptr)
            {

                // jesli puste to przypisujemy
                destX = checkX;
                destY = checkY;
                return true;
            }
        }
    }
    // jesli nie znaleziono zadnego wolnego pola
    return false;
}

void Organizm::zapisz(std::ostream &plik) const
{
    plik << getNazwa() << " "
         << x << " "
         << y << " "
         << sila << " "
         << inicjatywa << " "
         << wiek;
}

#include "Czlowiek.h"
#include "Swiat.h"
#include <iostream>

#define KIERUNEK_BRAK -1
#define GORA 0
#define DOL 1
#define LEWO 2
#define PRAWO 3

Czlowiek::Czlowiek(int x, int y, Swiat *swiat)
    : Zwierze(5, 4, x, y, swiat)
{
    this->kierunekRuchu = KIERUNEK_BRAK;
    this->licznikUmiejetnosci = 0; // umiejetnosc gotowa do użycia na starcie
}

Czlowiek::~Czlowiek()
{
}

void Czlowiek::ustawKierunek(int kierunek)
{
    this->kierunekRuchu = kierunek;
}

void Czlowiek::aktywujUmiejetnosc()
{
    if (licznikUmiejetnosci == 0) // można aktywować tylko gdy licznik jest 0
    {
        licznikUmiejetnosci = 5; // Aktywna przez 5 tur
        swiat->dodajKomunikat("CALOPALENIE AKTYWOWANE! (Pozostalo tur: 5)");
    }
    else if (licznikUmiejetnosci > 0)
    {
        swiat->dodajKomunikat("Umiejetnosc jest juz aktywna!");
    }
    else
    {
        swiat->dodajKomunikat("Umiejetnosc sie odnawia! Musisz poczekac.");
    }
}

void Czlowiek::wykonajCalopalenie()
{
    // niszczymy wszystkich sąsiadów (rośliny i zwierzęta)
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    int N = swiat->getN();
    int M = swiat->getM();

    for (int i = 0; i < 4; i++)
    {
        int sasiednieX = this->x + dx[i];
        int sasiednieY = this->y + dy[i];

        if (sasiednieX >= 0 && sasiednieX < N && sasiednieY >= 0 && sasiednieY < M)
        {
            Organizm *sasiad = swiat->getOrganizmNaPolu(sasiednieX, sasiednieY);
            if (sasiad != nullptr)
            {
                swiat->dodajKomunikat("Calopalenie spala: " + sasiad->getNazwa());
                sasiad->zabij(); // niszczymy sąsiada bez walki
            }
        }
    }
}

void Czlowiek::akcja()
{

    if (licznikUmiejetnosci < 0)
    {
        licznikUmiejetnosci++; // zbliżamy się do 0 (np. z -5 na -4)
        if (licznikUmiejetnosci == 0)
        {
            swiat->dodajKomunikat("Moc gotowa do uzycia!");
        }
    }

    // ruch czlowieka strzalkami
    int noweX = this->x;
    int noweY = this->y;

    if (kierunekRuchu != KIERUNEK_BRAK)
    {

        if (kierunekRuchu == GORA)
            noweY--;
        else if (kierunekRuchu == DOL)
            noweY++;
        else if (kierunekRuchu == LEWO)
            noweX--;
        else if (kierunekRuchu == PRAWO)
            noweX++;

        // reset, żeby w nowej turze wybrac nowy kierunek
        kierunekRuchu = KIERUNEK_BRAK;

        int N = swiat->getN();
        int M = swiat->getM();

        if (noweX >= 0 && noweX < N && noweY >= 0 && noweY < M)
        {
            Organizm *kolizyjny = swiat->getOrganizmNaPolu(noweX, noweY);

            if (kolizyjny != nullptr)
            {
                if (licznikUmiejetnosci > 0)
                {
                    swiat->dodajKomunikat("Calopalenie niszczy przy ruchu: " + kolizyjny->getNazwa());
                    kolizyjny->zabij(); // Zabijamy go natychmiast

                    // I wchodzimy na "zwolnione" pole przeciwnika
                    x = noweX;
                    y = noweY;
                }
                else
                {
                    kolizyjny->kolizja(this);
                    // Jeśli wygraliśmy, wchodzimy
                    if (this->czyZyje() && !kolizyjny->czyZyje())
                    {
                        x = noweX;
                        y = noweY;
                    }
                }
            }
            else
            {
                x = noweX;
                y = noweY;
            }
        }
    }

    if (licznikUmiejetnosci > 0)
    {
        wykonajCalopalenie();
        licznikUmiejetnosci--;

        if (licznikUmiejetnosci == 0)
        {
            licznikUmiejetnosci = -5; // cooldown (5 tur przerwy)
            swiat->dodajKomunikat("Calopalenie wygaslo. Rozpoczyna sie cooldown.");
        }
    }
}

void Czlowiek::rysowanie()
{
    // Jeśli umiejętność aktywna, rysujemy inaczej
    if (licznikUmiejetnosci > 0)
        // std::cout << KOLOR_CZLOWIEK << ")C(" << KOLOR_TEKST;
        std::cout << KOLOR_CZLOWIEK << ")C(" << KOLOR_TEKST;
    else
        // std::cout << KOLOR_CZLOWIEK << " C " << KOLOR_TEKST;
        std::cout << KOLOR_CZLOWIEK << " C " << KOLOR_TEKST;
}

void Czlowiek::zapisz(std::ostream &plik) const
{
    // Najpierw zapisujemy to co zwykłe zwierzę (X, Y, Siła...)
    Organizm::zapisz(plik);

    // A potem dopisujemy nasze unikalne cechy
    plik << " " << licznikUmiejetnosci << " " << kierunekRuchu;
}
#include "Swiat.h"
#include "Wilk.h"
#include "Owca.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "Lis.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "Jagody.h"
#include "Barszcz.h"
#include "Roslina.h"
#include "Czlowiek.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

Swiat::Swiat(int N, int M)
    : N(N), M(M), tura(0)
{
}
Swiat::~Swiat()
{
    for (int i = 0; i < organizmy.size(); i++)
    {
        delete organizmy[i];
    }
    // czyszczenie wektora ze wskaźnikow
    organizmy.clear();
}

void Swiat::dodajOrganizm(Organizm *organizm)
{
    organizmy.push_back(organizm);
}

void Swiat::losujPozycje(int &x, int &y)
{
    // losujemy wolne pole

    int proby = 0;
    do
    {
        x = rand() % N;
        y = rand() % M;
        proby++;

        // Zabezpieczenie na wypadek braku miejsca
        if (proby > 10000)
            return;

    } while (getOrganizmNaPolu(x, y) != nullptr);
}

void Swiat::wykonajTure()
{   
    for (int i = 0; i < organizmy.size(); i++) {
        if (organizmy[i]->getNazwa() == "Czlowiek" && organizmy[i]->czyZyje()) {
            Czlowiek* c = dynamic_cast<Czlowiek*>(organizmy[i]);
            // Jeśli moc jest aktywna, spalamy sąsiadów ZANIM ktokolwiek ruszy
            if (c->getLicznikUmiejetnosci() > 0) {
                c->wykonajCalopalenie(); 
            }
        }
    }


    // FUNKCJA LAMBDA anonimowa funkcja do określenia zasad sortowania
    sort(organizmy.begin(), organizmy.end(), [](Organizm *a, Organizm *b)
         {
        
        if (a->getInicjatywa() != b->getInicjatywa())
        {
            return a->getInicjatywa() > b->getInicjatywa();
        }
        
        // jeśli inicjatywa równa, starszy będzie pierwszy
        return a->getWiek() > b->getWiek(); });

    for (int i = 0; i < organizmy.size(); i++)
    {
        if (organizmy[i]->czyZyje())
        {
            organizmy[i]->akcja();
            organizmy[i]->starzejSie();
        }
    }

    for (int i = 0; i < organizmy.size(); i++)
    {
        if (organizmy[i]->czyZyje() == false)
        {
            delete organizmy[i];
            organizmy.erase(organizmy.begin() + i);
            i--;
        }
    }

    tura++;
}
void Swiat::dodajKomunikat(std::string komunikat)
{
    dziennik.push_back(komunikat);
}
void Swiat::rysujSwiat()
{
    //system("cls"); // dla Windows
    system("clear"); // dla MacOS

    cout << KOLOR_TEKST << "Aleksandra Janiuk 206419 | Tura: " << tura << endl
         << KOLOR_TEKST;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Organizm *znaleziony = NULL;

            for (int k = 0; k < organizmy.size(); k++)
            {
                if (organizmy[k]->getX() == j && organizmy[k]->getY() == i)
                {
                    znaleziony = organizmy[k];
                    break;
                }
            }

            if (znaleziony != NULL)
            {
                znaleziony->rysowanie();
            }
            else
            {
                cout << KOLOR_PLANSZY << " . " << KOLOR_TEKST;
            }
        }
        cout << endl;
    }

    cout << "--------------------------------" << endl;
    cout << "Dziennik zdarzen:" << endl;
    for (const auto &wpis : dziennik)
    {
        cout << wpis << endl;
    }
    cout << "--------------------------------" << endl;

    dziennik.clear();
}
Organizm *Swiat::getOrganizmNaPolu(int x, int y)
{
    for (int i = 0; i < organizmy.size(); i++)
    {
        if (organizmy[i]->getX() == x && organizmy[i]->getY() == y)
        {
            return organizmy[i];
        }
    }
    return NULL;
}

bool Swiat::czyCzlowiekZyje()
{
    for (int i = 0; i < organizmy.size(); i++)
    {
        if (organizmy[i]->getNazwa() == "Czlowiek")
        {
            return true; // znaleziono człowieka na liście
        }
    }
    return false; // przeszukano wszystko i nie znaleziono
}

void Swiat::zapiszSwiat(string nazwaPliku)
{
    ofstream plik(nazwaPliku);
    if (!plik.is_open())
        return;

    // zapisujemy wymiary świata i numer tury
    plik << N << " " << M << endl;
    plik << tura << endl;

    // zapisujemy liczbę organizmów
    plik << organizmy.size() << endl;

    // pętla po wszystkich organizmach
    for (int i = 0; i < organizmy.size(); i++)
    {
        organizmy[i]->zapisz(plik);
        plik << endl; // Nowa linia dla każdego zwierzaka
    }

    dodajKomunikat("Zapisano stan gry do pliku!");
    plik.close();
}

void Swiat::wczytajSwiat(string nazwaPliku)
{
    ifstream plik(nazwaPliku);
    if (!plik.is_open())
    {
        dodajKomunikat("Nie udalo sie otworzyc pliku zapisu!");
        return;
    }

    // czyścimy obecny świat
    for (int i = 0; i < organizmy.size(); i++)
        delete organizmy[i];
    organizmy.clear();

    // wczytujemy wymiary
    int noweN, noweM;
    plik >> noweN >> noweM;
    this->N = noweN;
    this->M = noweM;
    plik >> this->tura;

    int liczbaOrganizmow;
    plik >> liczbaOrganizmow;

    // wczytywanie po kolei
    for (int i = 0; i < liczbaOrganizmow; i++)
    {
        string typ;
        int x, y, sila, inicjatywa, wiek;

        plik >> typ >> x >> y >> sila >> inicjatywa >> wiek;

        Organizm *nowy = nullptr;

        if (typ == "Lis")
            nowy = new Lis(x, y, this);
        else if (typ == "Owca")
            nowy = new Owca(x, y, this);
        else if (typ == "Wilk")
            nowy = new Wilk(x, y, this);
        else if (typ == "Zolw")
            nowy = new Zolw(x, y, this);
        else if (typ == "Antylopa")
            nowy = new Antylopa(x, y, this);
        else if (typ == "Trawa")
            nowy = new Trawa(x, y, this);
        else if (typ == "Mlecz")
            nowy = new Mlecz(x, y, this);
        else if (typ == "Guarana")
            nowy = new Guarana(x, y, this);
        else if (typ == "WilczeJagody")
            nowy = new Jagody(x, y, this);
        else if (typ == "BarszczSosnowskiego")
            nowy = new Barszcz(x, y, this);
        else if (typ == "Czlowiek")
        {
            Czlowiek *czlowiek = new Czlowiek(x, y, this);
            int licznik, kierunek;
            plik >> licznik >> kierunek; // doczytujemy specyficzne dane
            czlowiek->setLicznik(licznik);
            czlowiek->ustawKierunek(kierunek);
            nowy = czlowiek;
        }

        if (nowy != nullptr)
        {
            // Nadpisujemy statystyki
            nowy->setSila(sila);
            nowy->setInicjatywa(inicjatywa);
            nowy->setWiek(wiek);
            organizmy.push_back(nowy);
        }
    }

    dodajKomunikat("Wczytano stan gry!");
    plik.close();
}

// metoda pomocnicza, żeby main wiedział gdzie jest nowy człowiek
Czlowiek *Swiat::getCzlowiek()
{
    for (int i = 0; i < organizmy.size(); i++)
    {
        if (organizmy[i]->getNazwa() == "Czlowiek")
            return dynamic_cast<Czlowiek *>(organizmy[i]);
    }
    return nullptr;
}
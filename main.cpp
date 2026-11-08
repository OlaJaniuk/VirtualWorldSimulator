#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <cmath>
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
#include "PobierzZnak.h"

using namespace std;

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_LEFT 68
#define KEY_RIGHT 67
#define KEY_SKILL 'm'
#define KEY_ENTER 10
#define KEY_ESC 27

int main()
{

    srand(time(NULL));

    int szerokosc, wysokosc;

    // pobranie wymiarow planszy od uzytkownika
    cout << "--- SYMULATOR SWIATA ---" << endl;
    cout << "Podaj szerokosc planszy (np. 20): ";
    cin >> szerokosc;
    cout << "Podaj wysokosc planszy (np. 20): ";
    cin >> wysokosc;

    // zabezpieczenie przed zbyt małą planszą
    if (szerokosc < 5)
    {
        szerokosc = 5;
    }

    if (wysokosc < 5)
    {
        wysokosc = 5;
    }

    Swiat swiat(szerokosc, wysokosc);

    // najpierw dodajemy Człowieka (zawsze jeden)
    int x, y;
    swiat.losujPozycje(x, y);

    // musi byc wskaźnik na człowieka, żeby móc nim sterować z main
    Czlowiek *czlowiek = new Czlowiek(x, y, &swiat);
    swiat.dodajOrganizm(czlowiek);

    // Liczba organizmów zależna od wielkości planszy (np. 20% pól to zwierzęta)
    int liczbaPol = szerokosc * wysokosc;
    int startowaLiczbaOrganizmow = sqrt(liczbaPol); // np. dla 20x20=400 pól -> 80 zwierząt

    // 75% zwierzęta
    int liczbaZwierzat = (int)(startowaLiczbaOrganizmow * 0.75);

    // 25% rośliny
    int liczbaRoslin = startowaLiczbaOrganizmow - liczbaZwierzat;

    // respienie zwierzat
    for (int i = 0; i < liczbaZwierzat; i++)
    {
        swiat.losujPozycje(x, y);

        int typ = rand() % 5;

        if (typ == 0)
            swiat.dodajOrganizm(new Lis(x, y, &swiat));
        else if (typ == 1)
            swiat.dodajOrganizm(new Owca(x, y, &swiat));
        else if (typ == 2)
            swiat.dodajOrganizm(new Wilk(x, y, &swiat));
        else if (typ == 3)
            swiat.dodajOrganizm(new Zolw(x, y, &swiat));
        else if (typ == 4)
            swiat.dodajOrganizm(new Antylopa(x, y, &swiat));
    }

    // respienie roslin
    for (int i = 0; i < liczbaRoslin; i++)
    {
        swiat.losujPozycje(x, y);

        int typ = rand() % 5;

        if (typ == 0)
            swiat.dodajOrganizm(new Trawa(x, y, &swiat));
        else if (typ == 1)
            swiat.dodajOrganizm(new Mlecz(x, y, &swiat));
        else if (typ == 2)
            swiat.dodajOrganizm(new Guarana(x, y, &swiat));
        else if (typ == 3)
            swiat.dodajOrganizm(new Jagody(x, y, &swiat));
        else if (typ == 4)
            swiat.dodajOrganizm(new Barszcz(x, y, &swiat));
    }

    //----start gry----
    string opisRuchu = "BRAK";

    swiat.rysujSwiat();
    cout << "PLANOWANY RUCH: " << opisRuchu << endl;
    cout << "[Strzalki] Ruch | [M] Moc | [ENTER] Czekaj | [Z] Zapis | [W] Wczytaj | [ESC] Wyjscie" << endl;

    while (true)
    {
        // _getch() pobiera znak bez czekania na Enter
        //int znak = _getch();
        int znak = PobierzZnak::getch();

        bool wykonajTure = false;
        // sprawdzmay czy czlowiek zyje raz na obieg petli
        bool czlowiekZyje = swiat.czyCzlowiekZyje();

        if (znak == 27 ) // Wykryto strzałkę lub ESC (kod specjalny)
        {
            //znak = _getch(); // Pobieramy drugi kod strzałki
            int znak2 = PobierzZnak::getch();

            if (znak2 == 91)  // czyli to strzałka na MacOS :P
            {
                int znak3 = PobierzZnak::getch();
                if (czlowiekZyje)
                {
                    if (znak3 == KEY_UP)
                {
                    czlowiek->ustawKierunek(0);
                }
                else if (znak3 == KEY_DOWN)
                {
                    czlowiek->ustawKierunek(1);
                }
                else if (znak3 == KEY_LEFT)
                {
                    czlowiek->ustawKierunek(2);
                }
                else if (znak3 == KEY_RIGHT)
                {
                    czlowiek->ustawKierunek(3);
                }

                wykonajTure = true;

                }
                

            }
            else
            {
                break;
            }


            
        }
        else if (znak == KEY_ENTER)
        {
            if (czlowiekZyje)
            {
                czlowiek->ustawKierunek(-1);
            }
            wykonajTure = true;
        }
        else if ((znak == KEY_SKILL || znak == 'm' || znak == 'M') && czlowiekZyje)
        {
            czlowiek->aktywujUmiejetnosc();

            swiat.rysujSwiat();
            cout << "[Strzalki] Ruch | [M] Moc | [ENTER] Czekaj | [Z] Zapis | [W] Wczytaj | [ESC] Wyjscie" << endl;
        }

        else if (znak == KEY_ESC)
        {
            break;
        }

        else if (znak == 'z' || znak == 'Z')
        {
            swiat.zapiszSwiat("zapis.txt");
            swiat.rysujSwiat();
            cout << "[Strzalki] Ruch | [M] Moc | [ENTER] Czekaj | [Z] Zapis | [W] Wczytaj | [ESC] Wyjscie" << endl;
        }
        else if (znak == 'w' || znak == 'W')
        {
            swiat.wczytajSwiat("zapis.txt");

            // po wczytaniu musimy odzyskać sterowanie nad nowym człowiekiem
            // stary wskaźnik 'czlowiek' wskazuje teraz na usuniętą pamięć.
            czlowiek = swiat.getCzlowiek(); // Pobieramy nowego człowieka ze świata

            swiat.rysujSwiat();
            cout << "[Strzalki] Ruch | [M] Moc | [ENTER] Czekaj | [Z] Zapis | [W] Wczytaj | [ESC] Wyjscie" << endl;
        }

        if (wykonajTure)
        {
            swiat.wykonajTure();
            swiat.rysujSwiat();

            if (swiat.czyCzlowiekZyje())
            {
                cout << "[Strzalki] Ruch | [M] Moc | [ENTER] Czekaj | [Z] Zapis | [W] Wczytaj | [ESC] Wyjscie" << endl;
            }
            else
            {
                cout << "--- NIE ZYJESZ --- (Tryb obserwatora)" << endl;
                cout << "[ENTER] Kolejna tura | [Z] Zapisz | [W] Wczytaj | [ESC] Wyjscie" << endl;
            }
        }
    }

    return 0;
}

// g++ -std=c++11 main.cpp Czlowiek.cpp Wilk.cpp Owca.cpp Lis.cpp Zolw.cpp Antylopa.cpp Zwierze.cpp Organizm.cpp Roslina.cpp Trawa.cpp Mlecz.cpp Guarana.cpp Jagody.cpp Barszcz.cpp -o swiat
// g++ -std=c++11 *.cpp -o swiat
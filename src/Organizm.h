#ifndef ORGANIZM_H
#define ORGANIZM_H

#define KOLOR_PLANSZY "\033[38;2;92;96;102m"
#define KOLOR_TEKST "\033[38;2;199;208;221m"
#define KOLOR_CZLOWIEK "\033[38;2;255;120;194m"
#define KOLOR_WILK "\033[38;2;0;0;0m"
#define KOLOR_OWCA "\033[38;2;230;240;255m"
#define KOLOR_LIS "\033[38;2;221;140;60m"
#define KOLOR_ZOLW "\033[38;2;47;141;163m"
#define KOLOR_ANTYLOPA "\033[38;2;198;180;131m"
#define KOLOR_TRAWA "\033[38;2;66;119;53m"
#define KOLOR_MLECZ "\033[38;2;234;224;131m"
#define KOLOR_GUARANA "\033[38;2;188;0;0m"
#define KOLOR_JAGODY "\033[38;2;190;67;255m"
#define KOLOR_BARSZCZ "\033[38;2;97;147;97m"

#include <iostream>
#include <fstream>

// zapowiedz klasy swiat
class Swiat;

class Organizm
{
public:
    // Destruktor wirtualny, żeby usuwał też ze wszystkich klas ktore dziedzicza
    virtual ~Organizm();

    // Metody abstrakcyjne (czysto wirtualne = 0)
    virtual void akcja() = 0;
    virtual void kolizja(Organizm *atakujacy) = 0;
    virtual void rysowanie() = 0;

    virtual std::string getNazwa() const = 0;
    int getSila() const { return sila; }
    int getInicjatywa() const { return inicjatywa; }
    int getWiek() const { return wiek; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool czyZyje() const { return zyje; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setSila(int sila) { this->sila = sila; }
    void setInicjatywa(int inicjatywa) { this->inicjatywa = inicjatywa; }
    void setWiek(int wiek) { this->wiek = wiek; }

    void zabij() { zyje = false; }
    void starzejSie() { wiek++; }
    virtual bool czyOdbilAtak(Organizm *atakujacy) { return false; }
    virtual void zapisz(std::ostream &plik) const;

protected:
    int sila;
    int inicjatywa;
    int x;
    int y;
    bool zyje;
    int wiek;

    // referencja do swiata w ktorym zyje organizm
    Swiat *swiat;

    // Konstruktor jest protected bo nie istnieje na planszy np. organizm, tylko juz konkretnie np Wilk
    Organizm(int sila, int inicjatywa, int x, int y, Swiat *swiat);

    bool znajdzWolnePole(int &noweX, int &noweY) const;
    virtual Organizm *stworzNowy(int x, int y) const = 0;
};

#endif
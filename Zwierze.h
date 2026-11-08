#ifndef ZWIERZE_H
#define ZWIERZE_H

#include "Organizm.h"

class Zwierze : public Organizm
{
public:
    ~Zwierze() override;

    virtual bool czyOdbilAtak(Organizm *atakujacy) override { return false; }
    virtual void akcja() override;
    virtual void kolizja(Organizm *atakujacy) override;

protected:
// Konstruktor jest protected bo nie istnieje na planszy zwierze tylko juz konkretnie np wilk
    Zwierze(int sila, int inicjatywa, int x, int y, Swiat *swiat);
    virtual int getZasiegRuchu() const { return 1; }
    virtual bool czyRuchJestBezpieczny(Organizm *cel) const { return true; }
    void rozmnozSie();
};

#endif
#ifndef ROSLINA_H
#define ROSLINA_H

#include "Organizm.h"

class Roslina : public Organizm
{
public:
    ~Roslina() override;

    virtual void akcja() override;
    virtual void kolizja(Organizm *atakujacy) override;

protected:
// Konstruktor jest protected bo nie istnieje na planszy roslina tylko juz konkretnie np trawa
    Roslina(int sila, int x, int y, Swiat *swiat);
    virtual int getSzanseRozsiania() const { return 3; }

};

#endif
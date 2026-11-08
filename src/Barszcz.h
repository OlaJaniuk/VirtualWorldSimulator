#ifndef BARSZCZ_H
#define BARSZCZ_H

#include <iostream>
#include "Roslina.h"

class Barszcz : public Roslina
{
public:
    Barszcz(int x, int y, Swiat *swiat);
    ~Barszcz() override;

    virtual void akcja() override;
    virtual void kolizja(Organizm *atakujacy) override;
    virtual void rysowanie() override;
    std::string getNazwa() const override { return "BarszczSosnowskiego"; }
    
protected:
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
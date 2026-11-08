#ifndef ZOLW_H
#define ZOLW_H

#include <iostream>
#include "Zwierze.h"

class Zolw : public Zwierze
{
public:
    Zolw(int x, int y, Swiat *swiat);
    ~Zolw() override;

    void akcja() override;
    bool czyOdbilAtak(Organizm *atakujacy) override;
    void rysowanie() override;
    std::string getNazwa() const override { return "Zolw"; }

protected:
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
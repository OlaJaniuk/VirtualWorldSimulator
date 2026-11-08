#ifndef ANTYLOPA_H
#define ANTYLOPA_H

#include <iostream>
#include "Zwierze.h"

class Antylopa : public Zwierze
{
public:
    Antylopa(int x, int y, Swiat *swiat);
    ~Antylopa() override;

    bool czyOdbilAtak(Organizm *atakujacy) override;
    void rysowanie() override;
    std::string getNazwa() const override { return "Antylopa"; }

protected:
    int getZasiegRuchu() const override { return 2; }
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
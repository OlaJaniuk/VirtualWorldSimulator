#ifndef GUARANA_H
#define GUARANA_H

#include <iostream>
#include "Roslina.h"

class Guarana : public Roslina
{
public:
    Guarana(int x, int y, Swiat *swiat);
    ~Guarana() override;

    virtual void kolizja(Organizm *atakujacy) override;
    virtual void rysowanie() override;
    std::string getNazwa() const override { return "Guarana"; }
    
protected:
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
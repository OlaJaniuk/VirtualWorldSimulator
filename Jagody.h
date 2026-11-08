#ifndef JAGODY_H
#define JAGODY_H

#include <iostream>
#include "Roslina.h"

class Jagody : public Roslina
{
public:
    Jagody(int x, int y, Swiat *swiat);
    ~Jagody() override;

    virtual void kolizja(Organizm *atakujacy) override;
    virtual void rysowanie() override;
    std::string getNazwa() const override { return "WilczeJagody"; }
    
protected:
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
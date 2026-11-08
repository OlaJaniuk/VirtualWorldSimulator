#ifndef TRAWA_H
#define TRAWA_H

#include <iostream>
#include "Roslina.h"

class Trawa : public Roslina
{


public:
    Trawa(int x, int y, Swiat *swiat);
    ~Trawa() override;

    virtual void rysowanie() override;
    std::string getNazwa() const override { return "Trawa"; }

protected:
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
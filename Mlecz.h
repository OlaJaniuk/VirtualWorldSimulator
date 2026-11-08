#ifndef MLECZ_H
#define MLECZ_H

#include <iostream>
#include "Roslina.h"

class Mlecz : public Roslina
{
public:
    Mlecz(int x, int y, Swiat *swiat);
    ~Mlecz() override;

    virtual void akcja() override;
    virtual void rysowanie() override;
    std::string getNazwa() const override { return "Mlecz"; }
    
protected:
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
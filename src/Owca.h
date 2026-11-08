#ifndef OWCA_H
#define OWCA_H

#include <iostream>
#include "Zwierze.h"

class Owca : public Zwierze
{
public:
    Owca(int x, int y, Swiat *swiat);
    ~Owca() override;

    void rysowanie() override;
    std::string getNazwa() const override { return "Owca"; }

protected:
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
#ifndef WILK_H
#define WILK_H

#include <iostream>
#include "Zwierze.h"

class Wilk : public Zwierze
{
public:
    Wilk(int x, int y, Swiat *swiat);
    ~Wilk() override;

    void rysowanie() override;
    std::string getNazwa() const override { return "Wilk"; }

protected:
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
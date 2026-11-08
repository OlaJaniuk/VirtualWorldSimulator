#ifndef LIS_H
#define LIS_H

#include <iostream>
#include "Zwierze.h"

class Lis : public Zwierze
{
public:
    Lis(int x, int y, Swiat *swiat);
    ~Lis() override;

    void rysowanie() override;
    std::string getNazwa() const override { return "Lis"; }
    
protected:
    bool czyRuchJestBezpieczny(Organizm *cel) const override;
    virtual Organizm *stworzNowy(int x, int y) const override;
};

#endif
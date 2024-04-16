#pragma once
#include "figure.h"

template<int valeur>
class Somme : public figure {
public:
    Somme(int s, bool m);
    Somme();
    int calculerPoints(const std::vector<int>& des) const override;
    void afficherResultat() const override;
    std::string save() const override;
};

template<int valeur>
Somme<valeur>::Somme(int s, bool m)
{
    sc = s;
    marque = m;
    type = 0;
}

template<int valeur>
Somme<valeur>::Somme()
{
    sc = 0;
    marque = 0;
    type = 0;
}

template<int valeur>
int Somme<valeur>::calculerPoints(const std::vector<int>& des) const
{
    int nombre = 0;
    for (int val : des) {
        if (val == valeur) {
            nombre++;
        }
    }
    return valeur * nombre;
}

template<int valeur>
void Somme<valeur>::afficherResultat() const
{
    switch (valeur) {
    case 1:
        std::cout << "One : " << sc;
        break;
    case 2:
        std::cout << "Two : " << sc;
        break;
    case 3:
        std::cout << "Three : " << sc;
        break;
    case 4:
        std::cout << "Four : " << sc;
        break;
    case 5:
        std::cout << "Five : " << sc;
        break;
    case 6:
        std::cout << "Six : " << sc;
        break;
    }
}

template<int valeur>
std::string Somme<valeur>::save() const
{
    std::string txt = "";
    switch (valeur) {
    case 1:
        txt = "One=" + std::to_string(sc);
        txt += "=" + std::to_string(marque);
        break;
    case 2:
        txt = "Two=" + std::to_string(sc);
        txt += "=" + std::to_string(marque);
        break;
    case 3:
        txt = "Three=" + std::to_string(sc);
        txt += "=" + std::to_string(marque);
        break;
    case 4:
        txt = "Four=" + std::to_string(sc);
        txt += "=" + std::to_string(marque);
        break;
    case 5:
        txt = "Five=" + std::to_string(sc);
        txt += "=" + std::to_string(marque);
        break;
    case 6:
        txt = "Six=" + std::to_string(sc);
        txt += "=" + std::to_string(marque);
        break;
    }
    return txt;
}

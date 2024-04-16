#pragma once
#include "joueur.h"
class ia : public Joueur
{
public : 
    ia(const std::string& nom);
    void jouerTourFacile(lancer& lancer);
    void afficherScore();
};


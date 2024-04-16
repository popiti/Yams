#include "regles.h"
#include <iostream>
void regles::afficherMineure()
{
    std::cout << "Partie Mineure:\n";
    std::cout << "Figure   | Condition                   | Score          | Score maximum\n";
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "1        | Obtenir le maximum de 1     | Somme des 1    | 5 points\n";
    std::cout << "2        | Obtenir le maximum de 2     | Somme des 2    | 10 points\n";
    std::cout << "3        | Obtenir le maximum de 3     | Somme des 3    | 15 points\n";
    std::cout << "4        | Obtenir le maximum de 4     | Somme des 4    | 20 points\n";
    std::cout << "5        | Obtenir le maximum de 5     | Somme des 5    | 25 points\n";
    std::cout << "6        | Obtenir le maximum de 6     | Somme des 6    | 30 points\n";

}

void regles::afficherMajeure()
{
    std::cout << "\nPartie Majeure:\n";
    std::cout << "Figure       | Condition                                     | Score                           | Score maximum\n";
    std::cout << "----------------------------------------------------------------------------------------------------------\n";
    std::cout << "Brelan       | Obtenir trois des de même valeur              | Somme des trois dés identiques  | 18 points\n";
    std::cout << "Carre        | Obtenir quatre des de même valeur             | Somme des quatre dés identiques | 24 points\n";
    std::cout << "Full         | Obtenir un brelan et deux des de même valeur  | 25 points                       | 25 points\n";
    std::cout << "Petite suite | Obtenir une suite croissante de quatre des    | 30 points                       | 30 points\n";
    std::cout << "Grande suite | Obtenir une suite croissante de cinq des      | 40 points                       | 40 points\n";
    std::cout << "Yahtzee      | Obtenir cinq des de même valeur               | 50 points                       | 50 points\n";
    std::cout << "Chance       | Aucune condition                              | Somme des cinq des              | 30 points\n";
    std::cout << std::endl;
}
#include "ia.h"

ia::ia(const std::string& nom):Joueur(nom)
{
}

void ia::jouerTourFacile(lancer& lancer) {
    afficherFeuilleScore();
    std::cout << getNom() << ", c'est a vous de jouer !" << std::endl;
    lancer.lancerDes();
    const std::vector<int>& resultatsDes = lancer.getResultatsDes();
    std::cout << "Resultats du lancer : ";
    for (int resultat : resultatsDes) {
        std::cout << resultat << " ";
    }
    std::cout << std::endl;
    std::cout << "Figures possibles : " << std::endl;
    int i = 0;
    int max = 0;
    int choix = 0;
    for (const auto& figure : figures) {
        i++;
        std::cout << i << " --- ";
        figure->afficherResultat();
        if (!figure->marque)
        {
            std::cout << " -> " << figure->calculerPoints(resultatsDes);
            if (max < figure->calculerPoints(resultatsDes) || (max <= figure->calculerPoints(resultatsDes) && choix ==0 ))
            {
                max = figure->calculerPoints(resultatsDes);
                choix = i;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    isYams(resultatsDes);
        if (choix >= 1 && choix <= static_cast<int>(figures.size())) {
            std::unique_ptr<figure>& categorieChoisie = figures[choix - 1];

            if (categorieChoisie && !categorieChoisie->marque) {

                int points = categorieChoisie->calculerPoints(resultatsDes);
                setScore(getScore()+points);
                std::cout << "Vous avez obtenu " << points << " points pour cette categorie !" << std::endl;
                categorieChoisie->sc = points;
                categorieChoisie->marque = true;
            }
        }
}

void ia::afficherScore()
{
    Joueur::afficherScore();
}
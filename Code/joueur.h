#include <string>
#include <memory>
#include "lancer.h"
#include "figure.h"
#include <fstream>
#include <sstream>

class Joueur {
private:
    std::string nom;
    int score;
    int bonusYams;

public:
    std::vector<std::unique_ptr<figure>> figures;
    Joueur(const std::string& nom);
    Joueur(const std::string& nom, int sc);
    void chargerFigure(std::string nomFig,int scoreFig, bool marqueFig);
    void jouerTourFacile(lancer& lancer);
    void jouerTourNormal(lancer& lancer);
    void jouerTourDifficile(lancer& lancer);
    void jouerTourHardCore(lancer& lancer,int categorie);
    bool checkType();
    void addScoreDifficile(const std::vector<int>& resultatsDes);
    void addScoreHardCore(const std::vector<int>& resultatsDes, int categorie);
    void relancerDes(lancer& lancer);
    void afficherScore();
    void afficherFeuilleScore() const;
    void enregistrerScorePartiel(std::ofstream& file);
    std::string getNom() const;
    int getScore() const;
    void setScore(int s);
    void setNom(std::string n);
    void checkBonus();
    void isYams(const std::vector<int>& resultatsDes);
};



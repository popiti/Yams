#include "ia.h"

enum class Difficulte {
    facile,
    normal,
    difficile,
    hard_core
};


class Partie {
private:
    std::vector<Joueur> joueurs;
    size_t joueurActuel;
    size_t nombreMaxJoueurs;
    size_t nombreTours;
    Difficulte difficulte;

public:
    Partie(size_t nombreMaxJoueurs, size_t nombreTours,Difficulte diff);
    void setnombreMaxJoueurs(size_t nombreMaxJoueurs);
    void setnombreTours(size_t nombreTours);
    void demarrerPartie(lancer& lancer);
    void demarrerPartieIA(lancer& lancer);
    void chargerPartie(lancer& lancer);
    void demarrerPartieCharge(lancer& lancer,int tour, std::vector<int> ordreFig);
    void passerTour();
    void save(int tour, std::vector<int> ordreFig);
    bool estPartieTerminee() const;
    void afficherGagnant() const;
    void afficherScoresFinaux() ;
    void afficherGagnantIA(ia& jia) const;
    void afficherScoresFinauxIA(ia& jia);
    std::string getDifficulte(std::vector<int> ordreFig);
    void setDifficulte(std::string diff);
};


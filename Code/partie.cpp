#include "partie.h"
#include <fstream>
#include <sstream>
#include <string>
#include <random>
Partie::Partie(size_t nombreMaxJoueurs, size_t nombreTours, Difficulte diff)
    : joueurActuel(0), nombreMaxJoueurs(nombreMaxJoueurs), nombreTours(nombreTours), difficulte(diff) {
}

void Partie::setnombreMaxJoueurs(size_t nbJ){
    nombreMaxJoueurs=nbJ;
}
void Partie::setnombreTours(size_t nbT){
    nombreTours=nbT;
}
void Partie::save(int tour,std::vector<int> ordreFig){
    std::cout << "Save en cours" << std::endl;
    std::ofstream file("savePartie.txt");
    if (file.is_open()) {
            file << "difficulte=" << getDifficulte(ordreFig) << std::endl;
            file  <<"tour="<< tour <<  std::endl;
            file  <<"tourMax="<< nombreTours <<  std::endl;
            file  <<"nbJoueur="<< nombreMaxJoueurs <<  std::endl;
            for (size_t i = 0; i < nombreMaxJoueurs; ++i) {
                file  <<"joueur="<< joueurs[i].getNom() << "=" << joueurs[i].getScore() << std::endl;
                joueurs[i].enregistrerScorePartiel(file);
                file  <<"";
            }
            file.close();
    } else {
        std::cerr << "Unable to open file for writing: "  << std::endl;
    }
}
void Partie::chargerPartie(lancer& lancer){

    std::ifstream file("savePartie.txt");
    std::string line;
    int i = 0;
    int tour=0;
    std::vector<int> ordreCharge;
    while (!file.eof()) {
        std::getline(file, line);
        std::stringstream ss(line);
        std::string cle;
        std::string val;
        std::getline(ss, cle, '=');
        if (cle=="difficulte")
        {
            std::getline(ss, val,'=');
            setDifficulte(val);
            if (difficulte == Difficulte::hard_core)
            {
                std::getline(ss, val, '=');
                while (val != "")
                {
                    ordreCharge.push_back(stoi(val));
                    std::getline(ss, val, '=');
                }
            }
        }
        else if(cle=="tour"){
            std::getline(ss, val);
            tour=stoi(val)+1;
        }
        else if(cle=="tourMax"){
            std::getline(ss, val);
            setnombreTours(stoi(val));
        }
        else if(cle=="nbJoueur"){
            std::getline(ss, val);
            setnombreMaxJoueurs(stoi(val));
        }
        else if(cle=="joueur"){
            std::getline(ss, val,'=');
            std::string scoreL;
            std::getline(ss, scoreL);
            joueurs.push_back(Joueur(val,stoi(scoreL)));
        }
        else if(cle==""){
            std::cout << "Chaine vide" <<  std::endl;
        }
        else{

            std::string score;
            std::string marque;
            std::getline(ss, score, '=');
            std::getline(ss, marque);
            bool marqueb=stoi(marque);
            joueurs.back().chargerFigure(cle,stoi(score),marqueb);
        }
        i++;
    }
    demarrerPartieCharge(lancer,tour,ordreCharge);
}
void Partie::demarrerPartieCharge(lancer& lancer, int t, std::vector<int> ordreFig){
    for (size_t tour = t; tour <= nombreTours; ++tour) {
        std::cout << "Tour " << tour << " : " << std::endl;

        for (size_t i = 0; i < nombreMaxJoueurs; ++i) {

            std::cout << "Tour du joueur : " << joueurs[i].getNom() << std::endl;
            if (difficulte == Difficulte::facile)
            {
                joueurs[joueurActuel].jouerTourFacile(lancer);
            }
            if (difficulte == Difficulte::normal)
            {
                joueurs[joueurActuel].jouerTourNormal(lancer);
            }
            if (difficulte == Difficulte::difficile)
            {
                joueurs[joueurActuel].jouerTourDifficile(lancer);
            }
            if (difficulte == Difficulte::hard_core)
            {
                joueurs[joueurActuel].jouerTourHardCore(lancer, ordreFig.front());
            }
            passerTour();
        }
        if (difficulte == Difficulte::hard_core)
            ordreFig.erase(ordreFig.begin());
    }
    afficherScoresFinaux();
    afficherGagnant();
}

void Partie::demarrerPartie(lancer& lancer) {

    for (size_t i = 0; i < nombreMaxJoueurs; ++i) {
        std::string nomJoueur = "Joueur " + std::to_string(i + 1);
        joueurs.push_back(Joueur(nomJoueur));
    }
    std::vector<int> ordreFig;
    for (int j = 0;j < 13;++j)
    {
        ordreFig.push_back(j);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ordreFig.begin(), ordreFig.end(), g); // doc cpp reference
    for (size_t tour = 1; tour <= nombreTours; ++tour) {
        std::cout << "Tour " << tour << " : " << std::endl;

        for (size_t i = 0; i < nombreMaxJoueurs; ++i) {

            std::cout << "Tour du joueur : " << joueurs[joueurActuel].getNom() << std::endl;
            if (difficulte == Difficulte::facile)
            {
                joueurs[joueurActuel].jouerTourFacile(lancer);
            }
            if (difficulte == Difficulte::normal)
            {
                joueurs[joueurActuel].jouerTourNormal(lancer);
            }
            if (difficulte == Difficulte::difficile)
            {
                joueurs[joueurActuel].jouerTourDifficile(lancer);
            }
            if (difficulte == Difficulte::hard_core)
            {
                joueurs[joueurActuel].jouerTourHardCore(lancer,ordreFig.front());
            }
            passerTour();
        }
        ordreFig.erase(ordreFig.begin());
        char relancer;
        do {
            std::cout << "Voulez-vous sauvegarder votre partie? (o/n) : ";
            std::cin >> relancer;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (relancer != 'o' && relancer != 'O' && relancer != 'n' && relancer != 'N');
        if (relancer == 'o' || relancer == 'O') {
            save(tour, ordreFig);
        }
    }
    afficherScoresFinaux();
    afficherGagnant();
}

void Partie::demarrerPartieIA(lancer& lancer) {

    for (size_t i = 0; i < nombreMaxJoueurs; ++i) {
        std::string nomJoueur = "Joueur " + std::to_string(i + 1);
        joueurs.push_back(Joueur(nomJoueur));
    }
    ia jIA("Joueur IA");
    std::vector<int> ordreFig;
    for (int j = 0;j < 13;++j)
    {
        ordreFig.push_back(j);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ordreFig.begin(), ordreFig.end(), g);
    for (size_t tour = 1; tour <= nombreTours; ++tour) {
        std::cout << "Tour " << tour << " : " << std::endl;

        for (size_t i = 0; i < nombreMaxJoueurs; ++i) {

            std::cout << "Tour du joueur : " << joueurs[joueurActuel].getNom() << std::endl;
            if (difficulte == Difficulte::facile)
            {
                joueurs[joueurActuel].jouerTourFacile(lancer);
                jIA.jouerTourFacile(lancer);
            }
            if (difficulte == Difficulte::normal)
            {
                joueurs[joueurActuel].jouerTourNormal(lancer);
                jIA.jouerTourFacile(lancer);
            }
            if (difficulte == Difficulte::difficile)
            {
                joueurs[joueurActuel].jouerTourDifficile(lancer);  
                jIA.jouerTourFacile(lancer);
            }
            if (difficulte == Difficulte::hard_core)
            {
                joueurs[joueurActuel].jouerTourHardCore(lancer, ordreFig.front());
                jIA.jouerTourFacile(lancer);
            }
            passerTour();
        }
        ordreFig.erase(ordreFig.begin());
        char relancer;
        do {
            std::cout << "Voulez-vous sauvegarder votre partie? (o/n) : ";
            std::cin >> relancer;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (relancer != 'o' && relancer != 'O' && relancer != 'n' && relancer != 'N');
        if (relancer == 'o' || relancer == 'O') {
            save(tour, ordreFig);
        }
    }
    afficherScoresFinauxIA(jIA);
    afficherGagnantIA(jIA);
}

void Partie::afficherScoresFinaux() {

    std::cout << "Scores finaux : " << std::endl;
    for (Joueur& joueur : joueurs) {
        joueur.afficherScore();
    }
}

void Partie::afficherGagnantIA(ia& jia) const
{
    int score = 0;
    for (size_t i = 0; i < nombreMaxJoueurs; ++i) {
        if (joueurs[i].getScore() > score)
        {
            score = joueurs[i].getScore();
        }
    }

    if (jia.getScore() > score)
    {
        std::cout << "Le gagnant est : " << jia.getNom() << std::endl;
    }
    else if (jia.getScore() == score)
    {
        for (size_t i = 0; i < nombreMaxJoueurs; ++i) {
            if (joueurs[i].getScore() == score)
            {
                std::cout << "Le gagnant est : " << joueurs[i].getNom() << std::endl;
            }
        }
        std::cout << "Le gagnant est : " << jia.getNom() << std::endl;
    }
    else
    {
        for (size_t i = 0; i < nombreMaxJoueurs; ++i) {
            if (joueurs[i].getScore() == score)
            {
                std::cout << "Le gagnant est : " << joueurs[i].getNom() << std::endl;
            }
        }
    }
}

void Partie::afficherScoresFinauxIA(ia& jia)
{
    std::cout << "Scores finaux : " << std::endl;
    for (Joueur& joueur : joueurs) {
        joueur.afficherScore();
    }
    jia.afficherScore();
}

std::string Partie::getDifficulte(std::vector<int> ordreFig)
{
    if (difficulte == Difficulte::facile) return "facile";
    if (difficulte == Difficulte::normal) return "normal";
    if (difficulte == Difficulte::difficile) return "difficile";
    if (difficulte == Difficulte::hard_core)
    {
        std::string txt="hard_core";
        for (int val : ordreFig)
        {
            txt += "=" + std::to_string(val);
        }
        txt += "=";
        return txt;
    }
}

void Partie::setDifficulte(std::string diff)
{
    if (diff == "facile") difficulte=Difficulte::facile;
    if (diff == "normal") difficulte = Difficulte::normal;
    if (diff == "difficile") difficulte = Difficulte::difficile;
    if (diff == "hard_core") difficulte = Difficulte::hard_core;
}

void Partie::passerTour() {

    joueurActuel = (joueurActuel + 1) % nombreMaxJoueurs;
}

bool Partie::estPartieTerminee() const {

    return false;
}

void Partie::afficherGagnant() const {

    int score = 0;
    for (size_t i = 0; i < nombreMaxJoueurs; ++i) {
        if (joueurs[i].getScore() > score)
        {
            score = joueurs[i].getScore();
        }
    }

    for (size_t i = 0; i < nombreMaxJoueurs; ++i) {
        if (joueurs[i].getScore() == score)
        {
            std::cout << "Le gagnant est : " << joueurs[i].getNom() << std::endl;
        }
    }
}


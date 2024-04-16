#include "joueur.h"
#include "carre.h"
#include "chance.h"
#include "full.h"
#include "grande.h"
#include "petite.h"
#include "yahtzee.h"
#include "Somme.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <iostream>
Joueur::Joueur(const std::string& nom) : nom(nom), score(0),bonusYams(0) {

    figures.push_back(std::make_unique<Somme<1>>());
    figures.push_back(std::make_unique<Somme<2>>());
    figures.push_back(std::make_unique<Somme<3>>());
    figures.push_back(std::make_unique<Somme<4>>());
    figures.push_back(std::make_unique<Somme<5>>());
    figures.push_back(std::make_unique<Somme<6>>());
    figures.push_back(std::make_unique<Brelan<int>>());
    figures.push_back(std::make_unique<Carre<int>>());
    figures.push_back(std::make_unique<Full<int>>());
    figures.push_back(std::make_unique<Petite<int>>());
    figures.push_back(std::make_unique<Grande<int>>());
    figures.push_back(std::make_unique<Chance<int>>());
    figures.push_back(std::make_unique<Yahtzee<int>>());
}

void Joueur::setScore(int s){
    score=s;
}
void Joueur::setNom(std::string n){
    nom=n;
}
void Joueur::chargerFigure(std::string nomFig,int scoreFig, bool marqueFig) {
    if(nomFig=="One"){
        figures.push_back(std::make_unique<Somme<1>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Two"){
        figures.push_back(std::make_unique<Somme<2>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Three"){
        figures.push_back(std::make_unique<Somme<3>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Four"){
        figures.push_back(std::make_unique<Somme<4>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Five"){
        figures.push_back(std::make_unique<Somme<5>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Six"){
        figures.push_back(std::make_unique<Somme<6>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Brelan"){
        figures.push_back(std::make_unique<Brelan<int>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Carre"){
        figures.push_back(std::make_unique<Carre<int>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Full"){
        figures.push_back(std::make_unique<Full<int>>(scoreFig,marqueFig));
    }
    else if(nomFig=="PetiteSuite"){
        figures.push_back(std::make_unique<Petite<int>>(scoreFig,marqueFig));
    }
    else if(nomFig=="GrandeSuite"){
        figures.push_back(std::make_unique<Grande<int>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Chance"){
        figures.push_back(std::make_unique<Chance<int>>(scoreFig,marqueFig));
    }
    else if(nomFig=="Yahtzee"){
        figures.push_back(std::make_unique<Yahtzee<int>>(scoreFig,marqueFig));
    }
}

Joueur::Joueur(const std::string& nom, int sc) : nom(nom), score(sc), bonusYams(0) {
}


void Joueur::jouerTourFacile(lancer& lancer) {
    afficherFeuilleScore();
    std::cout << nom << ", c'est a vous de jouer !" << std::endl;
    lancer.lancerDes();
    const std::vector<int>& resultatsDes = lancer.getResultatsDes();
    std::cout << "Resultats du lancer : ";
    for (int resultat : resultatsDes) {
        std::cout << resultat << " ";
    }
    std::cout << std::endl;


    std::cout << "Categories possibles : " << std::endl;
    int i = 0;
    for (const auto& figure : figures) { // on a utilisé auto parce que figure est un type complexe car c'est un pointeur vers un un membre d'une classe
        i++;
        std::cout << i << " --- ";
        figure->afficherResultat();
        if (!figure->marque)
            std::cout << " -> " << figure->calculerPoints(resultatsDes);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int relance = 0; relance < 2; ++relance) {
        char relancer;
        do {
            std::cout << "Voulez-vous relancer des des ? (o/n) : ";
            std::cin >> relancer;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (relancer != 'o' && relancer != 'O' && relancer != 'n' && relancer != 'N');
            if (relancer == 'o' || relancer == 'O') {
                relancerDes(lancer);
                i = 0;
                for (const auto& figure : figures) {
                    i++;
                    std::cout << i << " --- ";
                    figure->afficherResultat();
                    if (!figure->marque)
                        std::cout << " -> " << figure->calculerPoints(resultatsDes);
                    std::cout << std::endl;
                }
            }
            else {
                break;
            }
    }
    isYams(resultatsDes);
    int choix = 0;
    int testchoix = 0;
    do {


        std::cout << "Choisissez une categorie (1, 2, 3, ...) : ";
        std::cin >> choix;


        if (choix >= 1 && choix <= static_cast<int>(figures.size())) {

            std::unique_ptr<figure>& categorieChoisie = figures[choix - 1];


            if (categorieChoisie && !categorieChoisie->marque) {

                int points = categorieChoisie->calculerPoints(resultatsDes);


                score += points;
                testchoix = 1;

                std::cout << "Vous avez obtenu " << points << " points pour cette categorie !" << std::endl;
                categorieChoisie->sc = points;
                categorieChoisie->marque = true;


            }
            else {
                std::cout << "Cette categorie a deja ete utilisee. Choisissez une autre categorie." << std::endl;
            }
        }
        else {
            std::cout << "Choix invalide. Veuillez choisir une categorie valide." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (testchoix == 0);
}

void Joueur::jouerTourNormal(lancer& lancer) {
    afficherFeuilleScore();
    std::cout << nom << ", c'est a vous de jouer !" << std::endl;
    lancer.lancerDes();
    const std::vector<int>& resultatsDes = lancer.getResultatsDes();
    std::cout << "Resultats du lancer : ";
    for (int resultat : resultatsDes) {
        std::cout << resultat << " ";
    }
    std::cout << std::endl;


    std::cout << "Categories possibles : " << std::endl;
    int i = 0;
    for (const auto& figure : figures) { // on a utilisé auto parce que figure est un type complexe car c'est un pointeur vers un un membre d'une classe
        i++;
        std::cout << i << " --- ";
        figure->afficherResultat();
        if (!figure->marque)
            std::cout << " -> " << figure->calculerPoints(resultatsDes);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int relance = 0; relance < 2; ++relance) {
        char relancer;
        do {
            std::cout << "Voulez-vous relancer des des ? (o/n) : ";
            std::cin >> relancer;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (relancer != 'o' && relancer != 'O' && relancer != 'n' && relancer != 'N');
        if (relancer == 'o' || relancer == 'O') {
            relancerDes(lancer);
            i = 0;
            for (const auto& figure : figures) {
                i++;
                std::cout << i << " --- ";
                figure->afficherResultat();
                if (!figure->marque)
                    std::cout << " -> " << figure->calculerPoints(resultatsDes);
                std::cout << std::endl;
            }
        }
        else {
            break;
        }
    }
    isYams(resultatsDes);
    int choix = 0;
    int testchoix = 0;
    do {
        std::cout << "Choisissez une categorie (1, 2, 3, ...) : ";
        std::cin >> choix;


        if (choix >= 1 && choix <= static_cast<int>(figures.size())) {

            std::unique_ptr<figure>& categorieChoisie = figures[choix - 1];
            if (categorieChoisie->type == 0 && !checkType())
            {
                std::cout << "Il faut d\'abord remplir la partie superieur avant de remplir la partie inferieur" << std::endl;
            }
            else{
                if (categorieChoisie && !categorieChoisie->marque) {

                    int points = categorieChoisie->calculerPoints(resultatsDes);


                    score += points;
                    testchoix = 1;

                    std::cout << "Vous avez obtenu " << points << " points pour cette categorie !" << std::endl;
                    categorieChoisie->sc = points;
                    categorieChoisie->marque = true;


                }
                else {
                    std::cout << "Cette categorie a deja ete utilisee. Choisissez une autre categorie." << std::endl;
                }
            }
        }
        else {
            std::cout << "Choix invalide. Veuillez choisir une categorie valide." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (testchoix == 0);
}

void Joueur::jouerTourDifficile(lancer& lancer) {
    afficherFeuilleScore();
    std::cout << nom << ", c'est a vous de jouer !" << std::endl;
    lancer.lancerDes();
    const std::vector<int>& resultatsDes = lancer.getResultatsDes();
    std::cout << "Resultats du lancer : ";
    for (int resultat : resultatsDes) {
        std::cout << resultat << " ";
    }
    std::cout << std::endl;


    std::cout << "Categorie actuelle : " << std::endl;
    int i = 0;
    for (const auto& figure : figures) { // on a utilisé auto parce que figure est un type complexe car c'est un pointeur vers un un membre d'une classe
        i++;
        if (!figure->marque)
        {
            figure->afficherResultat();
            std::cout << " -> " << figure->calculerPoints(resultatsDes);
            std::cout << std::endl;
            break;
        }
    }
    std::cout << std::endl;
    for (int relance = 0; relance < 2; ++relance) {
        char relancer;
        do {
            std::cout << "Voulez-vous relancer des des ? (o/n) : ";
            std::cin >> relancer;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (relancer != 'o' && relancer != 'O' && relancer != 'n' && relancer != 'N');
        if (relancer == 'o' || relancer == 'O') {
            relancerDes(lancer);
            i = 0;
            for (const auto& figure : figures) {
                i++;
                std::cout << i << " --- ";
                figure->afficherResultat();
                if (!figure->marque)
                    std::cout << " -> " << figure->calculerPoints(resultatsDes);
                std::cout << std::endl;
            }
        }
        else {
            break;
        }
    }
    isYams(resultatsDes);
    addScoreDifficile(resultatsDes);
}

void Joueur::jouerTourHardCore(lancer& lancer, int categorie)
{
    afficherFeuilleScore();
    std::cout << nom << ", c'est a vous de jouer !" << std::endl;
    lancer.lancerDes();
    const std::vector<int>& resultatsDes = lancer.getResultatsDes();
    std::cout << "Resultats du lancer : ";
    for (int resultat : resultatsDes) {
        std::cout << resultat << " ";
    }
    std::cout << std::endl;


    std::cout << "Categorie actuelle : " << std::endl;
    int i = 0;
    for (const auto& figure : figures) { // on a utilisé auto parce que figure est un type complexe car c'est un pointeur vers un un membre d'une classe
        if (i == categorie)
        {
            figure->afficherResultat();
            std::cout << " -> " << figure->calculerPoints(resultatsDes);
            std::cout << std::endl;
            break;
        }
        i++;
    }
    std::cout << std::endl;
    for (int relance = 0; relance < 2; ++relance) {
        char relancer;
        do {
            std::cout << "Voulez-vous relancer des des ? (o/n) : ";
            std::cin >> relancer;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (relancer != 'o' && relancer != 'O' && relancer != 'n' && relancer != 'N');
        if (relancer == 'o' || relancer == 'O') {
            relancerDes(lancer);
            i = 0;
            for (const auto& figure : figures) {
                i++;
                std::cout << i << " --- ";
                figure->afficherResultat();
                if (!figure->marque)
                    std::cout << " -> " << figure->calculerPoints(resultatsDes);
                std::cout << std::endl;
            }
        }
        else {
            break;
        }
    }
    isYams(resultatsDes);
    addScoreHardCore(resultatsDes, categorie);
}


bool Joueur::checkType()
{
    for (size_t i = 0; i < figures.size(); ++i) {
        const std::unique_ptr<figure>& figure = figures[i];
        if (figure) {
            if (figure->type == 1 && figure->marque==0) {
                return false;
            }
        }
    }
    return true;
}

void Joueur::addScoreDifficile(const std::vector<int>& resultatsDes)
{
    int points = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        const std::unique_ptr<figure>& figure = figures[i];
        if (figure) {
            if (figure->marque == 0) {
                points = figure->calculerPoints(resultatsDes);
                score += points;
                figure->marque = 1;
                figure->sc = points;
                break;
            }
        }
    }
}

void Joueur::addScoreHardCore(const std::vector<int>& resultatsDes, int categorie)
{
    int points = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        const std::unique_ptr<figure>& figure = figures[i];
        if (figure) {
            if (i == categorie) {
                points = figure->calculerPoints(resultatsDes);
                score += points;
                figure->marque = 1;
                figure->sc = points;
                break;
            }
        }
    }
}

void Joueur::relancerDes(lancer& lancer) {

    std::vector<bool> desARejouer(5, false);


    for (size_t i = 0; i < 5; ++i) {
        char choix;
        std::cout << "Voulez-vous relancer le de #" << (i + 1) << " ? (o/n) : ";
        std::cin >> choix;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        desARejouer[i] = (choix == 'o' || choix == 'O');
    }


    lancer.relancerDes(desARejouer);


    const std::vector<int>& resultatsDes = lancer.getResultatsDes();
    std::cout << "Nouveaux resultats : ";
    for (int resultat : resultatsDes) {
        std::cout << resultat << " ";
    }
    std::cout << std::endl;
}

void Joueur::checkBonus(){
    int mineur=0;
    for (size_t i = 0; i < figures.size(); ++i) {
        const std::unique_ptr<figure>& figure = figures[i];
        if (figure) {
            if (figure->type==0) {
                mineur += figure->sc;
            }
        }
    }
    if (mineur >= 63)
    {
        score += 35;
        std::cout << "Ton score sur la partie mineur est de " << mineur << " . Bravo tu gagnes un bonus de 35 points ! " << std::endl;
    }
}

void Joueur::isYams(const std::vector<int>& des){

    for (size_t i = 0; i < figures.size(); ++i) {
        const std::unique_ptr<figure>& figure = figures[i];
        if (figure) {
            if (figure->calculerPoints(des) == 50) {
                if (figure->marque == 1)
                {
                    if (figure->sc > 0 && bonusYams==0)
                    {
                        bonusYams = 100;
                        std::cout << "Bravo tu as obtenu un deuxieme yathzee ! Tu as gagne un bonus de 100 points ! " << std::endl;
                        figure->sc +=100;
                        score += 100;
                    }
                }
            }
        }
    }
}

void Joueur::afficherScore() {
    checkBonus();
    std::cout << nom << ", votre score actuel est : " << score << std::endl;
}

void Joueur::enregistrerScorePartiel(std::ofstream& file) {


    for (const auto& figure : figures) {
            file  <<figure->save()<< std::endl;
    }
}

std::string Joueur::getNom() const
{
    return nom;
}

int Joueur::getScore() const
{
    return score;
}

void Joueur::afficherFeuilleScore() const {
    std::cout << "Feuille de score pour " << nom << " : " << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        const std::unique_ptr<figure>& figure = figures[i];
        if (figure) {
            std::cout << i + 1 << ". ";
            figure->afficherResultat();
            std::cout << std::endl;
        }
    }
    std::cout << "Score actuel : " << score << std::endl;
}
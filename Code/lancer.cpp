#include "lancer.h"
#include <cstdlib>
#include <algorithm>
#include <time.h>

lancer::lancer() : resultatsDes(5, 0) {

}

void lancer::lancerDes() {
    srand(time(nullptr));
    for (int& resultat : resultatsDes) {
        resultat = 1 + std::rand() % 6;
    }


    std::sort(resultatsDes.begin(), resultatsDes.end());
}

void lancer::relancerDes(const std::vector<bool>& desARejouer) {
    srand(time(nullptr));
    for (size_t i = 0; i < resultatsDes.size(); ++i) {
        if (desARejouer[i]) {
            resultatsDes[i] = 1 + std::rand() % 6;
        }
    }


    std::sort(resultatsDes.begin(), resultatsDes.end());
}

const std::vector<int>& lancer::getResultatsDes() const {
    return resultatsDes;
}


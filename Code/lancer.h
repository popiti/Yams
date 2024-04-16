#ifndef LANCER_H_INCLUDED
#define LANCER_H_INCLUDED
#include <vector>

class lancer {
private:
    std::vector<int> resultatsDes;

public:
    lancer(); // Constructeur
    void lancerDes();
    void relancerDes(const std::vector<bool>& desARejouer);
    const std::vector<int>& getResultatsDes() const;
};
#endif
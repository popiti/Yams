#include "figure.h"
template <typename T> class Chance : public figure {
public:
    Chance(int s, bool m);
    Chance();
    int calculerPoints(const std::vector<T>& des) const override;
    void afficherResultat() const override;
    std::string save() const override;
};
template<typename T>
Chance<T>::Chance(){
    sc=0;
    marque=0;
    type = 1;
}
template<typename T>
Chance<T>::Chance(int s, bool m){
    sc=s;
    marque=m;
    type = 1;
}
template<typename T>
int Chance<T>::calculerPoints(const std::vector<T>& des) const {

    int somme = 0;
    for (int valeur : des) {
        somme += valeur;
    }
    return somme;
}

template<typename T>
void Chance<T>::afficherResultat() const {
    std::cout << "Chance : " << sc;
}
template<typename T>
std::string Chance<T>::save() const {

    std::string txt= "Chance="+std::to_string(sc);
    txt+="="+std::to_string(marque);
    return txt;
}

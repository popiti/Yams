#include "figure.h"
template<typename T> class Yahtzee : public figure {
public:
    Yahtzee(int s, bool m);
    Yahtzee();
    int calculerPoints(const std::vector<T>& des) const override;
    void afficherResultat() const override;
    std::string save() const override;
};
template<typename T>
Yahtzee<T>::Yahtzee(){
    sc=0;
    marque=0;
    type = 1;
}
template<typename T>
Yahtzee<T>::Yahtzee(int s, bool m){
    sc=s;
    marque=m;
    type = 1;
}
template<typename T>
int Yahtzee<T>::calculerPoints(const std::vector<T>& des) const {

    for (int valeur : des) {
        if (std::count(des.begin(), des.end(), valeur) == 5) {

            return 50;
        }
    }
    return 0;
}

template<typename T>
void Yahtzee<T>::afficherResultat() const {
    std::cout << "Yahtzee : " << sc;
}
template<typename T>
std::string Yahtzee<T>::save() const {

    std::string txt= "Yahtzee="+std::to_string(sc);
    txt+="="+std::to_string(marque);
    return txt;
}

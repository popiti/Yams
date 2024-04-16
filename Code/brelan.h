#include "figure.h"

template <typename T> class Brelan : public figure {
public:
    Brelan(int s, bool m);
    Brelan();
    int calculerPoints(const std::vector<T>& des) const override;
    void afficherResultat() const override;
    int getBrelan(const std::vector<T>& des) const;
    std::string save() const override;
};
template<typename T>
Brelan<T>::Brelan(){
    sc=0;
    marque=0;
    type = 1;
}
template<typename T>
Brelan<T>::Brelan(int s, bool m){
    sc=s;
    marque=m;
    type = 1;
}
template<typename T>
int Brelan<T>::calculerPoints(const std::vector<T>& des) const {

    std::vector<int> desTries = des;
    std::sort(desTries.begin(), desTries.end());


    for (size_t i = 0; i <= desTries.size() - 3; ++i) {
        if (desTries[i] == desTries[i + 1] && desTries[i] == desTries[i + 2]) {

            return 3 * desTries[i];
        }
    }


    return 0;
}

template<typename T>
void Brelan<T>::afficherResultat() const {
    std::cout << "Brelan : " << sc;
}

template<typename T>
int Brelan<T>::getBrelan(const std::vector<T>& des) const {

    std::vector<int> desTries = des;
    std::sort(desTries.begin(), desTries.end());


    for (size_t i = 0; i <= desTries.size() - 3; ++i) {
        if (desTries[i] == desTries[i + 1] && desTries[i] == desTries[i + 2]) {

            return desTries[i];
        }
    }
    return 0;
}
template<typename T>
std::string Brelan<T>::save() const {

    std::string txt= "Brelan="+std::to_string(sc);
    txt+="="+std::to_string(marque);
    return txt;
}

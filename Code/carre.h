#include "figure.h"

template<typename T> class Carre : public figure {
public:
    Carre(int s, bool m);
    Carre();
     int calculerPoints(const std::vector<int>& des) const override;
     void afficherResultat() const override;
     std::string save() const override;
};
template<typename T>
Carre<T>::Carre(){
    sc=0;
    marque=0;
    type = 1;
}

template<typename T>
Carre<T>::Carre(int s, bool m){
    sc=s;
    marque=m;
    type = 1;
}
template<typename T>
int Carre<T>::calculerPoints(const std::vector<int>& des) const {

    std::vector<int> desTries = des;
    std::sort(desTries.begin(), desTries.end());


    for (size_t i = 0; i <= desTries.size() - 4; ++i) {
        if (desTries[i] == desTries[i + 1] && desTries[i] == desTries[i + 2] && desTries[i] == desTries[i + 3]) {

            return 4 * desTries[i];
        }
    }
    return 0;
}

template<typename T>
void Carre<T>::afficherResultat() const {
    std::cout << "Carre : " << sc;
}
template<typename T>
std::string Carre<T>::save() const {

    std::string txt= "Carre="+std::to_string(sc);
    txt+="="+std::to_string(marque);
    return txt;
}

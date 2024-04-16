#include "figure.h"
template<typename T> class Petite : public figure {
public:
    Petite(int s, bool m);
    Petite();
    int calculerPoints(const std::vector<T>& des) const override;
    void afficherResultat() const override;
    std::string save() const override;
};
template<typename T>
Petite<T>::Petite(){
    sc=0;
    marque=0;
    type = 1;
}
template<typename T>
Petite<T>::Petite(int s, bool m){
    sc=s;
    marque=m;
    type = 1;
}
template<typename T>
int Petite<T>::calculerPoints(const std::vector<T>& des) const {

    std::vector<int> desTries = des;
    std::sort(desTries.begin(), desTries.end());
    std::vector<int> suite1{1, 2, 3, 4 };
    std::vector<int> suite2{2, 3, 4, 5 };
    std::vector<int> suite3{3, 4, 5, 6 };
    bool isSuite1 = std::includes(desTries.begin(), desTries.end(), suite1.begin(), suite1.end());
    bool isSuite2 = std::includes(desTries.begin(), desTries.end(), suite2.begin(), suite2.end());
    bool isSuite3 = std::includes(desTries.begin(), desTries.end(), suite3.begin(), suite3.end());
    if (isSuite1 || isSuite2 || isSuite3){
          return 30;
     }
    else {
        return 0;
    }
}

template<typename T>
void Petite<T>::afficherResultat() const {
    std::cout << "Petite Suite : " << sc;
}
template<typename T>
std::string Petite<T>::save() const {

    std::string txt= "PetiteSuite="+std::to_string(sc);
    txt+="="+std::to_string(marque);
    return txt;
}
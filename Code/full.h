#include "figure.h"
#include "brelan.h"
#include "paire.h"

template<typename T> class Full : public figure {
public:
    Full(int s, bool m);
    Full();
    int calculerPoints(const std::vector<T>& des) const override;
    void afficherResultat() const override;
    std::string save() const override;
};
template<typename T>
Full<T>::Full(){
    sc=0;
    marque=0;
    type = 1;
}
template<typename T>
Full<T>::Full(int s, bool m){
    sc=s;
    marque=m;
    type = 1;
}
template<typename T>
int Full<T>::calculerPoints(const std::vector<T>& des) const {
    Brelan<T> brelan;
    Paire<T> paire;

    int pointsBrelan = brelan.getBrelan(des);
    int pointsPaire = paire.getPair(des,pointsBrelan);
    if (pointsBrelan > 0 && pointsPaire > 0 ) {

        return 25;
    }
    else {

        return 0;
    }
}

template<typename T>
void Full<T>::afficherResultat() const {
    std::cout << "Full : " << sc;
}
template<typename T>
std::string Full<T>::save() const {

    std::string txt= "Full="+std::to_string(sc);
    txt+="="+std::to_string(marque);
    return txt;
}

#include "figure.h"
template<typename T> class Grande : public figure {
public:
    Grande(int s, bool m);
    Grande();
    int calculerPoints(const std::vector<T>& des) const override;
    void afficherResultat() const override;
    std::string save() const override;
};
template<typename T>
Grande<T>::Grande(){
    sc=0;
    marque=0;
    type = 1;
}
template<typename T>
Grande<T>::Grande(int s, bool m){
    sc=s;
    marque=m;
    type = 1;
}
template<typename T>
int Grande<T>::calculerPoints(const std::vector<T>& des) const {

    std::vector<int> desTries = des;
    std::sort(desTries.begin(), desTries.end());
    int cpt = 0;
    for (size_t i = 0; i < desTries.size() - 1; ++i) {
        if (desTries[i] + 1 != desTries[i + 1]) {
            if (desTries[i] != desTries[i + 1])
            {
                return 0;
            }
        }
        else {
            cpt++;
        }
    }
    if (cpt == 4)
    {
        return 40;
    }
    else {
        return 0;
    }
}

template<typename T>
void Grande<T>::afficherResultat() const {
    std::cout << "Grande Suite : " << sc;
}
template<typename T>
std::string Grande<T>::save() const {

    std::string txt= "GrandeSuite="+std::to_string(sc);
    txt+="="+std::to_string(marque);
    return txt;
}

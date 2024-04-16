#include "figure.h"

template<typename T> class Paire : public figure {
public:
    int calculerPoints(const std::vector<T>& des) const override;
    void afficherResultat() const override;
    int getPair(const std::vector<T>& des, int brelan) const ;
    std::string save() const override;
};

template<typename T>
int Paire<T>::calculerPoints(const std::vector<T>& des) const {

    std::vector<int> desTries = des;
    std::sort(desTries.begin(), desTries.end());


    for (size_t i = 0; i <= desTries.size() - 2; ++i) {
        if (desTries[i] == desTries[i + 1]) {

            return 2 * desTries[i];
        }
    }


    return 0;
}

template<typename T>
void Paire<T>::afficherResultat() const {
    std::cout << "Paire : " << sc;
}

template<typename T>
int Paire<T>::getPair(const std::vector<T>& des,int brelan) const {

    std::vector<int> desTries = des;
    std::sort(desTries.begin(), desTries.end());


    for (size_t i = 0; i <= desTries.size() - 2; ++i) {
        if (desTries[i] == desTries[i + 1] && desTries[i] != brelan) {

            return 2 * desTries[i];
        }
    }
    return 0;
}

template<typename T>
std::string Paire<T>::save() const {
    return "";
}

#ifndef FIG_H_INCLUDED
#define FIG_H_INCLUDED
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

class figure {
public:
    int sc;
    bool marque = false;
    int type;
    virtual int calculerPoints(const std::vector<int>& des) const = 0;
    virtual void afficherResultat() const = 0;
    virtual std::string save() const = 0;
};

#endif

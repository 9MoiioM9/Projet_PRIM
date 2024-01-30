//
// Created by Documents on 29/01/2024.
//

#ifndef PROJET_PRIM_ARBRERECOUVR_H
#define PROJET_PRIM_ARBRERECOUVR_H


class ArbreRecouvr {
private:
    int numSommet;
    ArbreRecouvr *fils;
    ArbreRecouvr *voisin;

public:
    ArbreRecouvr();
    ArbreRecouvr(int numSommet);
    void setSommet(int s);
    void addFils(ArbreRecouvr *fils);
    void addVoisin(ArbreRecouvr *voisin);

    int getNumSommet() const;

    ArbreRecouvr *getFils() const;

    ArbreRecouvr *getVoisin() const;
};


#endif //PROJET_PRIM_ARBRERECOUVR_H

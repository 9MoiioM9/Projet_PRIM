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
    ArbreRecouvr(int numSommet);
    void addFils(ArbreRecouvr *fils);
    void addVoisin(ArbreRecouvr *voisin);
};


#endif //PROJET_PRIM_ARBRERECOUVR_H

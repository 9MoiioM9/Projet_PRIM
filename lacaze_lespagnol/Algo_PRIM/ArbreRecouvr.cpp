//
// Created by Documents on 29/01/2024.
//

#include "ArbreRecouvr.h"

ArbreRecouvr::ArbreRecouvr(int numSommet) : numSommet(numSommet), fils(nullptr), voisin(nullptr){

}

void ArbreRecouvr::addFils(ArbreRecouvr *fils) {
    if (this->fils == nullptr){
        this->fils = fils;
    }
    else{
        this->fils->addVoisin(fils);
    }
}

void ArbreRecouvr::addVoisin(ArbreRecouvr *voisin) {
    if(this->voisin == nullptr){
        this->voisin = voisin;
    }
    else{
        this->voisin->addVoisin(voisin);
    }
}

void ArbreRecouvr::setSommet(int s) {
    this->numSommet = s;
}

ArbreRecouvr::ArbreRecouvr() : numSommet(0),fils(nullptr), voisin(nullptr){

}


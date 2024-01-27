//
// Created by Moi on 27/01/2024.
//

#include "Sommet.h"

//Partie concernant la classe Couple
int Sommet::Couple::getAdjacent() const {
    return adjacent;
}

int Sommet::Couple::getCost() const {
    return cost;
}

Sommet::Couple Sommet::Couple::getNext() const {
    return *next;
}

void Sommet::Couple::addNext(int &ajd, int &c) {
    //TODO pb de pointeur
    if(isNull()){
        *next = Couple(ajd, c);
    }else{
        Couple *tmp = next;
        while(!tmp->isNull()){
            tmp = tmp->next;
        }
        //On arrive à la fin donc tmp == nullptr
        *tmp = Couple(ajd, c);
    }
}

bool Sommet::Couple::isNull() {
    return this->next;
}

Sommet::Couple::~Couple() {
    while(!next->isNull()){
        Couple *tmp = next;
        next = next->next;
        tmp->next = nullptr;
        delete tmp;
    }
}

//==========================================================

//Partie concernant la classe Sommet
int Sommet::getNumero() const {
    return numero;
}

Sommet::Couple Sommet::getVoisins() const {
    return *voisins;
}

bool Sommet::isEnd() const {
    return voisins;
}

Sommet::~Sommet() {
    delete voisins;
}

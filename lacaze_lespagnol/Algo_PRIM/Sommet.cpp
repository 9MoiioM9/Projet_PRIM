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

void Sommet::Couple::addNext(int &adj, int &c) {
    if(next == nullptr){
        next = new Couple(adj, c);
    }else{
        next->addNext(adj, c);
    }
}

Sommet::Couple::~Couple() {
    delete next;
}

//==========================================================

//Partie concernant la classe Sommet
int Sommet::getNumero() const {
    return numero;
}

Sommet::Couple Sommet::getVoisins() const {
    return *voisins;
}

Sommet::~Sommet() {
    delete voisins;
}

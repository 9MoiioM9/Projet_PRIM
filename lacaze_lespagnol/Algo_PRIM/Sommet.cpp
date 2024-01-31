//
// Created by Moi on 27/01/2024.
//

#include "Sommet.h"

//Partie concernant la classe Couple
Sommet* Sommet::Couple::getAdjacent() const {
    return adjacent;
}

int Sommet::Couple::getCost() const {
    return cost;
}

Sommet::Couple& Sommet::Couple::getNext() {
    return *next;
}

void Sommet::Couple::addSommet(Sommet *adj, int c) {
    if(next == nullptr){
        next = new Couple(adj, c);
    }else{
        next->addSommet(adj, c);
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

Sommet::Couple& Sommet::getVoisins() {
    return *voisins;
}

void Sommet::setNumero(int num) {
    this->numero = num;
}

Sommet::~Sommet() {
    delete voisins;
}

void Sommet::addVoisin(Sommet *s, int cost) {
    if(this->voisins == nullptr){
        this->voisins = new Couple(s,cost);
    }
    else{
        this->getVoisins().addSommet(s,cost);
    }
}

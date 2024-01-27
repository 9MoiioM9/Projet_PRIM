//
// Created by Moi on 27/01/2024.
//

#include "PrimM.h"

PrimM::Matrice::Matrice(int nbSommet) : nbSommet(nbSommet){
    this->matrice = new int[nbSommet*nbSommet];
    for (int i = 0; i < nbSommet*nbSommet; ++i) {
        matrice[i]=0;
    }
}

int PrimM::Matrice::get(int sommet1, int sommet2) {
    return this->matrice[(sommet1-1)+ nbSommet*(sommet2-1)];
}

int PrimM::Matrice::set(int sommet1, int sommet2, int value) {
    matrice[(sommet1-1)+ nbSommet*(sommet2-1)] = value;
    matrice[(sommet2-1)+ nbSommet*(sommet1-1)] = value;
}


PrimM::PrimM(std::string input, int sommet) : sommet(sommet), nbSommet(0), afficheEcran(true), output(
        nullptr){
    this->input = new std::ifstream();
    this->input->open(input);
    this->enregistrerMatrice();
}



PrimM::PrimM(std::string input, int sommet, std::string output) : sommet(sommet), nbSommet(0), afficheEcran(false){
    this->input = new std::ifstream(input);
    this->input->open(input);
    this->output = new std::ofstream(output);
    this->output->open(output);
    this->enregistrerMatrice();
}

void PrimM::enregistrerMatrice() {
    char* nombre;
    input->getline(nombre,INT_MAX,' ');
    this->nbSommet = std::stoi(nombre);
    matriceAdjacence = new Matrice(nbSommet);

    //TODO remplir la matrice
}




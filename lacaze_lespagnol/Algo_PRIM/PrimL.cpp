//
// Created by Moi on 27/01/2024.
//

#include "PrimL.h"
#include <iostream>

PrimL::PrimL(std::string input, int sommet)
: sommet(sommet), nb_sommet(0), afficheEcran(false), output(nullptr){
    this->input = new std::ifstream();
    this->input->open(input);
    this->enregistrerListeAdjacence();
}

PrimL::PrimL(std::string input, int sommet, std::string output)
: sommet(sommet), nb_sommet(0), afficheEcran(false) {
    this->input = new std::ifstream(input);
    this->input->open(input);
    this->output = new std::ofstream(output);
    this->output->open(output);
    this->enregistrerListeAdjacence();
}

void PrimL::addTwoSommets(int s1, int s2, int cost) {
    liste_ajacentes[s1 -1].getVoisins().addSommet(&liste_ajacentes[s2-1], cost);
    liste_ajacentes[s2 -1].getVoisins().addSommet(&liste_ajacentes[s1-1], cost);
}

void PrimL::enregistrerListeAdjacence() {
    char* nb;
    input->getline(nb, INT_MAX, ' ');
    this->nb_sommet = std::stoi(nb);
    liste_ajacentes = new Sommet(nb_sommet);

    liste_ajacentes = new Sommet[nb_sommet];

    for(int i=0; i<nb_sommet; i++){
        liste_ajacentes[i].setNumero(i+1);
    }

    for(int i = 0; i<nb_sommet; i++){
        input->getline(nb, INT_MAX, ' ');
        while(true){
            input->getline(nb, INT_MAX, ' ');
            if(*nb == '0'){
                break;
            }else {
                int s = std::stoi(nb);
                input->getline(nb, INT_MAX, ' ');
                int cost = std::stoi(nb);
                this->addTwoSommets(i+1, s, cost);
            }
        }
    }
    this->input->close();
    this->afficherResult();
}

bool PrimL::isConnexe() {
    return false;
}

void PrimL::afficherResult() {

}


//
// Created by Moi on 27/01/2024.
//

#include <iostream>
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

    //remplir la matrice
    for (int i = 0; i < nbSommet; ++i) {
        input->getline(nombre,INT_MAX,' ');
        while(true){
            input->getline(nombre,INT_MAX,' ');
            if (*nombre == '0'){
                break;
            }
            else{
                int sommet = std::stoi(nombre);
                input->getline(nombre,INT_MAX,' ');
                int poids = std::stoi(nombre);
                this->matriceAdjacence->set(i+1,sommet,poids);
            }
        }
    }
    this->input->close();
    this->afficherResult();
}

void PrimM::afficherResult() {
    if (this->afficheEcran){
        if(this->isConnexe()){
            std::cout << "le graphe est connexe" << std::endl;
        }else{
            std::cout << "le graphe n'est pas connexe" << std::endl;
        }
        ///TODO faire arbre recouvrant, afficher cout arbre + chaque sommet
    }else{
        ///TODO same mais avec this->output
    }
}

void PrimM::isConnexe_Aux(int sommet,bool *connex) {

    for (int i = 0; i < nbSommet; ++i) {
        if(matriceAdjacence->get(sommet,i+1)!=0){
            if(!connex[i]){
                connex[i] = true;
                isConnexe_Aux(i+1,connex);
            }
        }
    }
}

bool PrimM::isConnexe() {
    bool connex[nbSommet];
    for (int i = 0; i < nbSommet; ++i) {
        connex[i]=false;
    }
    isConnexe_Aux(sommet,connex);

    bool found = false;
    for (int i = 0; i < nbSommet; ++i) {
        if(!connex[i]){
            found = true;
        }
    }
    return !found;
}


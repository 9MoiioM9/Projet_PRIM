//
// Created by Moi on 27/01/2024.
//

#include <iostream>
#include "PrimM.h"
#include "ArbreRecouvr.h"

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
            ArbreRecouvr arbre = algoPrim();
            std::cout<< "le cout de l'arbre est " << this->calculeCout(&arbre)<<std::endl;

        }else{
            std::cout << "le graphe n'est pas connexe" << std::endl;
            std::cout << "l'algorithme de Prim ne peux être réaliser" << std::endl;
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
    connex[sommet-1] = true;
    isConnexe_Aux(sommet,connex);

    bool found = false;
    for (int i = 0; i < nbSommet; ++i) {
        if(!connex[i]){
            found = true;
        }
    }
    return !found;
}

ArbreRecouvr PrimM::algoPrim() {
    ArbreRecouvr arbres[nbSommet];
    bool tabUsed[nbSommet];
    for (int i = 0; i < nbSommet; ++i) {
        arbres[i].setSommet(i+1);
        tabUsed[i] = false;
    }
    tabUsed[sommet-1] = true;


    algoPrim_Aux(tabUsed,arbres);

    return arbres[sommet-1];
}

void PrimM::algoPrim_Aux(bool *listeUsed, ArbreRecouvr *listeAll) {
    int min = INT_MAX;
    int sommetDep = 0;
    int sommetArrive=0;
    //recherche arete
    for (int i = 0; i < nbSommet; ++i) {
        if(listeUsed[i] == true){
            for (int j = 0; j < nbSommet; ++j) {
                int cout = matriceAdjacence->get(i+1,j+1);
                if(cout>0 && !listeUsed[j]){
                    if(cout < min){
                        min = cout;
                        sommetDep = i+1;
                        sommetArrive = j+1;
                    }
                }
            }
        }
    }
    //assignation nouvelle aréte
    if (sommetDep!=0 && sommetArrive!=0){
        listeAll[sommetDep-1].addFils(&listeAll[sommetArrive-1]);
        listeUsed[sommetArrive-1] = true;
    }

    //continuation ou aréte
    bool found=false;
    for (int i = 0; i < nbSommet; ++i) {
        if(listeUsed[i] == false){
            found = true;
            break;
        }
    }

    if(found){
        algoPrim_Aux(listeUsed,listeAll);
    }
}

int PrimM::calculeCout(ArbreRecouvr *arbre) {
    int acc=0;
    int sommetCourant = arbre->getNumSommet();
    ArbreRecouvr *voisin=arbre->getFils();
    while(voisin != nullptr){
        acc +=matriceAdjacence->get(sommetCourant,voisin->getNumSommet());
        acc+= calculeCout(voisin);
        voisin = voisin->getVoisin();
    }
    return acc;
}


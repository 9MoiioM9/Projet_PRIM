//
// Created by Moi on 27/01/2024.
//

#include <iostream>
#include <chrono>
#include "PrimM.h"
#include "ArbreRecouvr.h"

using namespace std::literals;

PrimM::Matrice::Matrice(int nbSommet) : nbSommet(nbSommet){
    this->matrice = new int[nbSommet*nbSommet];
    for (int i = 0; i < nbSommet*nbSommet; ++i) {
        matrice[i]=0;
    }
}

int PrimM::Matrice::get(int sommet1, int sommet2) {
    return this->matrice[(sommet1-1)+ nbSommet*(sommet2-1)];
}

void PrimM::Matrice::set(int sommet1, int sommet2, int value) {
    matrice[(sommet1-1)+ nbSommet*(sommet2-1)] = value;
    matrice[(sommet2-1)+ nbSommet*(sommet1-1)] = value;
}


PrimM::PrimM(std::string input, int sommet) : sommet(sommet), nbSommet(0), afficheEcran(true), output(
        nullptr){
    this->input = new std::ifstream();
    this->input->open(input);
    if(!this->input->is_open()){
        std::cout << "erreur a l'ouverture du fichier" << std::endl;
        return;
    }
    this->enregistrerMatrice();
}



PrimM::PrimM(std::string input, int sommet, std::string outputS) : sommet(sommet), nbSommet(0), afficheEcran(false){
    this->input = new std::ifstream();
    this->input->open(input);
    if(!this->input->is_open() && !this->output->is_open()){
        std::cout << "erreur a l'ouverture du fichier" << std::endl;
        return;
    }
    this->output = new std::ofstream();
    this->output->open(outputS);
    if(!this->input->is_open() && !this->output->is_open()){
        std::cout << "erreur a l'ouverture du fichier" << std::endl;
        return;
    }
    this->enregistrerMatrice();
}

void PrimM::enregistrerMatrice() {
    char* nombre;
    *input >> nombre;
    char *ptr;
    this->nbSommet = strtol(nombre,&ptr,10);
    matriceAdjacence = new Matrice(nbSommet);

    //remplir la matrice
    for (int i = 0; i < nbSommet; ++i) {
        *input >> nombre;
        while(true){
            *input >> nombre;
            if (*nombre == '0'){
                break;
            }
            else{
                int sommet = std::stoi(nombre);
                *input >> nombre;
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
            std::cout << "LE GRAPHE EST CONNEXE" << std::endl;
            std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
            ArbreRecouvr arbre = algoPrim();
            std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
            std::cout<< "le cout de l'arbre est " << this->totalCost<<std::endl;
            afficheArbre(&arbre);
            std::cout<< "Temps de l'algorithme de Prim :" << (end - start) / 1ms << " ms" <<std::endl;
        }else{
            std::cout << "LE GRAPH N'EST PAS CONNEXE" << std::endl;
            std::cout << "l'algorithme de Prim ne peux être réaliser" << std::endl;
        }
    }else{
        if(this->isConnexe()){
            *output << "LE GRAPHE EST CONNEXE" <<std::endl;
            std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
            ArbreRecouvr arbre = algoPrim();
            std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
            *output << "le cout de l'arbre est " + std::to_string(this->totalCost) <<std::endl;
            afficheArbre(&arbre,true);
            *output << "Temps de l'algorithme de Prim :" + std::to_string((end - start) / 1ms)+" ms" <<std::endl;
        }else{
            *output << "LE GRAPH N'EST PAS CONNEXE"<<std::endl;
            *output << "l'algorithme de Prim ne peux être réaliser"<<std::endl;
        }
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
    arbres = new ArbreRecouvr[this->nbSommet];
    bool tabUsed[this->nbSommet];
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
        if(listeUsed[i]){
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
        totalCost += min;
    }

    //continuation ou aréte
    bool found=false;
    for (int i = 0; i < nbSommet; ++i) {
        if(!listeUsed[i]){
            found = true;
            break;
        }
    }

    if(found){
        algoPrim_Aux(listeUsed,listeAll);
    }
}

void PrimM::afficheArbre(ArbreRecouvr *arbre,bool output) {
    for (int i = 0; i < nbSommet; ++i) {
        if (arbre->getNumSommet() == i+1){
            if(output){
                *this->output <<std::to_string(arbre->getNumSommet()) + " -> _ : _" <<std::endl;
            }
            else{
                std::cout << arbre->getNumSommet() << " -> _ : _"<< std::endl;
            }

        }
        else {
            afficheArbre_Aux(arbre, i + 1);
        }
    }
}

bool PrimM::isFilsde(ArbreRecouvr *pere, int num) {
    bool found = false;
    ArbreRecouvr *fils = pere->getFils();
    while(fils != nullptr){
        if (fils->getNumSommet() == num){
            found = true;
            break;
        }
        fils = fils->getVoisin();
    }
    return found;
}

bool PrimM::afficheArbre_Aux(ArbreRecouvr *arbre,int num){
    if(arbre == nullptr){
        return false;
    }
    if(isFilsde(arbre,num)){
        if(output){
            *this->output << std::to_string(num)+ " -> "+std::to_string(arbre->getNumSommet())+ " : "+std::to_string(matriceAdjacence->get(num,arbre->getNumSommet())) << std::endl;
        }
        else{
            std::cout << num << " -> "<<arbre->getNumSommet()<< " : "<<matriceAdjacence->get(num,arbre->getNumSommet())<< std::endl;
        }
        return true;
    }else{
        bool found =false;
        if(arbre->getFils() == nullptr){
            return false;
        }
        ArbreRecouvr *fils = arbre->getFils();
        while(!found){
            found = afficheArbre_Aux(fils,num);
            if(fils->getVoisin()== nullptr){
                return false;
            }
            fils = fils->getVoisin();
        }
        return true;
    }
}
//
// Created by Moi on 27/01/2024.
//

#include "PrimL.h"
#include <iostream>
#include <chrono>

using namespace std::literals;
PrimL::PrimL(std::string input, int sommet)
: sommet(sommet), nb_sommet(0), afficheEcran(true), output(nullptr){
    this->input = new std::ifstream();
    this->input->open(input);
    if(!this->input->is_open()){
        std::cout << "erreur a l'ouverture du fichier" << std::endl;
        return;
    }
    this->enregistrerListeAdjacence();
}

PrimL::PrimL(std::string input, int sommet, std::string outputS)
: sommet(sommet), nb_sommet(0), afficheEcran(false) {
    this->input = new std::ifstream();
    this->input->open(input);
    if(!this->input->is_open()){
        std::cout << "erreur a l'ouverture du fichier" << std::endl;
        return;
    }
    this->output = new std::ofstream();
    this->output->open(outputS);
    if(!this->input->is_open() && !this->output->is_open()){
        std::cout << "erreur a l'ouverture du fichier" << std::endl;
        return;
    }
    this->enregistrerListeAdjacence();
}

void PrimL::addTwoSommets(int s1, int s2, int cost) {
    liste_ajacentes[s1 -1].addVoisin(&liste_ajacentes[s2-1], cost);
    liste_ajacentes[s2 -1].addVoisin(&liste_ajacentes[s1-1], cost);
}

void PrimL::enregistrerListeAdjacence() {
    char* nb;
    *input >> nb;
    char * ptr;
    this->nb_sommet = strtol(nb,&ptr,10);

    liste_ajacentes = new Sommet[nb_sommet];

    for(int i=0; i<nb_sommet; i++){
        liste_ajacentes[i].setNumero(i+1);
    }

    for(int i = 0; i<nb_sommet; i++){
        *input >> nb;
        while(true){
            *input >> nb;
            std::string nombre =nb;
            if(nombre == "0"){
                break;
            }else {
                int s = std::stoi(nb);
                *input >> nb;
                int cost = std::stoi(nb);
                this->addTwoSommets(i+1, s, cost);
            }
        }
    }
    this->input->close();
    this->afficherResult();
}

void PrimL::isConnexe_Aux(int sommet, bool *connexe) {
    //On récupère le numéro du premier adjacent
    Sommet::Couple *v = &liste_ajacentes[sommet-1].getVoisins();
    while(v!= nullptr && v->getAdjacent() != nullptr){
        if (!connexe[v->getAdjacent()->getNumero() - 1]){
            connexe[v->getAdjacent()->getNumero()-1] = true;
            isConnexe_Aux(v->getAdjacent()->getNumero(), connexe);
        }

        v = &v->getNext();
    }
}

bool PrimL::isConnexe() {
    bool connexe[nb_sommet];
    for (int i = 0; i < nb_sommet; ++i) {
        connexe[i]=false;
    }
    connexe[sommet-1] = true;

    isConnexe_Aux(sommet,connexe);

    bool found = false;
    for (int i = 0; i < nb_sommet; ++i) {
        if(!connexe[i]){
            found = true;
        }
    }
    return !found;
}

void PrimL::afficherResult() {
    if (this->afficheEcran){
        if(this->isConnexe()){
            std::cout << "LE GRAPHE EST CONNEXE" << std::endl;
            std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
            ArbreRecouvr arbre = algoPrim();
            std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
            std::cout<< "le cout de l'arbre est " << this->totalCost <<std::endl;
            afficheArbre(&arbre);
            std::cout<< "Temps de l'algorithme de Prim :" << (end - start) / 1ms << " ms" <<std::endl;
        }else{
            std::cout << "LE GRAPHE N'EST PAS CONNEXE" << std::endl;
            std::cout << "L'algorithme de Prim ne peux être réaliser" << std::endl;
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

void PrimL::algoPrim_Aux(bool *listeUsed, ArbreRecouvr *listeAll) {
    int min = INT_MAX;
    int sommetDep = 0;
    int sommetArrive=0;
    //recherche arete
    for (int i = 0; i < nb_sommet; ++i) {
        if(listeUsed[i]){
            Sommet::Couple *tmp = &liste_ajacentes[i].getVoisins();
            while(tmp != nullptr){
                if(!listeUsed[tmp->getAdjacent()->getNumero() - 1]){
                    if(tmp->getCost() < min){
                        min = tmp->getCost();
                        sommetDep = i+1;
                        sommetArrive = tmp->getAdjacent()->getNumero();
                    }
                }
                tmp = &tmp->getNext();
            }
        }
    }

    //assignation nouvelle arete
    if (sommetDep!=0 && sommetArrive!=0){
        listeAll[sommetDep-1].addFils(&listeAll[sommetArrive-1]);
        listeUsed[sommetArrive-1] = true;
        totalCost += min;
    }

    //continuation ou arret
    bool found=false;
    for (int i = 0; i < nb_sommet; ++i) {
        if(!listeUsed[i]){
            found = true;
            break;
        }
    }

    if(found){
        algoPrim_Aux(listeUsed,listeAll);
    }
}

ArbreRecouvr PrimL::algoPrim() {
    arbres = new ArbreRecouvr[this->nb_sommet];
    bool tabUsed[this->nb_sommet];
    for (int i = 0; i < this->nb_sommet; ++i) {
        arbres[i].setSommet(i+1);
        tabUsed[i] = false;
    }
    tabUsed[sommet-1] = true;

    algoPrim_Aux(tabUsed,arbres);

    return arbres[sommet-1];
}

int PrimL::getCostFromTwoSommets(int s1, int s2) {
    Sommet::Couple *tmp = &liste_ajacentes[s1 - 1].getVoisins();
    while(tmp->getAdjacent()->getNumero() != s2){
        tmp = &tmp->getNext();
    }

    return tmp->getCost();
}

bool PrimL::isFils2(ArbreRecouvr *pere, int num) {
    bool found = false;
    if(pere== nullptr)
        return false;
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

void PrimL::afficheArbre(ArbreRecouvr *arbre, bool output) {
    for (int i = 0; i < nb_sommet; ++i) {
        if (arbre->getNumSommet() == i+1){
            if(output){
                *this->output << std::to_string(arbre->getNumSommet()) + " -> _ : _"<<std::endl;
            }
            else{
                std::cout << arbre->getNumSommet() << " -> _ : _"<< std::endl;
            }
        }
        else{
            afficheArbre_Aux(arbre,i+1);
        }
    }
}


bool PrimL::afficheArbre_Aux(ArbreRecouvr *arbre,int num){
    if(arbre == nullptr){
        return false;
    }
    if(isFils2(arbre,num)){
        if(output){
            *this->output << std::to_string(num)+ " -> "+std::to_string(arbre->getNumSommet())+ " : "+std::to_string(getCostFromTwoSommets(num,arbre->getNumSommet()))<<std::endl;
        }
        else{
            std::cout << num << " -> "<<arbre->getNumSommet()<< " : "<<getCostFromTwoSommets(num,arbre->getNumSommet())<< std::endl;
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



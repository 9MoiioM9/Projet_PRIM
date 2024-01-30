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

void PrimL::isConnexe_Aux(int sommet, bool *connexe) {
    //On récupère le numéro du premier adjacent
    Sommet::Couple *v = &liste_ajacentes[sommet-1].getVoisins();
    while(v != nullptr){
        connexe[v->getAdjacent()->getNumero()-1] = true;
        isConnexe_Aux(v->getAdjacent()->getNumero()-1, connexe);
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
            ArbreRecouvr arbre = algoPrim();
            std::cout<< "le cout de l'arbre est " << this->totalCost <<std::endl;
            afficheArbre(&arbre);

        }else{
            std::cout << "LE GRAPHE N'EST PAS CONNEXE" << std::endl;
            std::cout << "L'algorithme de Prim ne peux être réaliser" << std::endl;
        }

    }else{
        ///TODO same mais avec this->output
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
    ArbreRecouvr arbres[this->nb_sommet];
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

void PrimL::afficheArbre(ArbreRecouvr *arbre) {
    for (int i = 0; i < nb_sommet; ++i) {
        if (arbre->getNumSommet() == i+1){
            std::cout << arbre->getNumSommet() << " -> _ : _"<< std::endl;
        }
        else{

            ArbreRecouvr *pere = arbre;
            bool found = false;
            ArbreRecouvr *grandPere = arbre;
            while(true){
                found = isFils2(pere,i+1);
                if (found){
                    std::cout << i+1 << " -> "<<pere->getNumSommet()<< " : "<<getCostFromTwoSommets(i+1,pere->getNumSommet())<< std::endl;
                    break;
                }
                //Cas de la premiere iteration
                if(pere->getNumSommet() == grandPere->getNumSommet()){
                    pere = pere->getFils();
                }

                //Cas suivants
                if(pere->getVoisin() == nullptr){
                    if(grandPere->getVoisin() == nullptr){
                        pere = grandPere->getFils()->getFils();
                        grandPere = grandPere->getFils();
                    }else{
                        pere = grandPere->getVoisin()->getFils();
                        grandPere = grandPere->getVoisin();
                    }
                }
                else{
                    pere = pere->getVoisin();
                }
            }
        }
    }
}





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

void PrimM::Matrice::set(int sommet1, int sommet2, int value) {
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
            std::cout << "LE GRAPHE EST CONNEXE" << std::endl;
            ArbreRecouvr arbre = algoPrim();
            std::cout<< "le cout de l'arbre est " << this->calculeCout(&arbre)<<std::endl;
            afficheArbre(&arbre);
        }else{
            std::cout << "LE GRAPH N'EST PAS CONNEXE" << std::endl;
            std::cout << "l'algorithme de Prim ne peux être réaliser" << std::endl;
        }
    }else{
        if(this->isConnexe()){
            output->write("LE GRAPHE EST CONNEXE\n",23);
            ArbreRecouvr arbre = algoPrim();
            output->write(("le cout de l'arbre est " + std::to_string(this->calculeCout(&arbre))+"\n").c_str(),25+(this->calculeCout(&arbre)/10));
            afficheArbre(&arbre,true);
        }else{
            output->write("LE GRAPH N'EST PAS CONNEXE\n",27);
            output->write("l'algorithme de Prim ne peux être réaliser\n",44);
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

void PrimM::afficheArbre(ArbreRecouvr *arbre,bool output) {
    for (int i = 0; i < nbSommet; ++i) {
        if (arbre->getNumSommet() == i+1){
            if(output){
                this->output->write((std::to_string(arbre->getNumSommet()) + " -> _ : _\n").c_str(),arbre->getNumSommet()/10 + 11);
            }
            else{
                std::cout << arbre->getNumSommet() << " -> _ : _"<< std::endl;
            }

        }
        else{

            ArbreRecouvr *pere = arbre;
            bool found = isFilsde(pere,i+1);
            ArbreRecouvr *grandPere = arbre;
            while(true){
                found = isFilsde(pere,i+1);
                if (found){
                    if(output){
                        this->output->write((std::to_string(i+1)+ " -> "+std::to_string(pere->getNumSommet())+ " : "+std::to_string(matriceAdjacence->get(i+1,pere->getNumSommet()))+"\n").c_str(),(i+1)/10 + pere->getNumSommet()/10 + matriceAdjacence->get(i+1,pere->getNumSommet())/10 +9);
                    }
                    else{
                        std::cout << i+1 << " -> "<<pere->getNumSommet()<< " : "<<matriceAdjacence->get(i+1,pere->getNumSommet())<< std::endl;
                    }
                    break;
                }
                //premiére itération
                if(pere->getNumSommet() == grandPere->getNumSommet()){
                    pere = pere->getFils();
                }

                //suite
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


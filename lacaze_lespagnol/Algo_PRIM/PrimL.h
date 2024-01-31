//
// Created by Moi on 27/01/2024.
//

#ifndef LACAZE_LESPAGNOL_PRIML_H
#define LACAZE_LESPAGNOL_PRIML_H

#include <string>
#include <fstream>
#include "Sommet.h"
#include "ArbreRecouvr.h"

class PrimL {
private:
    int sommet;
    Sommet *liste_ajacentes;
    int nb_sommet;
    bool afficheEcran;
    std::ofstream* output;
    std::ifstream* input;
    ArbreRecouvr *arbres;

    int totalCost = 0;

    void addTwoSommets(int, int, int);

    void enregistrerListeAdjacence();
    void afficherResult();
    bool isConnexe();
    void isConnexe_Aux(int sommet,bool *connexe);
    ArbreRecouvr algoPrim();
    void algoPrim_Aux(bool *listeUsed,ArbreRecouvr *listeAll);
    int getCostFromTwoSommets(int, int);

    bool isFils2(ArbreRecouvr *, int);
    void afficheArbre(ArbreRecouvr *, bool output = false);
    bool afficheArbre_Aux(ArbreRecouvr *arbre,int num);

public:
    PrimL(std::string input, int sommet);
    PrimL(std::string input, int sommet,std::string output);


};


#endif //LACAZE_LESPAGNOL_PRIML_H

//
// Created by Moi on 27/01/2024.
//

#ifndef LACAZE_LESPAGNOL_PRIML_H
#define LACAZE_LESPAGNOL_PRIML_H

#include <string>
#include <fstream>
#include "Sommet.h"

class PrimL {
private:
    int sommet;
    Sommet *liste_ajacentes;
    int nb_sommet;
    bool afficheEcran;
    std::ofstream* output;
    std::ifstream* input;

    void addTwoSommets(int, int, int);

    void enregistrerListeAdjacence();
    void afficherResult();
    bool isConnexe();
    void isConnexe_Aux(int sommet,bool *connexe);

public:
    PrimL(std::string input, int sommet);
    PrimL(std::string input, int sommet,std::string output);


};


#endif //LACAZE_LESPAGNOL_PRIML_H

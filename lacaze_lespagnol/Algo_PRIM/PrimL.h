//
// Created by Moi on 27/01/2024.
//

#ifndef LACAZE_LESPAGNOL_PRIML_H
#define LACAZE_LESPAGNOL_PRIML_H

#include <string>
#include "Sommet.h"

class PrimL {
private:
    int head;
    Sommet *liste_ajacentes;
    int nb_sommet;
    std::ofstream* output;
    std::ifstream* input;

public:
    //PrimL(std::string input, int sommet);
    //PrimL(std::string input, int sommet,std::string output);


};


#endif //LACAZE_LESPAGNOL_PRIML_H

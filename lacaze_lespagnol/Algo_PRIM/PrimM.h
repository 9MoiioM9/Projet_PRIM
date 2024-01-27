//
// Created by Moi on 27/01/2024.
//

#ifndef LACAZE_LESPAGNOL_PRIMM_H
#define LACAZE_LESPAGNOL_PRIMM_H

#include <string>
#include <fstream>

class PrimM {
private:
    class Matrice{
    private:
        int nbSommet;
        int *matrice;
    public:
        Matrice(int nbSommet);
        int get(int sommet1,int sommet2);
        int set(int sommet1,int sommet2, int value);
    };


    Matrice* matriceAdjacence;
    int sommet;
    bool afficheEcran;
    std::ofstream* output;
    std::ifstream* input;
    int nbSommet;

    void enregistrerMatrice();

public:
    PrimM(std::string input, int sommet);
    PrimM(std::string input, int sommet,std::string output);
};


#endif //LACAZE_LESPAGNOL_PRIMM_H

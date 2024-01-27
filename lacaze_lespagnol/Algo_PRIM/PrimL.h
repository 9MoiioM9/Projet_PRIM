//
// Created by Moi on 27/01/2024.
//

#ifndef LACAZE_LESPAGNOL_PRIML_H
#define LACAZE_LESPAGNOL_PRIML_H


class PrimL {
    struct Sommet {
        int numero;
        struct Couple {
            int adjacent;
            int cost; 
        };

    };

    int head;
    Suite liste_ajacentes;
    const int tail = 0;



};


#endif //LACAZE_LESPAGNOL_PRIML_H

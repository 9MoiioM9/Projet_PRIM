//
// Created by Moi on 27/01/2024.
//

#ifndef LACAZE_LESPAGNOL_SOMMET_H
#define LACAZE_LESPAGNOL_SOMMET_H


class Sommet {
private:
    struct Couple {
        int adjacent;
        int cost;
    };

    int numero;
    Couple *voisin;

public:
    Sommet();

};


#endif //LACAZE_LESPAGNOL_SOMMET_H

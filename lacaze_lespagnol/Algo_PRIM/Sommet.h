//
// Created by Moi on 27/01/2024.
//

#ifndef LACAZE_LESPAGNOL_SOMMET_H
#define LACAZE_LESPAGNOL_SOMMET_H


class Sommet {
private:
    class Couple {
    private:
        int adjacent;
        int cost;
        Couple *next;
    public:
        Couple(int &adj, int &c) : adjacent(adj), cost(c), next(nullptr) {}
        int getAdjacent() const;
        int getCost() const;
        Couple getNext() const;
        void addNext(int &, int &);

        ~Couple();
    };

    int numero;
    Couple *voisins;

public:
    Sommet(int &num) : numero(num), voisins(nullptr) {};
    int getNumero() const;
    Couple getVoisins() const;

    ~Sommet();
};


#endif //LACAZE_LESPAGNOL_SOMMET_H

//
// Created by Moi on 27/01/2024.
//

#ifndef LACAZE_LESPAGNOL_SOMMET_H
#define LACAZE_LESPAGNOL_SOMMET_H


class Sommet {
public:
    class Couple {
    private:
        Sommet *adjacent;
        int cost;
        Couple *next;
    public:
        Couple(Sommet *adj, int &c) : adjacent(adj), cost(c), next(nullptr) {}
        Sommet* getAdjacent() const;
        int getCost() const;
        Couple& getNext();
        void addSommet(Sommet *, int);

        ~Couple();
    };
    Sommet() {};
    Sommet(int num) : numero(num), voisins(nullptr) {};
    int getNumero() const;
    void setNumero(int);
    Couple& getVoisins();

    ~Sommet();

private:

    int numero;
    Couple *voisins;
};


#endif //LACAZE_LESPAGNOL_SOMMET_H

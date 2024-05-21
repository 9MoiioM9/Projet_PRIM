Rapport du Projet PRIM

*Lacaze Yon, Lespagnol Killian*

<a name="_page0_x72.00_y395.18"></a>I – Introduction :

Le projet consiste, à partir d’un arbre couvrant, de programmer un algorithme de PRIM de calcul. Le programme en question est capable de prendre un fichier en argument, pour le calculer, et possiblement un fichier dans lequel on renvoie l’affichage du programme. Pour cela nous verrons les différentes structures que nous avons créées et comment nous les avons utilisées, dans le cadre de ce projet.

[**I – Introduction : 1** ](#_page0_x72.00_y395.18)[II](#_page2_x72.00_y72.00) **[–](#_page2_x72.00_y72.00) [Algorithme](#_page2_x72.00_y72.00) [de](#_page2_x72.00_y72.00) [PRIM](#_page2_x72.00_y72.00) [:](#_page2_x72.00_y72.00) [3**](#_page2_x72.00_y72.00)**

[**III](#_page2_x72.00_y290.12) **[–](#_page2_x72.00_y290.12) [Structures](#_page2_x72.00_y290.12) [utilisées](#_page2_x72.00_y290.12) [:](#_page2_x72.00_y290.12) [3** ](#_page2_x72.00_y290.12)[I – Structure PrimL : 3](#_page2_x72.00_y331.12)**

[II – Structure PrimM : 3 ](#_page2_x72.00_y579.71)[III – Structure ArbreRecouvr : 4](#_page3_x72.00_y72.00)

[**IV – Compilation et exécution: 4** ](#_page3_x72.00_y241.86)[V – Complexité: 4**](#_page3_x72.00_y646.52)

<a name="_page2_x72.00_y72.00"></a>II – Algorithme de PRIM :

Pour commencer un petit point sur l’algorithme que nous avons programmé : l'algorithme de PRIM. Le but de cet algorithme est de prendre un graphe pondéré et non orienté et d’en calculer un arbre couvrant minimal. L’arbre calculé regroupe l’ensemble des sommets du graphe, en prenant les arêtes possédant le plus petit coût. L’arbre possède un poids qui est égal à la somme de tous les poids de toutes les arêtes, il correspond au parcours le plus court du graphe selon les poids des arêtes. Si le graphe initial n’est pas entièrement connexe, l’algorithme identifie et traite une composante connexe à la fois pour trouver un arbre de poids minimum dans cette partie du graphe.

<a name="_page2_x72.00_y290.12"></a>III – Structures utilisées :

<a name="_page2_x72.00_y331.12"></a>I – Structure PrimL :

Pour PrimL nous avons :

● **Classe Sommet** pour représenter un sommet d’un graphe

- **Sous-classe Couple** pour représenter un sommet et son poids. Chaque couple connaît le couple suivant dans la suite. Cette sous classe contient :
  - un pointeur de type Sommet ;
  - un type int pour le poids ;
  - un pointeur de type Couple pour représenter le couple suivant de la suite
- Un type int pour le numéro du sommet ;
- Un pointeur de type Couple pour représenter les voisins du sommet.

Pour faire plus simple, la structure utilise le principe des listes chaînées. Une dans Sommet et une autre dans Couple.

<a name="_page2_x72.00_y579.71"></a>II – Structure PrimM :

- Un objet de type Matrice qui contient un tableau de taille (nbSommet\*nbSommet), pour permettre de représenter la matrice d’adjacence.
- Un objet de type ArbreRecouvr pour y enregistrer l’arbre recouvrant du graph
- Un input et un output pour pouvoir lire et écrire dans les fichier
- Un accumulateur coutTotal pour pouvoir l’enregistrer

<a name="_page3_x72.00_y72.00"></a>III – Structure ArbreRecouvr :

Stratégie : un arbre possède un numéro de sommet (de 1 jusqu'à n Sommet), ainsi que potentiellement un fils et potentiellement un voisin. Cette structure particulière nous permet d’éviter d'utiliser les vectors classiques en les remplaçant par des listes chaînées. Pour pouvoir récupérer tous les fils d’un sommet, il suffit donc de récupérer son fils, puis de se décaler de voisin en voisin, dans ce cas on parcourt tous les fils du sommet de départ “de la gauche vers la droite”.

<a name="_page3_x72.00_y241.86"></a>IV – Compilation et exécution:

Remarque : Nous avons fait le projet en C++ 17 sous l’IDE CLion.

Pour Compiler et exécuter, 2 possibilité:

- Dans le dossier src, lancer la commande make dans un terminal, puis lancer l'exécutable lacaze\_lespagnol.
- Lancer le projet dans Clion, le lier au CMakeLists, le projet pourra être lancée depuis Clion

Argument lors de l'exécution :

- 1er argument : “PrimM” ou “PrimL” selon l’algorithme voulant être utilisé.
- 2éme argument : chemin du fichier contenant les information du graphe comme spécifié dans le sujet.
- 3éme argument : le numéro du sommet de départ.
- 4ème argument(optionnel) : le fichier dans lequel les résultats seront écrits, si celui-ci n’est pas renseigné, l'affichage se fera en console.

<a name="_page3_x72.00_y646.52"></a>V – Complexité:

Concernant la complexité de ce programme qui représente l’algorithme de PRIM, par rapport à notre fonction de calcul nous obtenons une complexité de O(n²), où n correspond au nombre de sommets dans le graphe.

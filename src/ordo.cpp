#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

#include "ordo.h"

/**************************************
Objectif : Constructeur de la classe.
- Lecture du fichier filename
- Initialisation du nombre de noeuds du graphe potentiel-tâches
(incluant les tâches fictives)
- Initialisation des listes d'adjacence "Lpred" et "Lsucc"
- Initialisation du tableau des durées des tâches
- Allocation d'espaces mémoires pour les tableaux plustot, plustard
**************************************/
graphe::graphe(char* filename)
{
    // !!! A FAIRE !!! //
}


/****************************************/
/* Objectif : Affichage du graphe potentiel-tâches
/****************************************/
void graphe::affichage()
{
	cout << "arête : " << "longueur" << endl;
	for(int i = 0; i < Lpred.size(); i++){
		for(int j = 0; j < Lpred[i].size(); j++)
			cout << "(" << i << "," << Lpred[i][j].first << ")" << ": " << Lpred[i][j].second << endl;
	}
}


/**************************************
Objectif : Affichage des résultats de l'ordonnancement
pour toutes les tâches y compris les tâches fictives
**************************************/
void graphe::resultats()
{
	cout << "-------------------------" << endl;
	cout << " Debut \t| " << "+tôt\t| " << "+tard" << "\t|" << endl;
	cout << "-------------------------" << endl;
	for(int i = 0; i < n; i++)
		cout << i << " \t| " << plustot[i] << "\t| " << plustard[i] << "\t|" << endl;
	cout << "-------------------------" << endl;
}


/**************************************
Objectif : Calcul des dates de débuts au plus tôt et 
au plus tard de toutes les tâches du graphe potentiel-tâches
Pour chaque noeud i du graphe potentiel-tâches :
- plustot[i] doit contenir la date de début au plus tot de i
- plustard[i] doit contenir la date de début au plus tard de i
**************************************/
void graphe::ordo()
{
    // !!! A FAIRE !!! //
}

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

#include "ordo.h"

Cmp::Cmp(int* d)
{
    this->d = d;
}

// max heap
bool Cmp::operator()(const int a, const int b)
{
    return this->d[a] < this->d[b];
}

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
	ifstream file(filename);

    file >> this->n;
    
    int duree[this->n];
	for(int i = 0 ; i < this->n ; ++i)
	{
		file >> duree[i];
		this->Lpred.push_back(std::vector<sommetadjacent>());
		this->Lsucc.push_back(std::vector<sommetadjacent>());
	}
		

	int idTache, nbPred, pred;

	for(int i = 0 ; i < this->n ; ++i) 
	{
		file >> idTache;
		--idTache;
		file >> nbPred;

		for(int i = 1 ; i <= nbPred ; ++i)
		{
			file >> pred;
			--pred;
			this->Lpred[idTache].push_back(std::make_pair(pred, duree[pred]));
			this->Lsucc[pred].push_back(std::make_pair(idTache, duree[pred]));
		}
	}
        
    file.close();
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
	this->calculDateAuPlusTot();
}

void graphe::calculDateAuPlusTot()
{
	//INIT
	int* T = new int[this->n];
    int* I = new int[this->n];
    this->plustot = new int[this->n];
    int* pere = new int[this->n];

	int i = 0;
    for(; i < this->n - 1 ; ++i)
        T[i] = i + 1;
    for(i = 0 ; i < this->n ; ++i)
        I[i] = i - 1;
    this->plustot[0] = 0;
    for(i = 1 ; i < this->n ; ++i)
        this->plustot[i] = -infini;
    /* tableau pere initialisé à 0 par défaut en c++ */
    int j = 0;  //noeud pivot initial

    for(int l = 1 ; l < this->n  ; ++l)
    {
        // pour chaque successeur de j..
        for(sommetadjacent s : this->Lsucc[j])
        {
            int i = s.first, cji = s.second;
            int sum = this->plustot[j] + cji;

            if(I[i] > -1 && sum > this->plustot[i])
            { 
                this->plustot[i] = sum;
                pere[i] = j;

                //reorganisation du tas T [ à partir de l'indice I[i] ]
                std::make_heap(T, T + this->n - l, Cmp(this->plustot));
            }
        }

        //Recherche dans T, de l'indice j de plus grande valeur d[i]
        j = T[0]; //sinon j reste à 0

        //Suppression de l'indice j du tas (premier element tas)
        std::pop_heap(T, T + this->n - l, Cmp(this->plustot));

        //Mettre a jour I en fonction du nouveau T
        I[j] = -1;    //j est la valeur du noeud qui a disparue du tas
        for(int z = 0 ; z < this->n - 1 - l ; ++z)
            I[T[z]] = z;
    }
}
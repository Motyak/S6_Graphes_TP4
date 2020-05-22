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
    
	//on ajoute la source a 0
	int duree[this->n + 1];
	duree[0] = 0;
	this->Lpred.push_back(std::vector<sommetadjacent>());
	this->Lsucc.push_back(std::vector<sommetadjacent>());
	

	for(int i = 1 ; i <= this->n ; ++i)
	{
		file >> duree[i];
		this->Lpred.push_back(std::vector<sommetadjacent>());
		this->Lsucc.push_back(std::vector<sommetadjacent>());
	}
	// ajout emplacement pred de la fin de projet et succ de derniere tache
	this->Lpred.push_back(std::vector<sommetadjacent>());
	this->Lsucc.push_back(std::vector<sommetadjacent>());

// // ajout predecesseur de la premiere tache et successeur de la source
// 	this->Lpred[1].push_back(make_pair(0, duree[0]));
// 	this->Lsucc[0].push_back(make_pair(1, duree[0]));
		

	int idTache, nbPred, pred;

	for(int i = 1 ; i <= this->n ; ++i) 
	{
		file >> idTache;
		file >> nbPred;

		for(int i = 1 ; i <= nbPred ; ++i)
		{
			file >> pred;
			this->Lpred[idTache].push_back(std::make_pair(pred, duree[pred]));
			this->Lsucc[pred].push_back(std::make_pair(idTache, duree[pred]));
		}
	}
	
	for(int i = 1 ; i <= this->n ; ++i)
	{
        // ajouter le sommet début de projet à toutes les taches qui n'ont pas de predecesseur
        if(this->Lpred[i].empty())
		{
			this->Lpred[i].push_back(std::make_pair(0, 0));
			this->Lsucc[0].push_back(std::make_pair(i, 0));
		}

        // ajouter le sommet fin de projet à toutes les taches qui n'ont pas de sucesseurs
		else if(this->Lsucc[i].empty())
		{
			this->Lpred[this->n + 1].push_back(std::make_pair(i, duree[i]));
			this->Lsucc[i].push_back(std::make_pair(this->n + 1, duree[i]));
		}
	}
        
    file.close();
}


/****************************************/
/* Objectif : Affichage du graphe potentiel-tâches
/****************************************/
void graphe::affichage()
{
	// cout << "arête : " << "longueur" << endl;
	// for(int i = 0; i < Lpred.size(); i++){
	// 	for(int j = 0; j < Lpred[i].size(); j++)
	// 		cout << "(" << i << "," << Lpred[i][j].first << ")" << ": " << Lpred[i][j].second << endl;
	// }

	cout << "arc : " << "durée" << endl;
	for(int i = 0; i < Lpred.size(); i++){
		for(int j = 0; j < Lpred[i].size(); j++)
			cout << "(" << Lpred[i][j].first << "," << i << ")" << ": " << Lpred[i][j].second << endl;
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
	// for(int i = 0; i < n; i++)
	for(int i = 0; i <= n + 1; i++)
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
	this->calculDateAuPlusTard();
}

void graphe::calculDateAuPlusTot()
{
	//INIT
	int* T = new int[this->n + 1];
    int* I = new int[this->n + 1];
    this->plustot = new int[this->n + 1];

	int i = 0;
    for(; i < this->n ; ++i)
        T[i] = i + 1;
    for(i = 0 ; i < this->n + 1 ; ++i)
        I[i] = i - 1;
    this->plustot[0] = 0;
    for(i = 1 ; i < this->n + 1 ; ++i)
        this->plustot[i] = -infini;

    int j = 0;  //noeud pivot initial

    for(int l = 1 ; l <= this->n + 1  ; ++l)
    {
        // pour chaque successeur de j..
        for(sommetadjacent s : this->Lsucc[j])
        {
            int i = s.first, cji = s.second;
            int sum = this->plustot[j] + cji;

            if(I[i] > -1 && sum > this->plustot[i])
            { 
                // std::cout<<"On part du sommet "<<j<<std::endl;//debug
                // std::cout<<"la tache "<<i<<" passe de "<<this->plustot[i];//debug
                this->plustot[i] = sum;
                // std::cout<<" a "<<this->plustot[i]<<std::endl<<std::endl;//debug

                //reorganisation du tas T [ à partir de l'indice I[i] ]
                std::make_heap(T, T + this->n + 1 - l, Cmp(this->plustot));
            }
        }

        //Recherche dans T, de l'indice j de plus grande valeur d[i]
        // j = T[0]; //sinon j reste à 0
        j++;    //topologique

        //Suppression de l'indice j du tas (premier element tas)
        std::pop_heap(T, T + this->n + 1 - l, Cmp(this->plustot));

        //Mettre a jour I en fonction du nouveau T
        I[j] = -1;    //j est la valeur du noeud qui a disparue du tas
        for(int z = 0 ; z < this->n - l ; ++z)
            I[T[z]] = z;
    }
}

void graphe::calculDateAuPlusTard()
{
	//INIT
	int* T = new int[this->n + 1];
    int* I = new int[this->n + 1];
    this->plustard = new int[this->n + 1];

	int i = 0;
    for(; i < this->n ; ++i)
        T[i] = i + 1;
    for(i = 0 ; i < this->n + 1 ; ++i)
        I[i] = i - 1;
    this->plustard[0] = 0;
    for(i = 1 ; i < this->n + 1 ; ++i)
        this->plustard[i] = infini;
	this->plustard[this->n + 1] = this->plustot[this->n + 1];	//

    int j = this->n + 1;  //noeud pivot initial

    for(int l = 1 ; l <= this->n + 1  ; ++l)
    {
        // pour chaque predecesseur de j..
        for(sommetadjacent s : this->Lpred[j])
        {
            int i = s.first, cji = s.second;

			int min = infini;
            for(int z = j  ; z <= this->n + 1 ; ++z)
			{
                // si l'étape en question est bien sucesseur de z.
                if(std::find(this->Lpred[z].begin(), this->Lpred[z].end(), s) != this->Lpred[z].end())
				    if(this->plustard[z] - cji < min)
					    min = this->plustard[z] - cji;
			}

            if(I[i] > -1 && min < this->plustard[i])
            { 
                // std::cout<<"On part du sommet "<<j<<std::endl;//debug
                // std::cout<<"la tache "<<i<<" passe de "<<this->plustard[i];//debug
                this->plustard[i] = min;
                // std::cout<<" a "<<this->plustard[i]<<std::endl<<std::endl;//debug

                //reorganisation du tas T [ à partir de l'indice I[i] ]
                std::make_heap(T, T + this->n + 1 - l, Cmp(this->plustard));
            }
        }

        //Recherche dans T, de l'indice j de plus grande valeur d[i]
        // j = T[0]; //sinon j reste à 0
        --j;

        //Suppression de l'indice j du tas (premier element tas)
        std::pop_heap(T, T + this->n + 1 - l, Cmp(this->plustard));

        //Mettre a jour I en fonction du nouveau T
        I[j] = -1;    //j est la valeur du noeud qui a disparue du tas
        for(int z = 0 ; z < this->n - l ; ++z)
            I[T[z]] = z;
    }
}

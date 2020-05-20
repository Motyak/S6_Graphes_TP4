/************************************************/
/* Auteur : S. Gueye				*/
/* TP : Ordonnancement 				*/
/* Date dernière maj : 04/05/2020		*/
/************************************************/

const int infini = 1e+5;
typedef pair<int,int> sommetadjacent; // un sommet adjacent j, à un noeud i, est une paire (numero sommet, longueur de l'arête (i,j))
typedef vector< vector<sommetadjacent> > listePred;
typedef vector< vector<sommetadjacent> > listeSucc;

class graphe{
	int n; 			// Nombre de noeuds du graphe potentiel-tâches (incluant les tâches fictives)
	listePred Lpred; 	// Graphe potentiel-tâches sous la forme d'une liste d'adjacence des prédécesseurs de chaque noeud
	listeSucc Lsucc; 	// Graphe potentiel-tâches sous la forme d'une liste d'adjacence des successeurs de chaque noeud
	int *plustot;		// Tableau stockant les dates de début au plus tôt de toutes les tâches
	int *plustard;		// Tableau stockant les dates de début au plus tard de toutes les tâches

public : 
	graphe(char* filename);
	void affichage();
	void ordo();
	void resultats();
};

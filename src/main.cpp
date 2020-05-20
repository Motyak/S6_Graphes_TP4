#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

#include "ordo.h"

int main(int argc,char** argv)
{
	if(argc < 2)
		cout << "Nombre d'arguments insuffisants" << endl;
	else{
		graphe obj(argv[1]);
		obj.affichage();
		obj.ordo();
		obj.resultats();
	}

	return(1);
}

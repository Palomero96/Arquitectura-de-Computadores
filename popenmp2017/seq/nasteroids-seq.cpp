/* Librerias */
#include <iostream>
#include <regex>
#include <cmath>
using namespace std;
/* Funciones */
bool checkArgs ( int argc, char *argv[]) {
	regex e("\\d+");
	regex f("\\d+\\.\\d+");
	bool check = true;
	/* Comprobacion de numero de argumentos*/
	if(argc != 6) {
		check = false;
	} else {
		/* Comprobacion de numero de asteroides */
		if(!regex_match(argv[1], e)) {
			check= false;
		}
		/* Comprobacion de numero de iteraciones*/
		if(!regex_match(argv[2], e)) {
			check= false;
		}
		/* Comprobacion de numero de planetas */
		if(!regex_match(argv[3], e)) {
			check= false;
		}
		/* Comprobacion de posicion del rayo */
		if(!regex_match(argv[4], f)) {
			check= false;
		} else {
			double ray = stod(argv[4]);
			if (ray > 199 || ray < 1) {
				check = false;
			}
		}
		/* Comprobacion de la semilla */
		if(regex_match(argv[5], e)) {
			int seed = stoi(argv[5]);
			if(seed == 0){
				check = false;
			}
		} else {
			check = false;
		}
	}
	if(!check) {
		cerr << "nasteroids-seq: Wrogn arguments.\nCorrect use:\nnasteroids-seq num_asteroides num_iteraciones num_planetas pos_rayo semilla\n";
	}

	return check;
}
/* Main */
int main(int argc, char *argv[])
{
	/* Llamamos a funcion para que compruebe argumentos */
	if (!checkArgs(argc, argv)) {
		return -1; 
	}
	/* Declaracion de variables*/
	
	return 0;
}

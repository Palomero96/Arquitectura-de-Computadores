/* Librerias */
#include <iostream>
#include <regex>
#include <cmath>
#include <random>

/* Constantes */
const double gravity = 0.00006674; 
const double t = 0.1; 		//Intervalo de tiempo
const double dmin = 2.0; 	//Distancia minima
const double width = 200; 	//Anchura del espacio			**No estoy seguro del tipo, confirmen
const double height = 200;	//Altura del espacio 			**No estoy seguro del tipo, confirmen
const int ray_width = 4;	//Anchura del rayo				**No estoy seguro del tipo, confirmen
const int m = 1000;			//Media para el calculo de distribucion normal de las masas				**No estoy seguro del tipo, confirmen
const int sdm = 50; 		//Desviacion estandar para el calculo de la dist normal de las masas 	**No estoy seguro del tipo, confirmen

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
			check = false;
		}
		/* Comprobacion de numero de iteraciones*/
		if(!regex_match(argv[2], e)) {
			check = false;
		}
		/* Comprobacion de numero de planetas */
		if(!regex_match(argv[3], e)) {
			check = false;
		}
		/* Comprobacion de posicion del rayo */
		if(!regex_match(argv[4], f)) {
			check = false;
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
int main(int argc, char *argv[]){
	
	
	/* Llamamos a funcion para que compruebe argumentos */
	if (!checkArgs(argc, argv)) {
		return -1; 
	}
	/* Declaracion de variables*/
	int seed = stoi(argv[5]);
	
	/* Código previo necesario para la obtención de las posiciones iniciales de los asteroides */
	default_random_engine re{seed};
	uniform_real_distribution<double> xdist{0.0, std::nextafter(width, std :: numeric_limits<double>::max())};
	uniform_real_distribution<double> ydist{0.0, std::nextafter(height, std :: numeric_limits<double>::max())};
	normal_distribution<double> mdist{m, sdm};

	return 0;
}

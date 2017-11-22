/* Librerias */
#include <iostream>
#include <regex>
#include <cmath>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
/* Estructuras de datos */
struct asteroide {
	int id;
	double x;
	double y;
	double mass;
	double vx;
	double vy;
	double px;
	double py;
	double pvx;
	double pvy;
};
struct planeta {
	double x;
	double y;
	double mass;
};

/* Funciones */
/* Metodo de comprobacion de variables */
bool checkArgs (int argc, char *argv[]) {
	/* Expresion regular para enteros */
	regex e("\\d+");
	/* Expresion regular para numeros en coma flotante */
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
/* Metodo de creacion de asteroides */
void createAstros (int num_asteroides, int num_planetas, unsigned int semilla, vector<asteroide> &asteroides, planeta *planetas){
	/* Constantes y variables */
	double mass = 1000.0;
	double sdm = 50.0;
	double width = 200.0;
	double height = 200.0;
	int i = 0;
	/* Distribuciones para coordenadas y masas */
	default_random_engine re{semilla};
	uniform_real_distribution<double> xdist{0.0, nextafter(width, numeric_limits<double>::max())};
	uniform_real_distribution<double> ydist{0.0, nextafter(height, numeric_limits<double>::max())};
	normal_distribution<double> mdist{mass, sdm};
	/* Creacion de asteroides */
	for( i = 0 ; i < num_asteroides ; i++){
		/* Creamos el asteroide y rellenamos sus campos */
		asteroide aaux;
		aaux.id = i;
		aaux.x = xdist(re);
		aaux.y = ydist(re);
		aaux.mass = mdist(re);
		aaux.vx = 0.0;
		aaux.vy = 0.0;
		aaux.px = 0.0;
		aaux.py = 0.0;
		aaux.pvx = 0.0;
		aaux.pvy = 0.0;
		/* Añadimos el asteroide a la lista */
		asteroides.push_back(aaux);
	}
	/* Creacion de planetas*/
	for(i = 0; i < num_planetas ; i++){
		/* Creamos el planeta */
		planeta paux;
		/* Rellenamos sus ejes en funcion de su resto con 4 */	
		switch ( i%4 ){
    		case 0:
    			paux.x = 0.0;
    			paux.y = ydist(re);
    			break;
    		case 1:
    			paux.x = xdist(re);
    			paux.y = 0.0;
				break;
    		case 2:
    			paux.x = 200.0;
    			paux.y = ydist(re);
				break;
    		case 3:
    			paux.x = xdist(re);
    			paux.y = 200.0;
    			break;
		}
		/* Rellenamos su masa */
		paux.mass = mdist(re)*10;
		/* Añadimos el planeta al array */
		planetas[i] = paux;
		
	}	
}
/* Metodo de calculo de fuerzas de asteroides sobre un asteroide */
void calcAsts (vector<asteroide> &asteroides, int actast) {
	/* Declaramos variables y constantes */
	double distancia = 0.0;
	double pendiente = 0.0;
	double alfa = 0.0;
	double fuerza = 0.0;
	double g = 6.674 * exp(-5);
	int signox = 0;
	int signoy = 0;
	/* Para cada asteroide del espacio */
	for(int i = 0 ; i < asteroides.size() ; i++) {
		/* Si es el mismo asteroide, no se calcula la fuerza que ejerce sobre si mismo */
		if (i == actast) {
			continue;
		}
		/* Calculamos la distancia entre los elementos */
		distancia = sqrt(pow((asteroides[actcast].x - asteroides[i].x),2)+pow((asteroides[actast].y - asteroides[i].y),2));
		/* Si la distancia es menor o igual a dos, no se calcula fuerza de atraccion */
		if (distancia <= 2.00) {
			continue;
		}
		/* Calculamos la pendiente */
		pendiente = (asteroides[actast].y - asteroide[i].y)/(asteroides[actast].x - asteroides[i].x);
		if(asteroides[actast].x != asteroides[i].x) {
			if(pendiente < -1  || pendiente > 1){
				pendiente = pendiente - trunc(pendiente);
			}
		}
		alfa = atan(pendiente);
		fuerza = g*asteroides[astact].mass*asteroides[i].mass/pow(distancia,2);
		if (asteroides[actast].x <= asteroides[i].x) {
			signox = 1;
		} else {
			signox = -1;
		}
		if (asteroides[actast].y <= asteroides[i].y) {
			signoy = 1;
		} else {
			signoy = -1;
		}
	}
}
/* Metodo de calculo de fuerzas de planetas sobre un asteroide */
void calcPlas (planeta *planetas, vector<asteroide> &asteroides, int actast) {
	/* Declaramos variables */
	double distancia = 0.0;
	double pendiente = 0.0;
	double alfa = 0.0;
	double g = 6.674 * exp(-5);
	/* Para cada planeta del espacio */
	for(int i = 0 ; i < num_planetas ; i++) {
		/* Calculamos la distancia entre los elementos */
		distancia = sqrt(pow((asteroides[actcast].x - planetas[i].x),2)+pow((asteroides[actast].y - planetas[i].y),2));
		/* Calculamos la pendiente */
		pendiente = (asteroides[actast].y - planetas[i].y)/(asteroides[actast].x - planetas[i].x);
		if(asteroides[actast].x != planetas.x) {
			if(pendiente < -1  || pendiente > 1){
				pendiente = pendiente - trunc(pendiente);
			}
		}
		alfa = atan(pendiente);
		
	}
}
/* Main */
int main(int argc, char *argv[]){
	
	
	/* Llamamos a funcion para que compruebe argumentos */
	if (!checkArgs(argc, argv)) {
		return -1; 
	}
	/* Declaracion de constantes */
	
	/* Declaracion de variables */
	int num_asteroides = stoi(argv[1]);
    int num_iteraciones = stoi(argv[2]);
    int num_planetas = stoi(argv[3]);
    double pos_rayo = stod(argv[4]);
    unsigned int semilla = stoi(argv[5]);
    /* Creamos lista para los asteroides */
    vector<asteroide> asteroides;
    /* Creamos array para planetas */
	planeta *planetas = new planeta[num_planetas];
	/* Llamamos a la funcion para crear los astros */
    createAstros(num_asteroides, num_planetas, semilla, asteroides, planetas);
    ofstream init("init_conf.txt");
    /* Imprimimos los datos iniciales en el fichero */
    init << num_asteroides << " " << num_iteraciones << " " << num_planetas << " " << pos_rayo << " " << semilla << endl;
    /* Imprimimos los asteroides en el fichero */
    for (unsigned i = 0 ; i < asteroides.size() ; i++){
    	init << fixed << setprecision(3) <<  asteroides[i].x << " " << asteroides[i].y << " " << asteroides[i].mass << endl;
    }
    /* Imprimimos los planetas en el fichero */
    for (int i = 0; i<num_planetas ; i++) {
    	init << fixed << setprecision(3) << planetas[i].x << " " << planetas[i].y << " " << planetas[i].mass << " " << endl;
	}
	/* Imprimimos el rayo */
	init << fixed << setprecision(3) << 0.000 << " " << pos_rayo << endl;
	/* Calculamos las fuerzas que afectan a los asteroides */
	
	return 0;
}

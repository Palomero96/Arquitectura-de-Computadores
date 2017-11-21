/* Librerias */
#include <iostream>
#include <regex>
#include <cmath>
#include <random>
#include <forward_list>

/* Constantes */
const double gravity = 0.00006674; 
const double t = 0.1; 		//Intervalo de tiempo
const double dmin = 2.0; 	//Distancia minima
//const double width = 200.0; 	//Anchura del espacio
//const double height = 200.0;	//Altura del espacio
const int ray_width = 4;	//Anchura del rayo				**No estoy seguro del tipo, confirmen
//const int m = 1000;			//Media para el calculo de distribucion normal de las masas				
//const int sdm = 50; 		//Desviacion estandar para el calculo de la dist normal de las masas 	

using namespace std;

/* Estructuras de datos */
class Asteroide {
		double x;
		double y;
		double mass;
		double vx;
		double vy;
		double px;
		double py;
		double pvx;
		double pvy;
	public:
		void set_values(double, double, double);
};
void Asteroide::set_values(double a, double b, double m){
	x = a;
	y = b;
	mass = m;
}



struct Planeta {
	double x;
	double y;
	double mass;
};
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
		}
		/* Comprobacion maximo asteroides e iteraciones */
		int num_asteroides = stoi(argv[1]);
		int num_iteraciones = stoi(argv[2]);
    	if(num_asteroides > 1000 || num_iteraciones >5000){
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
	int num_asteroides = stoi(argv[1]);
    //int num_iteraciones = stoi(argv[2]);
    int num_planetas = stoi(argv[3]);
    //double pos_rayo = stod(argv[4]);
	unsigned int seed = stoi(argv[5]);
	    
	/* Codigo previo necesario para la obtencion de las posiciones iniciales de los asteroides */
	default_random_engine re{seed};
	uniform_real_distribution<double> xdist{0.0, std::nextafter(200.0, std :: numeric_limits<double>::max())};
	uniform_real_distribution<double> ydist{0.0, std::nextafter(200.0, std :: numeric_limits<double>::max())};
	normal_distribution<double> mdist{1000.0, 50.0}; //Media y desv estandar para el calculo de distrib normal de masas. Lo ponemos directamente para evitar la creacin de más variables

	/* Creacion Asteroides */
    forward_list<Asteroide> asteroides; //Creamos un array con los asteroides
	for(int i = 1; i <= num_asteroides; i++){
		cerr << "Asteroide " << i << ": \n";
		Asteroide ast;
		ast.set_values(xdist(re), ydist(re), mdist(re));
		asteroides.emplace_front(ast);
		//cerr << asteroides[i].x << " " << asteroides[i].y << " " << asteroides[i].mass << "\n";	
	}
	
	/*Creacion Planetas*/
	Planeta planetas[num_planetas-1]; //Creamos un array con los planetas
	int j = 1;
	while(1){  //Con este bucle asignaremos la masa y la posicion de cada planeta. Si el contador supera al numero de planetas, salimos del bucle

		planetas[j].x = 0.0;
		planetas[j].y = ydist(re);
		planetas[j].mass = 10 * mdist(re); //Multiplicamos por 10 la masa de un asteroide para obtener la del planeta
		j++;
		
		if(j > num_planetas){
			break;
		}
		planetas[j].x = xdist(re);
		planetas[j].y = 200;
		planetas[j].mass = 10 * mdist(re);
		j++;
		
		if(j > num_planetas){
			break;
		}
		planetas[j].x = 200;
		planetas[j].y = ydist(re);
		planetas[j].mass = 10 * mdist(re);
		j++;
			
		if(j > num_planetas){
			break;
		}		
		planetas[j].x = xdist(re);
		planetas[j].y = 0;
		planetas[j].mass = 10 * mdist(re);
		j++;
		
		if(j > num_planetas){
			break;
		}
	}
	//Se borra posteriormente, solo para ver si se crean correctamente
	for(int i = 1; i <= num_planetas; i++){
		cerr << "Planeta " << i << ": \n";
		cerr << planetas[i].x << " " << planetas[i].y << " " << planetas[i].mass << "\n";	
	}
	return 0;
}

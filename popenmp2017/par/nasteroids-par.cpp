/* Librerias */
#include <iostream>
#include <regex>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
#include <omp.h>
using namespace std;
/* Estructuras de datos */
struct asteroide {
	double x;
	double y;
	double mass;
	double vx;
	double vy;
	/* Creamos variables para que guarden el estado anterior del asteriode */
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
			if (ray > 198 || ray < 2) {
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
		cerr << "nasteroids-par: Wrogn arguments.\nCorrect use:\nnasteroids-par num_asteroides num_iteraciones num_planetas pos_rayo semilla\n";
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
	#pragma omp parallel for ordered schedule(runtime)
	for( i = 0 ; i < num_asteroides ; i++){
		/* Rellenamos los campos del asteroide */
		asteroides[i].vx = 0.0;
		asteroides[i].vy = 0.0;
		asteroides[i].x = 0.0;
		asteroides[i].y = 0.0;
		asteroides[i].pvx = 0.0;
		asteroides[i].pvy = 0.0;
		#pragma omp ordered
		{
		asteroides[i].px = xdist(re);
		asteroides[i].py = ydist(re);
		asteroides[i].mass = mdist(re);
		}
	}
	/* Creacion de planetas*/
	#pragma omp parallel for ordered schedule(runtime)
	for(i = 0; i < num_planetas ; i++){
		#pragma omp ordered
		{
		/* Rellenamos los ejes del planeta en funcion de su resto con 4 */	
		switch ( i%4 ){
    		case 0:
    			planetas[i].x = 0.0;
    			planetas[i].y = ydist(re);
    			break;
    		case 1:
    			planetas[i].x = xdist(re);
    			planetas[i].y = 0.0;
				break;
    		case 2:
    			planetas[i].x = 200.0;
    			planetas[i].y = ydist(re);
				break;
    		case 3:
    			planetas[i].x = xdist(re);
    			planetas[i].y = 200.0;
    			break;
		}
		/* Rellenamos su masa */
		planetas[i].mass = mdist(re)*10;
		}	
	}
}
/* Metodo de calculo de fuerzas de asteroides sobre un asteroide */
void calcAsts (vector<asteroide> asteroides,  int actast, double &fuerzax, double &fuerzay) {
	/* Declaramos variables y constantes */
	double distancia = 0.0;
	double pendiente = 0.0;
	double alfa = 0.0;
	double fuerza = 0.0;
	double g = 6.674 * exp(-5);
	/* Para cada asteroide del espacio */
	for(unsigned i = 0 ; i < asteroides.size() ; i++) {
		/* Si es el mismo asteroide, no se calcula la fuerza que ejerce sobre si mismo */
		int actasta = (int) i;
		if (actast == actasta) {
			continue;
		}
		/* Calculamos la distancia entre los elementos */
		distancia = sqrt(pow((asteroides[actast].px - asteroides[i].px),2)+pow((asteroides[actast].py - asteroides[i].py),2));
		/* Si la distancia es menor o igual a dos, no se calcula fuerza de atraccion */
		if (distancia <= 2.00) {
			continue;
		}
		/* Calculamos la pendiente */
		pendiente = (asteroides[actast].py - asteroides[i].py)/(asteroides[actast].px - asteroides[i].px);
		/* Truncamos la pendiente si es necesario */
		if(asteroides[actast].px != asteroides[i].px) {
			if(pendiente < -1  || pendiente > 1){
				pendiente = pendiente - trunc(pendiente);
			}
		}
		/* Calculamos el angulo */
		alfa = atan(pendiente);
		/* Calculo de la fuerza */
		fuerza = g*asteroides[actast].mass*asteroides[i].mass/pow(distancia,2);
		/* Comprobamos que la fuerza no sea superior a la permitida */
		if(fuerza > 200.0){
			fuerza = 200.0;
		}
		/* Calculamos las componentes de la fuerza y las añadimos al sumatorio de fuerzas */
		fuerzax = fuerzax + fuerza*cos(alfa);
		fuerzay = fuerzay + fuerza*sin(alfa);
		
		fuerza = 0.0;
	}
}
/* Metodo de calculo de fuerzas de planetas sobre un asteroide */
void calcPlas (planeta *planetas, vector<asteroide> asteroides, int actast, double &fuerzax, double &fuerzay) {
	/* Declaramos variables y constantes */
	double distancia = 0.0;
	double pendiente = 0.0;
	double alfa = 0.0;
	double fuerza = 0.0;
	double g = 6.674 * exp(-5);
	/* Para cada planeta del espacio */
	for(unsigned i = 0 ; i < asteroides.size() ; i++) {
		/* Calculamos la distancia entre los elementos */
		distancia = sqrt(pow((asteroides[actast].px - planetas[i].x),2)+pow((asteroides[actast].py - planetas[i].y),2));
		/* Calculamos la pendiente */
		pendiente = (asteroides[actast].py - planetas[i].y)/(asteroides[actast].px - planetas[i].x);
		/* Truncamos la pendiente si es necesario */
		if(asteroides[actast].px != planetas[i].x) {
			if(pendiente < -1  || pendiente > 1){
				pendiente = pendiente - trunc(pendiente);
			}
		}
		/* Calculamos el angulo */
		alfa = atan(pendiente);
		/* Calculo de la fuerza */
		fuerza = g*asteroides[actast].mass*planetas[i].mass/pow(distancia,2);
		/* Comprobamos que la fuerza no sea superior a la permitida */
		if(fuerza > 200.0){
			fuerza = 200.0;
		}
		/* Calculamos las componentes de la fuerza y las añadimos al sumatorio de fuerzas */
		fuerzax = fuerzax + fuerza*cos(alfa);
		fuerzay = fuerzay + fuerza*sin(alfa);
		
		fuerza = 0.0;
	}
}
/* Main */
int main(int argc, char *argv[]){
	/* Obtenemos el tiempo antes de la ejecucion del codigo a evaluar */
	double ini = omp_get_wtime();
	/* Llamamos a funcion para que compruebe argumentos */
	if (!checkArgs(argc, argv)) {
		return -1; 
	}
	/* Declaracion de variables */
	int num_asteroides = stoi(argv[1]);
    int num_iteraciones = stoi(argv[2]);
    int num_planetas = stoi(argv[3]);
    double pos_rayo = stod(argv[4]);
    unsigned int semilla = stoi(argv[5]);
    double fuerzax = 0.0;
    double fuerzay = 0.0;
    /* Creamos lista para los asteroides */
    vector<asteroide> asteroides (num_asteroides);
    /* Creamos array para planetas */
	planeta *planetas = new planeta[num_planetas];
	/* Llamamos a la funcion para crear los astros */
    createAstros(num_asteroides, num_planetas, semilla, asteroides, planetas);
    ofstream init("init_conf.txt");
    /* Imprimimos los datos iniciales en el fichero */
    init << num_asteroides << " " << num_iteraciones << " " << num_planetas << " " << pos_rayo << " " << semilla << endl;
    /* Imprimimos los asteroides en el fichero */
    #pragma omp for ordered schedule(runtime)
    for (unsigned i = 0 ; i < asteroides.size() ; i++){
    	#pragma omp ordered
    	init << fixed << setprecision(3) <<  asteroides[i].px << " " << asteroides[i].py << " " << asteroides[i].mass << endl;
    }
    /* Imprimimos los planetas en el fichero */
    #pragma omp for ordered schedule(runtime)
    for (int i = 0; i<num_planetas ; i++) {
    	#pragma omp ordered
    	init << fixed << setprecision(3) << planetas[i].x << " " << planetas[i].y << " " << planetas[i].mass << " " << endl;
	}
	/* Imprimimos el rayo en el fichero */
	init << fixed << setprecision(3) << 0.000 << " " << pos_rayo << endl;
	/* Realizamos las iteraciones */
	for(int a = 0 ; a < num_iteraciones ; a++) {
		/* Comprobamos que no se hayan destruido todos los asteroides */
		if (asteroides.size() == 0) {
			break;
		}
		/* Calculamos el resultado de la iteracion */
		#pragma omp parallel for schedule(runtime)
		for(unsigned i = 0; i < asteroides.size() ; i++){
			fuerzax = 0.0;
			fuerzay = 0.0;
			/* Llamamos a los metodos que calculan fuerzas */
			calcAsts(asteroides, i, fuerzax, fuerzay);
			calcPlas(planetas, asteroides, i, fuerzax, fuerzay);
			/* Guardamos los datos actuales del asteroide */
			asteroides[i].vx = asteroides[i].pvx + (fuerzax/asteroides[i].mass) * 0.1;
			asteroides[i].vy = asteroides[i].pvy + (fuerzay/asteroides[i].mass) * 0.1;
			asteroides[i].x = asteroides[i].px + asteroides[i].vx * 0.1;
			asteroides[i].y = asteroides[i].py + asteroides[i].vy * 0.1;
			/* Comprobamos el efecto rebote */
			if(asteroides[i].x <= 0.0){
				asteroides[i].x = 2.0;
				asteroides[i].vx = asteroides[i].vx * -1;
			}
			if(asteroides[i].y <= 0.0){
				asteroides[i].y = 2.0;
				asteroides[i].vy = asteroides[i].vy * -1;
			}
			if(asteroides[i].x >= 200.0){
				asteroides[i].x = 198.0;
				asteroides[i].vx = asteroides[i].vx * -1;
			}
			if(asteroides[i].y >= 200.0){
				asteroides[i].y = 198.0;
				asteroides[i].vy = asteroides[i].vy * -1;
			}
			
		}
		/* Calculamos si el rayo aniquila asteroides */	
		for(unsigned i = 0; i < asteroides.size() ; i++){
			if(asteroides[i].y <= (pos_rayo + 2) && asteroides[i].y >= (pos_rayo - 2)){
				asteroides.erase(asteroides.begin()+i);
				i--;
			}
		}
		/* Liberamos recursos de asteroides muertos */
		asteroides.shrink_to_fit();
		/* Guardamos los datos como anteriores en los asteroides */	
		#pragma omp parallel for schedule(runtime)
		for(unsigned i = 0; i < asteroides.size() ; i++){
			asteroides[i].px = asteroides[i].x;
			asteroides[i].py = asteroides[i].y;
			asteroides[i].pvx = asteroides[i].vx;
			asteroides[i].pvy = asteroides[i].vy;
		}
			
	}
	/* Imprimimos resultados finales en fichero */
	ofstream out("out.txt");
	#pragma omp parallel for ordered schedule(runtime)
	for (unsigned i = 0 ; i < asteroides.size() ; i++) {
		#pragma omp ordered
		out << fixed << setprecision(3) << asteroides[i].px << " " << asteroides[i].py << " " << asteroides[i].pvx << " " << asteroides[i].pvy << " " << asteroides[i].mass << endl;
	}
	/* Obtenemos el tiempo después de la ejecucion del codigo a evaluar */
	double fin = omp_get_wtime();
	/* Hayamos la diferencia de tiempos para saber el tiempo empleado en la ejecucion */
	out << fin - ini << endl;
	return 0;
}

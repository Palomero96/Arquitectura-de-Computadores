/* Librerías */
#include <iostream>
#include <regex>
#include <fstream>
#include <iomanip>
#include <random>
#include <forward_list>
#include <omp.h>
using namespace std;
/* Funciones */
/*bool checkArgs ( int argc, char *argv[]) {
	regex r("\\d+");
	regex f("[+-]?([0-9]*[.])?[0-9]+");
	bool check = true;
	if(argc != 6) {
		check = false;
	} else {
		if(!regex_match(argv[1], r)) {
			check= false;
		}
		if(!regex_match(argv[2], r)) {
			check= false;
		}
		if(!regex_match(argv[3], r)) {
			check= false;
		}

		if(regex_match(argv[5], r)) {
			int seed = stoi(argv[5]);
			if(seed == 0){
				check = false;
			}
		}else {
			check = false;
		}		
	}
	
	if(!check) {
		cerr << "Wrong arguments.\nCorrect use:\nnasteroids-seq num_asteroides num_iteraciones num_planetas pos_rayo semilla\n";
	}

	return check;
}*/
struct planeta {
	int id;
	double x;
    double y;
    double mass;
};
/* Main */
int main(){
/*		if(argc != 6) {
		return -1;
	}
	//Definimos las variables
	int num_asteroides = stoi(argv[1]);
	int num_iteraciones = stoi(argv[2]);
	int num_planetas = stoi(argv[3]);
	double pos_rayo = stod(argv[4]);
	int semilla = stoi(argv[5]);
	//Calculamos los parametros iniciales
	
	
	//Creamos el archivo donde escribiremos los parametros de entrada y las 
	ofstream out("init_conf.txt");
	out << fixed << setprecision(3) << num_asteroides <<" "<<num_iteraciones<<" "<<num_planetas<<" "<< pos_rayo<< " " <<semilla<< endl;
*/
	
	double mass = 1000.0;
    double sdm = 50.0;
    double width = 200.0;
    double height = 200.0;
    int semilla = 2000;
    default_random_engine re{semilla};
    uniform_real_distribution <double> xdist{0.0, nextafter(width, numeric_limits<double>::max())};
    uniform_real_distribution <double> ydist{0.0, nextafter(height, numeric_limits<double>::max())};
    normal_distribution <double> mdist{mass, sdm};
  	//
  	vector <planeta> planetas;
    	
			double ini = omp_get_wtime(); 
	
	
		#pragma omp parallel for 
		for(int i=0; i<4; i++){
		planeta nombre;
		nombre.id=xdist(re);
		nombre.x=i;
		nombre.y=i;
		nombre.mass=mdist(re); 
		#pragma omp critical
		planetas.push_back(nombre); 
		
		}
		#pragma omp parallel for ordered collapse(2)
		for(unsigned i=0; i<planetas.size(); i++){
			for(unsigned j=0; j<planetas.size(); j++){	
			planetas[i].x=planetas[i].x + planetas[j].y;
			#pragma omp ordered
			cout << "Soy:" << omp_get_thread_num()<< " ID: " <<planetas[i].id << " Valor: " << planetas[i].x << endl;
		}
		
		}
		

cout << endl;
			double fin = omp_get_wtime();
			cout << "hay estos hilos uuuu:" << omp_get_num_threads()<<endl;
		cout << fin - ini << endl;
		cout << endl;
		for(unsigned i=0; i<4; i++){
		
		cout << planetas[i].id << " " << planetas[i].x << " " << planetas[i].y << " " << planetas[i].mass << endl;
		
		}
	

	
	return 0;
	
}

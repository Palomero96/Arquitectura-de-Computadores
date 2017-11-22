/* Librerías */
#include <iostream>
#include <regex>
#include <fstream>
#include <iomanip>
#include <random>
#include <forward_list>
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
   	vector <planeta> planetas ;
    
		for(int i=0; i<4; i++){
		planeta nombre;
		nombre.id=i;
	/*	nombre.x=xdist(re);
		nombre.y=ydist(re);
		nombre.mass=mdist(re); */
		planetas.push_back(nombre);
		
		}
		
		for(unsigned i=0; i<planetas.size(); i++){
		
		cout << planetas[i].id << " ";
		
		}
		planetas.erase(planetas.begin()+2);
			cout << "\n";
	
		for(unsigned i=0; i<planetas.size(); i++){
		cout << planetas[i].id << " ";
		}
		double g = 0.044969058;
			cout << "\n" << g;
	g = 6.674 * exp(-5);
			cout << "\n" << g;
		planetas.clear();
		planetas.shrink_to_fit();
	
	return 0;
	
}

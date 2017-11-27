/* Librerías */
#include <iostream>
#include <regex>
#include <fstream>
#include <iomanip>
#include <random>
#include <forward_list>
#include <omp.h>
using namespace std;

struct planeta {
	int id;
	double x;
    double y;
    double mass;
};
/* Main */
int main(){
	
	double mass = 1000.0;
    double sdm = 50.0;
    double width = 200.0;
    double height = 200.0;
    int semilla = 2000;
    default_random_engine re{semilla};
    uniform_real_distribution <double> xdist{0.0, nextafter(width, numeric_limits<double>::max())};
    uniform_real_distribution <double> ydist{0.0, nextafter(height, numeric_limits<double>::max())};
    normal_distribution <double> mdist{mass, sdm};
  	vector <planeta> planetas (6);
  	//planeta *planetas = new planeta[4];
    	//#pragma omp parallel num_threads(4) shared(planetas){
		
	
		for(int i=0; i<6; i++){
		
		planetas[i].id=i;
		planetas[i].x=i;
		planetas[i].y=i;
		planetas[i].mass=i; 
		
		}
		for(int i=0; i<6; i++){
		cout << planetas[i].id << " " << planetas[i].x << " " << planetas[i].y << " " << planetas[i].mass << endl;		
		}
//	}
		for(int i=0; i<20; i++){
			for(int j=0; j<4; j++){
				planetas[j].x=planetas[j].x + planetas[j+1].x;
			}
		}
			for(int i=0; i<6; i++){
		cout << planetas[i].id << " " << planetas[i].x << " " << planetas[i].y << " " << planetas[i].mass << endl;		
		}
	
	

/*	for(unsigned i=0; i<4; i++){
		
		cout << planetas[i].id << " " << planetas[i].x << " " << planetas[i].y << " " << planetas[i].mass << endl;
		
		}
		cout << "3. capacity of myvector: " << planetas.capacity() << '\n';

	for(unsigned i=0; i<planetas.size(); i++){
		if(i==2){
		planetas.erase(planetas.begin()+i);
		delete &planetas[i];
			i--;
		}
		
	}

	planetas.shrink_to_fit();
	
	
 cout << "3. capacity of myvector: " << planetas.capacity() << '\n';
	for(unsigned i=0; i<planetas.size(); i++){
		
		cout << planetas[i].id << " " << planetas[i].x << " " << planetas[i].y << " " << planetas[i].mass << endl;
		
		}
	for(unsigned i=0; i<planetas.size(); i++){
		if(i==0){
			planetas.erase(planetas.begin()+i);
		i--;
		}
	
	}
	
	planetas.shrink_to_fit();
cout << "3. capacity of myvector: " << planetas.capacity() << '\n';
	
*/
	
	return 0;
	
}

/* Librerias */
#include <iostream>
#include <regex>
using namespace std;
/* Funciones */
bool checkArgs ( int argc, char *argv[]) {
	regex r("\\d+");
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
		} else {
			check = false;
		}
	}

	if(!check) {
		cerr << "Wrogn arguments.\nCorrect use:\nnasteroids-seq num_asteroides num_iteraciones num_planetas pos_rayo semilla\n";
	}

	return check;
}
/* Main */
int main(int argc, char *argv[])
{
	cout << checkArgs(argc, argv);
	return 0;
}

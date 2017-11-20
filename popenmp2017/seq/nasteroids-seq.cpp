/* Librerías */
#include <iostream>
#include <regex>
using namespace std;
/* Funciones */
bool checkArgs ( int argc, char **argv[]) {
	regex r("\\d+");
	smatch match;
	bool check = true;
	if(argc != 2) {
		check = false;
	} else {
		if(regex_match(argv[1], match, r)) {
			cout << match;
		}
	}

	if(!check) {
		cerr << "Wrogn arguments.\nCorrect use:\nnasteroids-seq num_asteroides num_iteraciones num_planetas pos_rayo semilla\n";
	}

	return check;

}
/* Main */
int main(int argc, char const **argv[])
{
	cout << checkArgs(argc, argv[]);
	return 0;
}

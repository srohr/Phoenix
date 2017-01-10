#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

int main(){
	const int MAX = 800;
	srand (time(NULL));

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 4; j++)
			cout << rand()%801 << " ";
		cout << endl;
	}
	
}

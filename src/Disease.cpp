#include "Disease.h"

bool Disease::getIsSick(int timeFrameDays) {

	double probability = frequency / timeFrameDays;
	double rand = genRandNum();

	if (rand < probability) {

		return true;
	}
	else {
		return false;
	}
}

double Disease::genRandNum() {

	/*seeds random int*/
	double i = (double) rand() / RAND_MAX;
	cout << "random number is " << i << endl;
	return i;
}



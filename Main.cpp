#include "DaisyDeps.h"
#include <iostream>
#include <windows.h>
#include <thread>


using namespace std;


void drawGraphics() {

	Graphics* controller = new Graphics();
	
	controller->drawGraphics();
}


int main(int argc, char* argv[]) {

	ComplexCow* daisy = new ComplexCow(); //draws base cow with limited features if user doesn't define one

	thread t1{ drawGraphics };

	
	daisy->graze(10);

	daisy->digest(6, 0);

	daisy->digest(3, 1);

	daisy->graze(6);

	daisy->digest(7, 0);

	daisy->digest(5, 1);

	daisy->digest(2, 2);
	

	//daisy->graze(6);
	

	
		t1.join();
		

	return 0;
}







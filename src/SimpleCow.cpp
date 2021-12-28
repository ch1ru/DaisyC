#include "Cow.h"
#include "SimpleCow.h"
#include "Window.h"

using namespace std;

/*Constructor*/
SimpleCow::SimpleCow() {



	initialiseStomachs(); //assign stomach pointer to a 1 element array

	initialiseMoodLevels(); //sets mood levels to defaults

	setState("HUNGRY"); //sets the simple cow state to hungry

}

/*Sets initial values for the mood of the cow*/
void SimpleCow::initialiseMoodLevels() {

	/*Sets a mood for how full the stomach is*/
	emptyLevel = 0;
	hungryLevel = 3;
	contentLevel = 5;
	bloatedLevel = 7;
	fullLevel = 10;

}
/*Header file for complex cow*/
#ifndef COMPLEXCOW
#define COMPLEXCOW

#include <iostream>
#include "Cow.h"
#include "BackgroundImages.h"
#include "DrawImage.h"

using namespace std;

/*Defines a hungry cow with 4 stomachs... */
const class ComplexCow : public Cow {


public:

	ComplexCow();

	/*True if object is complex cow*/
	static bool isComplexCow;

	/*Flushes food ONLY from stomach specified*/
	void flush(int stomachIndex);

	/*Flushes food from all 4 stomachs*/
	void flush() override;

	/*Passes specified amount of grass from the stomach indexed if next stomach is empty*/
	void digest(int amount, int stomachIndex);



private:


	void initialiseStomachs() override;

	/*Sets initial values for the mood of the cow*/
	void initialiseMoodLevels();

	/*Alters state of all stomachs if contents change*/
	void refreshState() override;

};

#endif // !ComplexCow


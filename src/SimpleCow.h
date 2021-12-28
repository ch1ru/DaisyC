/*Simple cow with one stomach*/
#ifndef SIMPLECOW
#define SIMPLECOW

#include <iostream>
#include "Cow.h"

using namespace std;

class SimpleCow : public Cow {

private:

	void initialiseMoodLevels();


public:

	SimpleCow();

};

#endif // !SIMPLECOW

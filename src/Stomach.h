#ifndef STOMACH
#define STOMACH

#include <iostream>
#include <string>
#include "GameObject.h"
#include "DrawImage.h"

using namespace std;

class Stomach : GameObject {

private:

	struct stomach { 

		/*3 layers of the stomach*/
		DrawImage::drawingObject s, sPinkBacking, sGrassLevel;
	};


	void setDimAndPos(stomach &s, int h, int w, int x, int y);

	void setPath() override;

	void setGrassAndPinkBackingPath(stomach& s);

	BackgroundImages paths;


public:

	Stomach();

	~Stomach();

	stomach s0, s1, s2, s3;

};

#endif // ! STOMACH
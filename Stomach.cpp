#include "Stomach.h"

Stomach::Stomach() {

	setDimAndPos(s0, 120, 80, 200, 270); //h w x y
	setDimAndPos(s1, 120, 80, 290, 270);
	setDimAndPos(s2, 120, 80, 380, 270);
	setDimAndPos(s3, 120, 80, 470, 270);

	setPath();

}

Stomach::~Stomach() {


}

void Stomach::setDimAndPos(stomach &s, int h, int w, int x, int y) {

	s.s.imgDim.imageHeight = h;
	s.s.imgDim.imageWidth = w;
	s.s.imgPos.imagePosX = x;
	s.s.imgPos.imagePosY = y;

	s.sGrassLevel.imgDim.imageHeight = h;
	s.sGrassLevel.imgDim.imageWidth = w;
	s.sGrassLevel.imgPos.imagePosX = x;
	s.sGrassLevel.imgPos.imagePosY = y;

	s.sPinkBacking.imgDim.imageHeight = h;
	s.sPinkBacking.imgDim.imageWidth = w;
	s.sPinkBacking.imgPos.imagePosX = x;
	s.sPinkBacking.imgPos.imagePosY = y;
}

void Stomach::setPath() {

	setGrassAndPinkBackingPath(s0);
	setGrassAndPinkBackingPath(s1);
	setGrassAndPinkBackingPath(s2);
	setGrassAndPinkBackingPath(s3);

	s0.s.path = paths.s0Path;
	s1.s.path = paths.s1Path;
	s2.s.path = paths.s2Path;
	s3.s.path = paths.s3Path;

}

void Stomach::setGrassAndPinkBackingPath(stomach &s) {

	s.sGrassLevel.path = paths.grassPath;
	s.sPinkBacking.colour = { 200, 255, 255, 200};
	s.sPinkBacking.path = paths.pinkBackingPath;
}

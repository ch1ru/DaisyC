#include "GameObject.h"

GameObject::GameObject() {

	setDimAndPos(speechBubble, 150, 360, 230, 40); //height, length, xpos, ypos
	
	setDimAndPos(background, 500, 620, 0, 0);

	setDimAndPos(blinkBackground, 500, 620, 0, 0);

	itemsPlaqueYPos = -500;

	finalItemsYPos = 230;

	initItemObjects();

	initItemIcons();

	setPath();

}


DrawImage::drawingObject GameObject::getBackground() { 
	
	return background; 
}

DrawImage::drawingObject GameObject::getBlinkBackground() { 
	
	return blinkBackground; 
}


void GameObject::setPath() {

	background.path = backgroundPath.getBackgroundPath();

	blinkBackground.path = backgroundPath.getblinkBackgroundPath();

	speechBubble.path = backgroundPath.bubblePath;

	itemsButton.path = backgroundPath.itemsButtonPath;

	itemsPlaque.path = backgroundPath.plaquePath;

	moreGrazes.path = backgroundPath.moreGrazesPath;

	medicine.path = backgroundPath.medicinePath;

	magicSoup.path = backgroundPath.magicSoupPath;

	moreGrazesIcon.path = backgroundPath.moreGrazesPath;

	medicineIcon.path = backgroundPath.medicinePath;

	magicSoupIcon.path = backgroundPath.magicSoupPath;
}

void GameObject::initItemObjects() {

	setDimAndPos(itemsButton, 80, 80, 0, 420);

	setDimAndPos(itemsPlaque, 450, 380, 125, itemsPlaqueYPos);

	setDimAndPos(moreGrazes, 65, 65, 185, itemsPlaqueYPos + 540);

	setDimAndPos(medicine, 65, 65, 285, itemsPlaqueYPos + 540);

	setDimAndPos(magicSoup, 65, 65, 385, itemsPlaqueYPos + 540);
}


void GameObject::initItemIcons() {

	setDimAndPos(moreGrazesIcon, 20, 20, 350, 10);

	setDimAndPos(medicineIcon, 20, 20, 440, 10);

	setDimAndPos(magicSoupIcon, 20, 20, 530, 10);
}


void GameObject::setDimAndPos(DrawImage::drawingObject& obj, int h, int w, int x, int y) {

	obj.imgDim.imageHeight = h;
	obj.imgDim.imageWidth = w;
	obj.imgPos.imagePosX = x;
	obj.imgPos.imagePosY = y;
}



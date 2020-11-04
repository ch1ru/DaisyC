#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "Graphics.h"
#include "DrawImage.h"
#include "BackgroundImages.h"
#include "Window.h"

class GameObject {

private:

	int itemsPlaqueYPos;

	void initItemIcons();

	void initItemObjects();


public:

	DrawImage::drawingObject //images that are drawn to the window
		speechBubble,
		itemsButton,
		background,
		blinkBackground,
		itemsPlaque,
		moreGrazes,
		medicine,
		magicSoup,
		moreGrazesIcon,
		medicineIcon,
		magicSoupIcon;


	GameObject();

	double finalItemsYPos; //final y coord for plaque

	DrawImage::drawingObject getBackground(), getBlinkBackground();



protected:


	BackgroundImages backgroundPath;

	virtual void setPath();

	/*set dimentions and position of object*/
	void setDimAndPos(DrawImage::drawingObject& speechBubble, int h, int w, int x, int y);

};

#endif // ! GAMEOBJECT
//Draws objects to the window using the renderer from the window class
#ifndef DRAWIMAGE
#define DRAWIMAGE

#include "Window.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

using namespace std;


class DrawImage {

public:

	struct dimentions {
		double imageHeight;
		double imageWidth;
	};

	struct position {
		double imagePosX;
		double imagePosY;
	};

	struct drawingObject {

		position imgPos;
		dimentions imgDim;

		string path;
		SDL_Color colour;
	};


	DrawImage(drawingObject& image);

	~DrawImage();

	/*Draws rectangle to screen*/
	void draw();

private:

	double height;
	double width;
	double xPos;
	double yPos;

	SDL_Color col;

	SDL_Rect rect;

	void setDimentions(SDL_Rect&);

	void setPosition(SDL_Rect&);

	/*Sets image path*/
	SDL_Surface* loadImage(string);

	/*Creates window texture*/
	void createTexture(SDL_Surface*);

	SDL_Texture* texture = nullptr; //a created texture will be used by the renderer

};

#endif // !DRAWIMAGE;

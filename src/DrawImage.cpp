#include <iostream>
#include "DrawImage.h"
#include <SDL_image.h>
#include <SDL.h>


using namespace std;

DrawImage::DrawImage(drawingObject& image) {

	position objPos = image.imgPos;
	dimentions objDim = image.imgDim;


	height = objDim.imageHeight;
	width = objDim.imageWidth;
	xPos = objPos.imagePosX;
	yPos = objPos.imagePosY;

	draw(); //creates rectangle object and sets dimentions

	auto surface = loadImage(image.path); //the surface is the image being loaded

	createTexture(surface); //creates texture renderer for window

	SDL_FreeSurface(surface);
}


DrawImage::~DrawImage() {

	SDL_DestroyTexture(texture);
}


/*Draws rectangle to screen*/
void DrawImage::draw() {

	SDL_Rect rect;

	setDimentions(rect);

	setPosition(rect);

	SDL_RenderCopy(Window::renderer, texture, nullptr, &rect);

}

/*Sets height and width for thought bubble*/
void DrawImage::setDimentions(SDL_Rect& img) {
	img.w = width;
	img.h = height;
}

/*Sets x and y pos of speech bubble*/
void DrawImage::setPosition(SDL_Rect& img) {
	//upper left is (0,0)
	img.x = xPos;
	img.y = yPos;
}

/*Loads thought bubble image*/
SDL_Surface* DrawImage::loadImage(string path) {

	string imagePath = path;
	auto surface = IMG_Load(imagePath.c_str());
	if (!surface) {
		cerr << "Failed to load image" << endl;
	}
	else {
		return surface;
	}

}

void DrawImage::createTexture(SDL_Surface* surface) {

	DrawImage::texture = SDL_CreateTextureFromSurface(Window::renderer, surface);

	if (!texture) {
		cerr << "Failed to create texture" << endl;
	}
}



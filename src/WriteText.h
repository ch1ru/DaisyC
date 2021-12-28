#ifndef WRITETEXT
#define WRITETEXT

#include "Window.h"
#include <iostream>
#include <string>


using namespace std;

class WriteText {


public:

	static string speechBubbleText;

	WriteText();

	~WriteText();

	/*Draws text to window*/
	void Draw(string text, int xPos, int yPos, SDL_Color colour, float fSize, int wrapSize);


	
private:

	/*Initialises font*/
	TTF_Font* createFont(string font, int size);

	/*Creates text surface*/
	SDL_Surface* createTextSurface(TTF_Font* font, string& text, SDL_Color colour, int wrapSize);

	/*Create texture to deaw to renderer*/
	SDL_Texture* createTextTexture(SDL_Surface* surface);

	SDL_Rect textbox;

	TTF_Font* font;

	/*Surface of speechbubble font*/
	SDL_Surface* textSurface;

	/*Texture for drawing to renderer*/
	SDL_Texture* textTexture;

	void setTextboxDimentions(int xPos, int yPos);

	void freeResources();


};

#endif // !WRITETEXT


#include "WriteText.h"
#include <iostream>
#include <string>

using namespace std;


string WriteText::speechBubbleText = "";


WriteText::WriteText() {

	speechBubbleText = "";
}

WriteText::~WriteText() {

	freeResources();
}

/*Draws text to window*/
void WriteText::Draw(string text, int xPos, int yPos, SDL_Color colour = { 0, 0, 0 }, float fSize = 20, int wrapSize = 100) {

	font = createFont("Media/bertram.ttf", fSize); //initialises font

	textSurface = createTextSurface(font, text, colour, wrapSize); //creates surface for text

	textTexture = createTextTexture(textSurface); //creates texture for text

	setTextboxDimentions(xPos, yPos); //sets text to upper right inside speech bubble

	SDL_RenderCopy(Window::renderer, textTexture, NULL, &textbox);

	freeResources();

}

/*Deallocates SDL resources*/
void WriteText::freeResources() { 

	SDL_DestroyTexture(textTexture);

	SDL_FreeSurface(textSurface);

	TTF_CloseFont(font);
}


/*Sets dimentions for speechbubble textbox*/
void WriteText::setTextboxDimentions(int xPos, int yPos) {

	int textWidth = 0;
	int textHeight = 0;

	SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

	textbox = { xPos, yPos, textWidth, textHeight };

}

/*Initialises font*/
TTF_Font* WriteText::createFont(const string font, int size) {

	auto newFont = TTF_OpenFont(font.c_str(), size);
	
	return newFont;
}

/*Creates text surface*/
SDL_Surface* WriteText::createTextSurface(TTF_Font* font, string& text, SDL_Color colour, int wrapSize) {

	auto surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), colour, wrapSize);
	
	return surface;
}

/*Create texture to deaw to renderer*/
SDL_Texture* WriteText::createTextTexture(SDL_Surface* surface) {

	auto texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	
	return texture;
}



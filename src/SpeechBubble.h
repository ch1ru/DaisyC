//Used for user defined text to the speechbubble
#ifndef SPEECHBUBBLE
#define SPEECHBUBBLE

#include "Window.h"
#include "DrawImage.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "WriteText.h"
#include "Points.h"


using namespace std;

class SpeechBubble {


private:

	static bool isBubble;


public:

	SpeechBubble();

	~SpeechBubble();

	void write(string text); //write to bubble

	void clear(); //wipes text in bubble

	static bool checkIsBubble();
};

#endif // !SPEECHBUBBLE;


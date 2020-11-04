#include <iostream>
#include "SpeechBubble.h"
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Window.h"
#include "WriteText.h"


using namespace std;

bool SpeechBubble::isBubble = false;

SpeechBubble::SpeechBubble() {

	isBubble = true;
}


/*Output text to the thought bubble*/
void SpeechBubble::write(string text) {

	WriteText::speechBubbleText = text; //sets input text to be rendered 

	int satisfaction = Points::getSatisfaction();

	if (satisfaction < 3) {

		Points::setSatisfaction(satisfaction + 1);
	}
	
}

void SpeechBubble::clear() {

	WriteText::speechBubbleText = "";
}

bool SpeechBubble::checkIsBubble() {

	return isBubble;
}












//Creates window and poll events and establishes a renderer for this window
#ifndef WINDOW
#define WINDOW

#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SpeechBubble.h"
#include "BackgroundImages.h"
#include "DrawImage.h"
#include "Items.h"



using namespace std;

/*Defines the window size, position and initialises SDL image rendering*/
class Window {

public:

	Window();

	~Window();

	inline bool isWindowClosed() const { return windowClosed; }

	/*Defines events to interact with the window*/
	void pollEvents();

	double getWindowHeight() { return windowHeight; }

	double getWindowWidth() { return windowWidth; }

	/*Draws renderer to window*/
	void clear() const;

	struct button {
		int startX, endX, startY, endY; //start and end dimentions for button
		bool clicked = false;
		bool hover = false;
		string name;

	};

	button itemsBtn;

	button moreGrazesItemBtn;
	button medicineItemBtn;
	button magicSoupItemBtn;



private:

	Items gameItems;

	Items::Item moreGrazes, medicine, magicSoup;

	void initItemBtn();

	void initMoreGrazesItemBtn();

	void initMedicineItemBtn();

	void initMagicSoupSoupItemBtn();

	

	bool initialiseComponents();

	/*Creates window in the centre of screen*/
	void createWindow();

	bool checkCreatedWindow();

	bool initialiseImage();

	bool initialiseText();

	bool initialiseVideo();

	/*Initialises renderer for window*/
	void initialiseRenderer();

	/*Close window if escape key is pressed*/
	void escapeWindow(SDL_Event&);

	/*Set window icon*/
	void setWindowIcon(const string);


	/*fields*/

	/*true if window is closed*/
	bool windowClosed = false;

	/*Pointer for window*/
	SDL_Window* windowPtr = nullptr;

	/*Window is 600px high*/
	double windowHeight = 500;

	/*Window is 800px wide*/
	double windowWidth = 620;

	void drawCursor(double& mouseX, double& mouseY);

	bool hoverOver(button btn);

	void changeStateOfBtnsClicked();

	bool isBtnClicked(button btn);

	void updateItemsBtn();

	void updateMoreGrazesBtn();

	void updateMedicineBtn();

	void updateMagicSoupBtn();



public:


	/*Renderer for window*/
	static SDL_Renderer* renderer;

	void drawOverlay(SDL_Color col);



};

#endif // !WINDOW
#include <iostream>
#include <string>
#include <SDL.h>
#include "Window.h"
#include "SpeechBubble.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "BackgroundImages.h"
#include "GameObject.h"
#include "DrawImage.h"

using namespace std;

SDL_Renderer* Window::renderer = nullptr; //initialise renderer

//func prototype must stay in cpp since class needs to be fully defined to use drawingObject struct
void setBtnClickArea(Window::button& newBtn, DrawImage::drawingObject btn);  


double mouseX, mouseY;

/*Constructor*/
Window::Window() {

	windowClosed = !initialiseComponents(); //sets closed flag to true if not initialised

	setWindowIcon("Media/logo.gif"); //path to icon

	SDL_ShowCursor(SDL_DISABLE);

	initItemBtn();

	initMoreGrazesItemBtn();

	initMedicineItemBtn();

	initMagicSoupSoupItemBtn();

	moreGrazes = gameItems.getMoreGrazes();
	medicine = gameItems.getMedicine();
	magicSoup = gameItems.getMagicSoup();

}


/*Destructor for destroying window*/
Window::~Window() {

	cout << "Closing Window" << endl;
	SDL_DestroyWindow(windowPtr); //destroys window
	SDL_DestroyRenderer(renderer);
	TTF_Quit(); //uninitialises text renderer
	IMG_Quit();
	SDL_Quit(); //uninitialises SDL
}


/*Checks if window has been created*/
bool Window::checkCreatedWindow() {

	//if window has not been initialised
	if (windowPtr == nullptr) {
		cerr << "Failed to create window" << endl;
		return false;
	}
	else {
		return true;
	}
}

/*Draws a window*/
void Window::createWindow() {

	string windowTitle = "DaisyC";

	windowPtr = SDL_CreateWindow(
		windowTitle.c_str(), //converts string name into c string for SDL
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		windowWidth, windowHeight, 
		SDL_WINDOW_RESIZABLE
		);

	checkCreatedWindow(); 
}

/*Draws main game window*/
bool Window::initialiseComponents() {

	/*Initialises graphics components*/
	if (initialiseImage() && initialiseText() && initialiseVideo()) {

		createWindow(); //Creates SDL window centerscreen
		initialiseRenderer(); 
		return true;
	}
}

/*Check for mouse input*/
void Window::pollEvents() {

	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: //event on closing window

			windowClosed = true; 
			break;

		case SDL_KEYDOWN: //event on key press

			escapeWindow(event); //esc key
			break;

		case SDL_MOUSEMOTION: //event on moving mouse

			mouseX = event.motion.x;
			mouseY = event.motion.y;

			updateItemsBtn();

			updateMoreGrazesBtn();
			updateMedicineBtn();
			updateMagicSoupBtn();


			break;

		case SDL_MOUSEBUTTONDOWN: //event on click

			changeStateOfBtnsClicked();

			break;

		case SDL_MOUSEBUTTONUP:

			updateItemsBtn();

			updateMoreGrazesBtn();
			updateMedicineBtn();
			updateMagicSoupBtn();
	
			break;
		}


	}

	drawCursor(mouseX, mouseY);
}


void Window::updateItemsBtn() {

	if (hoverOver(itemsBtn)) {

		BackgroundImages::itemsButtonPath = "Media/ItemsBtn/sack_hover.png";
	}
	else {

		BackgroundImages::itemsButtonPath = "Media/ItemsBtn/sack_default.png";
	}
}

void Window::updateMoreGrazesBtn() {

	if (hoverOver(moreGrazesItemBtn) && itemsBtn.clicked) {

		Graphics::itemDescription = moreGrazes.description;
		
	}
	else {

	
	}
}

void Window::updateMedicineBtn() {

	if (hoverOver(medicineItemBtn) && itemsBtn.clicked) {

		Graphics::itemDescription = medicine.description;
	}
	else {

		
	}
}

void Window::updateMagicSoupBtn() {

	if (hoverOver(magicSoupItemBtn) && itemsBtn.clicked) {

		
		Graphics::itemDescription = magicSoup.description;
	}
	else {

		
	}
}


bool Window::hoverOver(button btn) {

	if (mouseX <= btn.endX && mouseX >= btn.startX) { //if in x coord range of button
		if (mouseY >= btn.startY && mouseY <= btn.endY) { //if in y coord range of button
			return true;
		}
	}

	return false; //mouse out of range

}

void Window::changeStateOfBtnsClicked() {

	if (isBtnClicked(itemsBtn)) {
		itemsBtn.clicked = !itemsBtn.clicked;
		BackgroundImages::itemsButtonPath = "Media/ItemsBtn/sack_clicked.png";
	}
	if (isBtnClicked(moreGrazesItemBtn)) {
		moreGrazesItemBtn.clicked = !moreGrazesItemBtn.clicked;
	}
	if (isBtnClicked(medicineItemBtn)) {
		medicineItemBtn.clicked = !medicineItemBtn.clicked;
	}
	if (isBtnClicked(magicSoupItemBtn)) {
		magicSoupItemBtn.clicked = !magicSoupItemBtn.clicked;
	}
}

bool Window::isBtnClicked(button btn) { //tests if mouse is hovering on item btn

	if (hoverOver(btn)) {
		return true;
	}
	else {
		return false;
	}
}

void Window::drawCursor(double& mouseX, double& mouseY) {

	BackgroundImages* cursorImage = new BackgroundImages();

	DrawImage::drawingObject cursor;

	cursor.imgDim.imageHeight = 55;
	cursor.imgDim.imageWidth = 55;

	cursor.imgPos.imagePosX = mouseX - 20;
	cursor.imgPos.imagePosY = mouseY - 20;

	cursor.path = cursorImage->cursorImagePath;

	DrawImage newCursor(cursor);
	newCursor.draw();
}

/*Check image component is initialised*/
bool Window::initialiseImage() {
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		cerr << "Failed to initialise SDL_Image" << endl;
		return false;
	}
	else {
		return true;
	}
}

/*Initialises ttf text rendering component*/
bool Window::initialiseText() {
	if (TTF_Init() != 0) {
		cerr << "Failed to initialise TTF" << endl;
		return false;
	}
	else {
		return true;
	}
}

/*Checks if video component (for drawing window) is initialised*/
bool Window::initialiseVideo() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "Failed to initialise video libraries" << endl;
		return false;
	}
	else {
		return true;
	}
}

/*initialise renderer*/
void Window::initialiseRenderer() {

	renderer = SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_PRESENTVSYNC); //creates renderer at low framerate

}

/*Close window if escape key is pressed*/
void Window::escapeWindow(SDL_Event& keystroke) {
	if (keystroke.key.keysym.sym == SDLK_ESCAPE) {
		windowClosed = true;
	}
}

/*Re-renders text and images to window*/
void Window::clear() const {


	SDL_RenderPresent(renderer);

	SDL_RenderClear(renderer);

}

/*Sets window icon*/
void Window::setWindowIcon(const string path) {

	SDL_Surface* icon = IMG_Load(path.c_str());
	SDL_SetWindowIcon(windowPtr, icon);
}

void Window::drawOverlay(SDL_Color col) {

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //allows for transparency by blending textures

	SDL_Rect rect;

	rect.w = windowWidth;
	rect.h = windowHeight;
	rect.x = 0;
	rect.y = 0;

	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

	SDL_RenderFillRect(renderer, &rect);

}


void Window::initItemBtn() {

	GameObject newBtn;

	auto btn = newBtn.itemsButton;

	setBtnClickArea(itemsBtn, btn);
	
}

void Window::initMoreGrazesItemBtn() {

	GameObject newBtn;

	auto btn = newBtn.moreGrazes;

	btn.imgPos.imagePosY = newBtn.finalItemsYPos;

	moreGrazesItemBtn.name = "more grazes";

	setBtnClickArea(moreGrazesItemBtn, btn);
}

void Window::initMedicineItemBtn() {

	GameObject newBtn;

	auto btn = newBtn.medicine;

	btn.imgPos.imagePosY = newBtn.finalItemsYPos;

	medicineItemBtn.name = "medicine";

	setBtnClickArea(medicineItemBtn, btn);
}

void Window::initMagicSoupSoupItemBtn() {

	GameObject newBtn;

	auto btn = newBtn.magicSoup;

	btn.imgPos.imagePosY = newBtn.finalItemsYPos;

	magicSoupItemBtn.name = "magic soup";

	setBtnClickArea(magicSoupItemBtn, btn);
}

void setBtnClickArea(Window::button& newBtn, DrawImage::drawingObject btn) {

	newBtn.startX = btn.imgPos.imagePosX;
	newBtn.endX = btn.imgPos.imagePosX + btn.imgDim.imageWidth;
	newBtn.startY = btn.imgPos.imagePosY;
	newBtn.endY = btn.imgPos.imagePosY + btn.imgDim.imageHeight;
}









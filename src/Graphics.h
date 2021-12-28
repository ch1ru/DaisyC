#ifndef GRAPHICS
#define GRAPHICS

#include "BackgroundImages.h"
#include "Window.h"
#include "DrawImage.h"
#include <thread>
#include "WriteText.h"
#include "TimeElapsed.h"
#include <vector>
#include "Timer.h"
#include "Points.h"
#include "Items.h"
#include "GameObject.h"
#include <string>
#include "Disease.h"

using namespace std;


class Graphics {

public:

	static bool Dead;
	static bool Exploded;

	/*Level of grass displayed in each stomach*/
	static double grassLevel[4];

	static vector<int>* foodQueue;
	static vector<char>* commandQueue;

	static bool grassLevelLock; //flag to ensure one stomach fills up at a time

	static bool moveFood;

	static string itemDescription;

	void drawGraphics();

	Graphics();


private:



	Timer* timer;

	Disease* illness = new Disease();

	static bool isSick;

	string backgroundPath;
	string blinkBackgroundPath;

	bool plaqueIsLowered;

	TimeElapsed timeZone;

	Points gamePoints;

	WriteText speechTextbox, daysPassedTextbox, score, moreGrazesIconText,
		medicineIconText, magicSoupIconText, descriptionText;

	Items gameItems;

	int itemsPlaqueCounter;

	Items::Item moreGrazes, medicine, magicSoup;

	int previousTimeInSeconds;

	BackgroundImages* background;

	long randomInterval;

	int grassLevelCounter;

	int pointsCounter;

	int blinkCounter;

	DrawImage::drawingObject itemPlaque;

	int moneyUpdateSpeed;


	/*Gets a random number between 1 and 6*/
	int generateRandomNumber();

	/*Returns true if cow needs to blink*/
	bool checkBlink(int &blinkCounter, long& randInterval);

	void drawBubbleAfterDeath(DrawImage& bubble, WriteText& textbox);

	void changeBackgroundImage(DrawImage::drawingObject backgroundObj, string newPath);

	double calcFinalHeightForPinkBacking(double grassLevel); 

	void renderPlaqueText();

	/*renders text for speechbubble, money and days passed*/
	void renderBackgroundText(); 

	void renderMoneyText();

	void renderSpeechText();

	void renderDaysPassedText();

	void drawWindow(Window& window);

	int calculateDaysPassed(int dayCounter);

	/*checks if day needs to be incremented*/
	void checkIncrementDay(TimeElapsed& days, Timer* timer); 

	/*declines food levels faster*/
	void cowIsSick(); 

	void adjustGrassLevel(DrawImage::dimentions &dim, double grassLevel, int stomachNumber);

	void transitionToNight(Window &newWindow, TimeElapsed &timeZone);

	/*Sets level of grass for graphics*/
	void setGrassLevel();

	/*Gets the proportion of grass in stomach as fraction*/
	double getProportionOfStomachFilled(int stomach);

	/*Return contents of stomach*/
	int getStomachContents(int stomach);

	void testIfFullOrEmpty(int stomach);

	void declineGrassLevel(int amount);

	void checkIfDigestRequired(Timer* timer, int &previousTimeInSeconds);

	/*updates timers*/
	void updateTimeElements(); 

	void updatePoints(Points& gamePoints);

	void checkUpdatePoints();

	void updateMoney(Points &gamePoints);

	void updateSatisfaction(Points &gamePoints);

	void drawIcons(DrawImage& newItemPlaque, DrawImage& newMoreGrazesItem, DrawImage& newMedicineItem);

	void changePlaqueHeightIfClicked(Timer* timer, int& counter, DrawImage::drawingObject &newItemsPlaque, Window& newWindow);

	void redrawPlaque(DrawImage::drawingObject &newItemsPlaque);

	void testIfPlaqueIsLowered(DrawImage::drawingObject& newItemsPlaque);

	void buyItemsIfClicked(Items &item, Window& newWindow);

	void renderIconText();

	/*refreshes item amounts*/
	void refreshItems();

	void renderItemPrices();

	void blinkRed(string& path, Timer* timer);

	void fade(Window& newWindow, SDL_Color col);

	/*brings cow back to life if dead*/
	void resurrect();

	void drawItemsButton();

	void drawItemDescription();

	void changeStomachLevels();

	void blink(DrawImage &backgroundImage, DrawImage &eyesClosedBackground);

	void testIfBlinkRed();

	void drawBubble(DrawImage& bubble);

	void testIfStomachIsFull(bool &isFull);

	/*calculates the alpha for the window overlay*/
	SDL_Color calcColourOfFade(int milliseconds);

	/*dealloc pointers*/
	void freePointers();

};

#endif // !GRAPHICS


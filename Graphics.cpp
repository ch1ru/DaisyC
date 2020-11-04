#include "DaisyDeps.h"
#include "TimeElapsed.h"
#include "WriteText.h"
#include "Timer.h"
#include "Stomach.h"
#include <iostream>
#include <thread>


using namespace std;

bool Graphics::Dead = false;
bool Graphics::Exploded = false;

bool Graphics::isSick = false;

double Graphics::grassLevel[4];




string Graphics::itemDescription = "";

vector<int>* Graphics::foodQueue = new vector<int>[4];
vector<char>* Graphics::commandQueue = new vector<char>[4];

bool Graphics::grassLevelLock = false;

Stomach stomach;

void drawItems(GameObject* newGameObject, DrawImage::drawingObject itemPlaque);


Graphics::Graphics() {

	for (int i = 0; i < 3; i++) {

		grassLevel[i] = 0;
	}

	timer = Timer::timerInstance();

	background = new BackgroundImages();

	randomInterval = generateRandomNumber(); //get initial random number

	grassLevelCounter = 0;

	pointsCounter = 0;

	plaqueIsLowered = false;

	blinkCounter = 0;

	moneyUpdateSpeed = 800;

	previousTimeInSeconds = 0;

	itemsPlaqueCounter = timer->getDeltaTime();

	

}

void Graphics::drawGraphics() {



	Window newWindow;
	
	string deadCowImage = background->deadCowImagePath;

	string explodedCowImage = background->explodedCowImagePath;

	bool isStomachFull = false;

	GameObject* newGameObject = new GameObject();

	itemPlaque = newGameObject->itemsPlaque;

	Uint8 alpha = 0;

	SDL_Color col = { 0, 0, 0, 0 };

	Timer* timerAfterExpl = Timer::getTimerAfterExpl();

	Timer* timerAfterDeath = Timer::getTimerAfterDeath();
	
	DrawImage backgroundImage(newGameObject->background);

	DrawImage eyesClosedBackground(newGameObject->blinkBackground);

	DrawImage bubble(newGameObject->speechBubble);

	DrawImage moreGrazesIcon(newGameObject->moreGrazesIcon);

	DrawImage medicineIcon(newGameObject->medicineIcon);

	DrawImage magicSoupIcon(newGameObject->magicSoupIcon);


	/*Instantiates just 1 stomach for a simple cow*/
	DrawImage s0(stomach.s0.s);
	DrawImage s1(stomach.s1.s);
	DrawImage s2(stomach.s2.s);
	DrawImage s3(stomach.s3.s);

	/*grass background for stomach*/
	DrawImage s1grassTexture(stomach.s1.sGrassLevel);
	DrawImage s0grassTexture(stomach.s0.sGrassLevel);
	DrawImage s2grassTexture(stomach.s2.sGrassLevel);
	DrawImage s3grassTexture(stomach.s3.sGrassLevel);


	//main loop
	while (!newWindow.isWindowClosed()) {


		updateTimeElements();

		changeStomachLevels();

		blink(backgroundImage, eyesClosedBackground);

		checkUpdatePoints();


			DrawImage s1pinkBacking(stomach.s1.sPinkBacking);
			DrawImage s0pinkBacking(stomach.s0.sPinkBacking);
			DrawImage s2pinkBacking(stomach.s2.sPinkBacking);
			DrawImage s3pinkBacking(stomach.s3.sPinkBacking);

			s1grassTexture.draw();
			s1pinkBacking.draw();
			s1.draw();

			/*if cow is complex cow*/
			if (ComplexCow::isComplexCow) {

				//Draw additional stomachs
				s0grassTexture.draw();
				s2grassTexture.draw();
				s3grassTexture.draw();

				s0pinkBacking.draw();
				s2pinkBacking.draw();
				s3pinkBacking.draw();

				s0.draw();
				s2.draw();
				s3.draw();
			}


			testIfStomachIsFull(isStomachFull);


			if (Graphics::Exploded && isStomachFull) { //if exploded

				timer->update();

				int milliseconds = timer->getDeltaTime() + 1;

				timerAfterExpl->setTimeAfterDeathCounter(milliseconds);

				changeBackgroundImage(newGameObject->getBackground(), explodedCowImage);

				col = calcColourOfFade(milliseconds - timerAfterExpl->getTimeAfterDeathCounter());

				moneyUpdateSpeed = 10;

				if (milliseconds - timerAfterExpl->getTimeAfterDeathCounter() > 4000) {

					/*Displays speech bubble shortly after cow dies*/
					drawBubbleAfterDeath(bubble, speechTextbox);

				}
			}
			else if (Graphics::Dead && !Graphics::Exploded) {

				timer->update();

				int milliseconds = timer->getDeltaTime() + 1;

				timerAfterDeath->setTimeAfterDeathCounter(milliseconds);

				Items::Item magicSoup = gameItems.getMagicSoup();

				if (magicSoup.amount > 0) {

					resurrect();

					timerAfterDeath->reset();

				}
				else {

					col = calcColourOfFade(milliseconds - timerAfterDeath->getTimeAfterDeathCounter());

					if (milliseconds - timerAfterDeath->getTimeAfterDeathCounter() > 3000) {

						changeBackgroundImage(newGameObject->getBlinkBackground(), deadCowImage);

						moneyUpdateSpeed = 10;
					}
					if (milliseconds - timerAfterDeath->getTimeAfterDeathCounter() > 5000) {

						/*Displays speech bubble shortly after cow dies*/
						drawBubbleAfterDeath(bubble, speechTextbox);
					}
				}
			}

			

			testIfBlinkRed();

			drawItemsButton();

			drawBubble(bubble);

			renderBackgroundText();

			drawIcons(moreGrazesIcon, medicineIcon, magicSoupIcon);

			changePlaqueHeightIfClicked(timer, itemsPlaqueCounter, itemPlaque, newWindow);

			refreshItems();

			drawItems(newGameObject, itemPlaque);

			buyItemsIfClicked(gameItems, newWindow);

			transitionToNight(newWindow, timeZone);

		    fade(newWindow, col);

		    renderPlaqueText();
			
            drawWindow(newWindow);
		
			
	}

	freePointers();

}


/*Gets a random number between 1 and 6*/
int Graphics::generateRandomNumber() {

	srand(time(NULL)); //seeds random number based on time
	unsigned int randomNumber = rand() % 6 + 1; //creates random number between 1 and 6
	return randomNumber;
}


/*Returns true if cow needs to blink*/
bool Graphics::checkBlink(int &blinkCounter, long& randomInterval) {

	
		if ((timer->getDeltaTime() - blinkCounter >= randomInterval * 1000) && !Graphics::Exploded) {
			
			randomInterval = generateRandomNumber();

			blinkCounter = timer->getDeltaTime();
			
			return true;
		}
		else if (timer->getDeltaTime() - blinkCounter > 90) {

			return false;
		}
}


void Graphics::changeBackgroundImage(DrawImage::drawingObject backgroundObj, string newPath) {

	backgroundObj.path = newPath;

	DrawImage backgroundImage(backgroundObj);

	backgroundImage.draw();
}




void Graphics::drawBubbleAfterDeath(DrawImage& bubble, WriteText& textbox) {

	string text = ""; //message to display
	int fontSize = 20;
	int wrapSize = 300;

	if (Graphics::Exploded) {

		text = "Pop goes Daisy the coo";
	}
	else {

		text = "Not much grass down 'ere";
	}

	bubble.draw(); //draw new bubble

	textbox.Draw(text, 285, 90, { 0, 0, 0 }, fontSize, wrapSize); //re-renders current text
}


void Graphics::renderPlaqueText() {

		renderIconText();

		renderItemPrices();

		drawItemDescription();
		
}

void Graphics::renderIconText() {

	string moreGrazesStr = to_string(moreGrazes.amount);
	string medicineStr = to_string(medicine.amount);
	string magicSoupStr = to_string(magicSoup.amount);

	int fontsize = 20;
	int wrapSize = 100;

	moreGrazesIconText.Draw(moreGrazesStr, 380, 10, { 0, 0, 0 }, fontsize, wrapSize);

	medicineIconText.Draw(medicineStr, 470, 10, { 0, 0, 0 }, fontsize, wrapSize);

	magicSoupIconText.Draw(magicSoupStr, 560, 10, { 0, 0, 0 }, fontsize, wrapSize);

}

void Graphics::renderItemPrices() {

	int height = itemPlaque.imgPos.imagePosY;
	int offset = 380;
	int fontSize = 24;
	int wrapSize = 50;

	string moreGrazesPriceStr = "$" + to_string(moreGrazes.cost);
	string medicinePriceStr = "$" + to_string(medicine.cost);
	string magicSoupPriceStr = "$" + to_string(magicSoup.cost);

	moreGrazesIconText.Draw(moreGrazesPriceStr, 194, height + offset, { 200, 0, 0 }, fontSize, wrapSize);

	medicineIconText.Draw(medicinePriceStr, 294, height + offset, { 200, 0, 0 }, fontSize, wrapSize);

	magicSoupIconText.Draw(magicSoupPriceStr, 394, height + offset, { 200, 0, 0 }, fontSize, wrapSize);
}

void Graphics::renderBackgroundText() {

	renderMoneyText();

	renderDaysPassedText();

	renderSpeechText();
}


void Graphics::renderMoneyText() {



	float money = round(gamePoints.getDollars() * 100) / 100;

	int moneyFontSize = 24;

	int wrapSize = 200;

	string moneyText = "$" + to_string(money);

	int pos = moneyText.find(".") + 3;

	moneyText.erase(pos);

	score.Draw(moneyText, 200, 10, { 200, 0, 0 }, moneyFontSize, wrapSize);

}


void Graphics::renderSpeechText() {

	string speechText;
	int fontSize = 20;
	int wrapSize = 300;
	
	if (!Graphics::Dead) {
		speechText = WriteText::speechBubbleText;
	}

	speechTextbox.Draw(speechText, 290, 75, { 0, 0, 0 }, fontSize, wrapSize); //Draws text to speechbubble
}

void Graphics::renderDaysPassedText() {

	int dayCountFontSize = 24;

	int daysPassed = calculateDaysPassed(timeZone.getDayCounter()) + 1;

	string daysPassedText = to_string(daysPassed);

	int wrapSize = 100;

	daysPassedTextbox.Draw("Day " + daysPassedText, 10, 10, { 255, 120, 0 }, dayCountFontSize, wrapSize);
}


void Graphics::drawWindow(Window& window) {

	
	window.pollEvents(); //check for poll events
	window.clear(); //present renderer onto window
}


int Graphics::calculateDaysPassed(int dayCounter) {

	int numOfDays = floor(dayCounter / 2);

	return numOfDays;
}


void Graphics::checkIncrementDay(TimeElapsed& days, Timer* timer) {

	int minutes = round(timer->getDeltaTime() / 50000) + 1;

	if (days.getLastTimeMinutes() == NULL) {

		days.setLastTimeMinutes(minutes);

	}

	if (days.getLastTimeMinutes() == minutes - 1) {

		days.incrementDayCounter();

		days.setLastTimeMinutes(minutes);

	}

	/*if new day*/
	if (days.getDayCounter() % 2 == 0 && !days.getTransitioned() && days.getDayCounter() != 0) { 

		days.incrementTime();

		cowIsSick();
	
	}

	

}

void Graphics::cowIsSick() {

	if (illness->getIsSick(7)) {

	cout << "daisy is sick" << endl;


		if (medicine.amount > 0) {
			isSick = false;
			medicine.amount--;
			cout << "Daisy is healed!" << endl;
		}
		else {

			isSick = true;

			stomach.s0.sPinkBacking.path = background->paleBackingPath;
			stomach.s1.sPinkBacking.path = background->paleBackingPath;
			stomach.s2.sPinkBacking.path = background->paleBackingPath;
			stomach.s3.sPinkBacking.path = background->paleBackingPath;
		}

	}
	else {

		stomach.s0.sPinkBacking.path = background->pinkBackingPath;
		stomach.s1.sPinkBacking.path = background->pinkBackingPath;
		stomach.s2.sPinkBacking.path = background->pinkBackingPath;
		stomach.s3.sPinkBacking.path = background->pinkBackingPath;

		isSick = false;

	}
}

void Graphics::adjustGrassLevel(DrawImage::dimentions& dim, double grassLevel, int stomachNumber) {

	setGrassLevel();

	if (dim.imageHeight > round(calcFinalHeightForPinkBacking(grassLevel))) { //if level has increased since last loop

		if (stomachNumber > 0) {

			if (!commandQueue[stomachNumber - 1].empty()) {

				if (commandQueue[stomachNumber - 1][0] == 'D' || commandQueue[stomachNumber - 1].size() == 1) {

					dim.imageHeight--;

					updateSatisfaction(gamePoints);
				}
			}
			
		}
		else {

			dim.imageHeight--;

			if (commandQueue[stomachNumber][0] == 'G') {
				gameItems.updateGrazes();
			}
		}
		
		
			
	}
	else if (dim.imageHeight < round(calcFinalHeightForPinkBacking(grassLevel))) { //if level has decreased since last loop

		dim.imageHeight++;

		updateSatisfaction(gamePoints);

		if(commandQueue[stomachNumber].size() > 1) {

			if (commandQueue[stomachNumber][0] == 'W') {
			
				commandQueue[stomachNumber].erase(commandQueue[stomachNumber].begin());
				
			}
		}
	}
	else {

		if (foodQueue[stomachNumber].size() > 1) {

			foodQueue[stomachNumber].erase(foodQueue[stomachNumber].begin());
		}
		if (commandQueue[stomachNumber].size() > 1) {

			commandQueue[stomachNumber].erase(commandQueue[stomachNumber].begin());

		}
		

	}

	
}

/*Sets level of grass for graphics*/
void Graphics::setGrassLevel() {

	if (ComplexCow::isComplexCow) {
		grassLevel[0] = getProportionOfStomachFilled(0);
		grassLevel[1] = getProportionOfStomachFilled(1);
	}
	else {
		grassLevel[1] = getProportionOfStomachFilled(1);
		grassLevel[0] = getProportionOfStomachFilled(0);
	}
	
	grassLevel[2] = getProportionOfStomachFilled(2);
	grassLevel[3] = getProportionOfStomachFilled(3);

}

/*Gets the proportion of grass in stomach as fraction*/
double Graphics::getProportionOfStomachFilled(int stomach) {

	double proportion = 0;

	proportion = 1.0 * getStomachContents(stomach) / 10;

	if (proportion < 0) {
		proportion = 0;
	}

	return proportion;
}


/*Return contents of stomach*/
int Graphics::getStomachContents(int stomach) {

	if (!foodQueue[stomach].empty()) {

		testIfFullOrEmpty(stomach);

		return foodQueue[stomach][0]; //Single Stomach

	}
	else {
		return 0;
	}


}

void Graphics::testIfFullOrEmpty(int stomach) {

	if (!foodQueue[stomach].empty()) {

		if (foodQueue[stomach][0] >= 10) {

			Cow::isStomachFull[stomach] = true;
		}
		else {

			Cow::isStomachFull[stomach] = false;
		}

		if (foodQueue[stomach][0] <= 0) {

			Cow::isStomachEmpty[stomach] = true;
		}
		else {

			Cow::isStomachEmpty[stomach] = false;
		}
	}
}

double Graphics::calcFinalHeightForPinkBacking(double grassLevel) {

	int scaleFactor = 110; //scales up from decimal

	int offset = 6;

	double pinkBackingFinalHeight = (1 - grassLevel) * scaleFactor + offset;

	return pinkBackingFinalHeight;
}


void Graphics::transitionToNight(Window& newWindow, TimeElapsed& timeZone) {


	double currentTransparencySF = timeZone.getTranparencyScaleFactor();

	Uint8 darkness = 170 * currentTransparencySF;


	if (!timeZone.getIsDay()) { //transition to night

		timeZone.setTransparencyScaleFactor(currentTransparencySF += 0.01);

		newWindow.drawOverlay({ 10, 10, 200, darkness });

	}
	else {
		
		if (currentTransparencySF > 0.01) { //transition to morning

			timeZone.setTransparencyScaleFactor(currentTransparencySF -= 0.01);

			newWindow.drawOverlay({ 10, 10, 200, darkness });
		}
	}

}



void Graphics::checkIfDigestRequired(Timer* timer, int &previousTimeInSeconds) {

	int seconds = round(timer->getDeltaTime() / 500);

	if (seconds % 18 == 0 && seconds != 0) {

		if (seconds != previousTimeInSeconds) {

			if (isSick) {

				declineGrassLevel(2);
			}
			else {

				declineGrassLevel(1);
			}
			

		}
		previousTimeInSeconds = seconds;
	}
	
}

void Graphics::declineGrassLevel(int amount) {

	int numberOfStomachs;

	if (ComplexCow::isComplexCow) {
		numberOfStomachs = 4;
	}
	else {
		numberOfStomachs = 1;
	}
	
	for (int i = 0; i < numberOfStomachs; i++) {

		if (Cow::isStomachEmpty[i]) {
		
			Graphics::Dead = true;
		}

		if (foodQueue[i].empty()) {

			foodQueue[i].push_back(-amount);
			
		}
		else {

			foodQueue[i].push_back(foodQueue[i].back() - amount);
		}
	}
}

void Graphics::updateTimeElements() {

	timer->update();

	checkIncrementDay(timeZone, timer);

}

void Graphics::updatePoints(Points &gamePoints) {

	

	updateMoney(gamePoints);

}

void Graphics::updateMoney(Points &gamePoints) {

	if (Graphics::Dead || Graphics::Exploded) {
		gamePoints.decrementDollars();
	}
	else {
		gamePoints.incrementDollars(gamePoints.getSatisfaction());
	}
	
}

void Graphics::updateSatisfaction(Points &gamePoints) {

	int satisfaction = Points::getSatisfaction();

	if (Cow::isSatisfied == false && (satisfaction >= 1 && satisfaction <= 5)) {

		Points::setSatisfaction(satisfaction - 1);
		
	}
	else {
		Points::setSatisfaction(satisfaction + 1);
	}
}

void drawItems(GameObject* newGameObject, DrawImage::drawingObject itemPlaque) {

	
	float height = itemPlaque.imgPos.imagePosY;
	float offset = 300;

	newGameObject->moreGrazes.path = BackgroundImages::moreGrazesPath;
	newGameObject->medicine.path = BackgroundImages::medicinePath;
	newGameObject->magicSoup.path = BackgroundImages::magicSoupPath;

	newGameObject->moreGrazes.imgPos.imagePosY = height + offset;
	newGameObject->medicine.imgPos.imagePosY = height + offset;
	newGameObject->magicSoup.imgPos.imagePosY = height + offset;

	DrawImage MoreGrazesItem(newGameObject->moreGrazes);
	DrawImage MedicineItem(newGameObject->medicine);
	DrawImage MagicSoupItem(newGameObject->magicSoup);

	MoreGrazesItem.draw();
	MedicineItem.draw();
	MagicSoupItem.draw();
}

void Graphics::drawIcons(DrawImage& moreGrazesIcon, DrawImage& medicineIcon, DrawImage& magicSoupIcon) {

	moreGrazesIcon.draw();
	medicineIcon.draw();
	magicSoupIcon.draw();
}

void Graphics::changePlaqueHeightIfClicked(Timer* timer, int &counter, DrawImage::drawingObject &newItemsPlaque, Window& newWindow) {



		if (timer->getDeltaTime() - counter > 1) {

			
			if(!plaqueIsLowered && newWindow.itemsBtn.clicked) {
				
				if (timeZone.getIsDay()) {
					newItemsPlaque.imgPos.imagePosY += 16;
				}
				else {
					cerr << "Can't shop at night" << endl;
					newWindow.itemsBtn.clicked = false;
				}
				
			}
			else if (plaqueIsLowered && (!newWindow.itemsBtn.clicked || !timeZone.getIsDay())) {


				newItemsPlaque.imgPos.imagePosY -= 16;

			}

			counter = timer->getDeltaTime();
			testIfPlaqueIsLowered(newItemsPlaque);
			redrawPlaque(newItemsPlaque);
		}
	


}

void Graphics::redrawPlaque(DrawImage::drawingObject &newItemsPlaque) {
	
	DrawImage itemsPlaque(newItemsPlaque);
	itemsPlaque.draw();
}

void Graphics::testIfPlaqueIsLowered(DrawImage::drawingObject& newItemsPlaque) {

	if (newItemsPlaque.imgPos.imagePosY > -70) {

		plaqueIsLowered = true;
	}
	else if (newItemsPlaque.imgPos.imagePosY < -500) {
		plaqueIsLowered = false;
	
	}
}


void Graphics::buyItemsIfClicked(Items& item, Window& newWindow) {

	if (newWindow.moreGrazesItemBtn.clicked) {
		item.buyMoreGrazes();
		newWindow.moreGrazesItemBtn.clicked = false;
	}
	else if (newWindow.medicineItemBtn.clicked) {
		item.buyMedicine();
		newWindow.medicineItemBtn.clicked = false;
	}
	else if (newWindow.magicSoupItemBtn.clicked) {
		item.buyMagicSoup();
		newWindow.magicSoupItemBtn.clicked = false;
	}
}


void Graphics::refreshItems() {

	moreGrazes = gameItems.getMoreGrazes();

	medicine = gameItems.getMedicine();

	magicSoup = gameItems.getMagicSoup();
}


void Graphics::blinkRed(string &path, Timer* timer) {

	int ticks = round(timer->getDeltaTime() / 250);

	if (ticks % 2 == 0 && ticks != 0) {

		path = background->pinkBackingPath;

	}
	else {

		path = background->redBackingPath;
		
	}
}


void Graphics::fade(Window& newWindow, SDL_Color col) {

	newWindow.drawOverlay(col);
}


void Graphics::resurrect() {

	Graphics::Dead = false;

	for (int i = 0; i < 4; i++) {

		Graphics::foodQueue[i].push_back(10);

	}

	gameItems.decrementMagicSoup();

}

void Graphics::drawItemsButton() {

	GameObject* gameObj = new GameObject();
	DrawImage itemsButton(gameObj->itemsButton);
	itemsButton.draw();

}

void Graphics::drawItemDescription() {

	int height = itemPlaque.imgPos.imagePosY + 210;
	float fontSize = 18;
	string text = itemDescription.c_str();
	int wrapSize = 264;

	descriptionText.Draw(text, 190, height, { 0, 0, 0 }, fontSize, wrapSize);

}

void Graphics::changeStomachLevels() {

	if (timer->getDeltaTime() - grassLevelCounter > 40) { //if 40ms elapsed

		grassLevelCounter = timer->getDeltaTime();

		checkIfDigestRequired(timer, previousTimeInSeconds);

		if (ComplexCow::isComplexCow) {

			adjustGrassLevel(stomach.s0.sPinkBacking.imgDim, grassLevel[0], 0);

			adjustGrassLevel(stomach.s1.sPinkBacking.imgDim, grassLevel[1], 1);
		}
		else {
			adjustGrassLevel(stomach.s0.sPinkBacking.imgDim, grassLevel[1], 1);

			adjustGrassLevel(stomach.s1.sPinkBacking.imgDim, grassLevel[0], 0);
		}


		adjustGrassLevel(stomach.s2.sPinkBacking.imgDim, grassLevel[2], 2);

		adjustGrassLevel(stomach.s3.sPinkBacking.imgDim, grassLevel[3], 3);


	}

	
}

void Graphics::blink(DrawImage &backgroundImage, DrawImage &eyesClosedBackground) {

	if (checkBlink(blinkCounter, randomInterval) || !timeZone.getIsDay()) {
		eyesClosedBackground.draw();
	}
	else {
		backgroundImage.draw();

	}
}

void Graphics::testIfBlinkRed() {
	
	if (timer->getDeltaTime() - grassLevelCounter > 10) {
		for (int i = 0; i < 4; i++) {

			if (grassLevel[i] <= 0.1) {
				
				switch (i) {

				case 0:
					blinkRed(stomach.s0.sPinkBacking.path, timer);
					break;
				case 1:
					blinkRed(stomach.s1.sPinkBacking.path, timer);
					break;
				case 2:
					blinkRed(stomach.s2.sPinkBacking.path, timer);
					break;
				case 3:
					blinkRed(stomach.s3.sPinkBacking.path, timer);
					break;
				}
			}
		}
	}
}

void Graphics::drawBubble(DrawImage &bubble) {

	/*Draw bubble and stomach components for simple cow*/
	if (SpeechBubble::checkIsBubble() && !Graphics::Dead) {
		bubble.draw();
	}
}

void Graphics::testIfStomachIsFull(bool &isFull) {
	//if any stomach is full
	if (stomach.s0.sPinkBacking.imgDim.imageHeight < 7 || stomach.s1.sPinkBacking.imgDim.imageHeight < 7 ||
		stomach.s2.sPinkBacking.imgDim.imageHeight < 7 || stomach.s3.sPinkBacking.imgDim.imageHeight < 7) {

		isFull = true;

	}
}


SDL_Color Graphics::calcColourOfFade(int milliseconds) {

	Uint8 alpha = 0;
	SDL_Color col = { 0, 0, 0, 0 };

	if (Graphics::Exploded) {

		if (milliseconds < 2000) {

			int percentage = milliseconds * 18 / 200;

			alpha = 250 - percentage;

			col = { 255, 255, 255, alpha };

		}
		else {

			alpha = 0;
		}

	}
	else if (!Graphics::Exploded) {

		if (milliseconds < 3500) {

			alpha = milliseconds / 12;

			col = { 0, 0, 0, alpha };

		}
	
	}
	

	

	return col;
}


void Graphics::freePointers() {

	delete background;
	delete illness;
	delete timer;
}

void Graphics::checkUpdatePoints() {

	if (timer->getDeltaTime() - pointsCounter > moneyUpdateSpeed) {

		pointsCounter = timer->getDeltaTime();

		updatePoints(gamePoints);

	}
}

/*Implementation file for all Cow definitions*/
#include "Cow.h"
#include <iostream>
#include <string>
#include "BackgroundImages.h"
#include "Graphics.h"
#include "DrawImage.h"
#include "Soundfx.h"

using namespace std;

bool Cow::isStomachFull[4];
bool Cow::isStomachEmpty[4];

bool Cow::isSatisfied = false;

int Cow::grazesLeft = 12;

Items gameItems;

/*Constructor*/
Cow::Cow() {

	BackgroundImages::setBackgroundPath("Media/cow_eyes_open.png");
	BackgroundImages::setBlinkBackgroundPath("Media/cow_eyes_shut.png");

	initialiseStomachs();

}

/*Returns true if Cow is dead*/
bool Cow::isDead() {
	if (stateOfCow == DEAD) {
		return true;
	}
	else {
		return false;
	}
}

/*Returns true if Cow is hungry*/
bool Cow::isHungry() {
	if (stateOfCow == HUNGRY) {
		return true;
	}
	else {
		return false;
	}
}

/*Returns true if Cow is content*/
bool Cow::isContent() {
	if (stateOfCow == CONTENT) {
		return true;
	}
	else {
		return false;
	}
}

/*Returns true if Cow is bloated*/
bool Cow::isBloated() {
	if (stateOfCow == BLOATED) {
		return true;
	}
	else {
		return false;
	}
}


/*Returns true if Cow is exploded*/
bool Cow::isExploded() {

	if (stateOfCow == EXPLODED) {
		return true;
	}
	else {
		return false;
	}
}

/*Tests if Cow is alive*/
bool Cow::isAlive() {
	return !isDead() && !isExploded();
}

/*Udpade graphical display*/
void Cow::updateGraphics() {
	//if cow is dead
	if (stateOfCow == DEAD) {
		Graphics::Dead = true; //Dead flag set
	}
	else if (stateOfCow == EXPLODED) {
		Graphics::Exploded = true; //Exploded flag set
		Graphics::Dead = true;
	}
}


/*Flush all stomachs*/
void Cow::flush() {
	Soundfx spx;
	if (!isDead() && !isExploded()) { //checks if Cow is alive
		if (stomachArrayPtr[0] == 0 && Graphics::foodQueue->size() <= 1) {
			killCow(); //kills cow if trying to flush empty stomach
			
		}
		else {

			cout << "Flushing stomach 0" << endl;
			stomachArrayPtr[0] = 0;

			Graphics::foodQueue[0].push_back(stomachArrayPtr[0]);
			Graphics::commandQueue[0].push_back('F');
			
			refreshState();

		}

	}
	updateGraphics();
}



/*Feed Cow 1 piece of grass... Yum*/
void Cow::graze() {
	if ((!isDead() && !isExploded()) && grazesLeft > 0) { //checks if Cow is alive

		stomachArrayPtr[0]++;
		Graphics::foodQueue[0].push_back(stomachArrayPtr[0]);
		Graphics::commandQueue[0].push_back('G');
		grazesLeft--;
		
		refreshState();
		updateGraphics();

	
	}
}

/*Feed Cow specified pieces of grass... very yum*/
void Cow::graze(int mouthfullsOfGrass) {
	if ((!isDead() && !isExploded()) && grazesLeft > 0) { //checks if Cow is alive

		stomachArrayPtr[0] += mouthfullsOfGrass;
		Graphics::foodQueue[0].push_back(stomachArrayPtr[0]);
		Graphics::commandQueue[0].push_back('G');
		grazesLeft -= mouthfullsOfGrass;
		
		refreshState();
		updateGraphics();

		
	}
}

/*moves food from parameter given stomach to the next*/
void Cow::digest(int amount) {

	if (!isDead() && !isExploded()) { //checks if Cow is alive

		if (stomachArrayPtr[0] == 0 && Graphics::foodQueue->size() <= 1) {
			killCow();
		}
		else {

			cout << "Digesting stomach 0" << endl;

			stomachArrayPtr[0] -= amount;
			Graphics::foodQueue[0].push_back(stomachArrayPtr[0]);
			Graphics::commandQueue[0].push_back('D');
			Graphics::commandQueue[0].push_back('W'); //wait

			refreshState();
			updateGraphics();
		}
		
	}
}

/*Alters state if stomach contents change*/
void Cow::refreshState() {
	/*FOR 1 STOMACH ONLY - Override exists for complex cow*/
	Soundfx spx;
	int s0;

	if (!Graphics::foodQueue[0].empty()) {

		/*s0 is the cow's first stomach*/
		s0 = stomachArrayPtr[0];
	}
	


	if (s0 < emptyLevel) {
		killCow();
	}
	else if (s0 < contentLevel && s0 >= emptyLevel) {
		setState("HUNGRY");
		spx.playMooSound();
		isSatisfied = false;
	}
	else if (s0 < bloatedLevel && s0 >= contentLevel) {
		setState("CONTENT");
		isSatisfied = true;
	}
	else if (s0 <= fullLevel && s0 >= bloatedLevel) {
		setState("BLOATED");
		spx.playMooSound();
		isSatisfied = false;
	}
	else {
		setState("EXPLODED");
		spx.playExplSound();
	}

	
}



/*Initialises 1st stomach element to 0*/
void Cow::initialiseStomachs() {

	stomachArrayPtr = new int[1];
	stomachArrayPtr[0] = 0;

	Cow::isStomachEmpty[0] = true;

	
}

void Cow::setThought(string newThought) {
	currentThought = Thoughts::setThought(newThought);

	//refreshview
}


/*Kills the cow*/
void Cow::killCow() {
	Soundfx spx;
	setState("DEAD"); //sets the state to dead
	spx.playDeadSound(); 
	updateGraphics(); //updates graphics display
}

/*Sets the state of the cow*/
void Cow::setState(string state) { //Sets the state of cow

	if (state == "DEAD") {
		stateOfCow = DEAD;
		cout << "RIP" << endl;
	}
	else if (state == "HUNGRY") {
		stateOfCow = HUNGRY;
	}
	else if (state == "CONTENT") {
		stateOfCow = CONTENT;
	}
	else if (state == "BLOATED") {
		stateOfCow = BLOATED;
	}
	else if (state == "EXPLODED") {
		stateOfCow = EXPLODED;
		cout << "KABOOM" << endl;
	}
}


void Cow::buyMoreGrazes() {

	Items::Item moreGrazes = gameItems.getMoreGrazes();
	
	if (Points::getDollars() >= moreGrazes.cost) {

		cout << "Bought more Grazes" << endl;
	}
}

void Cow::buyMedicine() {

	Items::Item medicine = gameItems.getMedicine();

	if (Points::getDollars() >= medicine.cost) {

		cout << "Bought Medicine" << endl;
	}
}

void Cow::buyMagicSoup() {

	Items::Item magicSoup = gameItems.getMagicSoup();

	if (Points::getDollars() >= magicSoup.cost) {
		
		cout << "Bought Magic Soup" << endl;
	}
}





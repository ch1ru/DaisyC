#include "Cow.h"
#include "ComplexCow.h"
#include <iostream>
#include "DrawImage.h"
#include "Soundfx.h"
#include "Graphics.h"

using namespace std;

/*fields*/

bool ComplexCow::isComplexCow = false;


/*Constructor*/
ComplexCow::ComplexCow() {

	Graphics* controller = new Graphics();

	grazesLeft = 48;

	/*Initialise array of 4 stomachs*/
	initialiseStomachs();

	/*initialise mood levels*/
	initialiseMoodLevels();

	setState("HUNGRY"); //sets the cow to a hungry state

	isComplexCow = true;
}

/*Flushes food ONLY from stomach specified*/
void ComplexCow::flush(int stomachIndex) {

	if (!isDead() && !isExploded()) {
		//flush stomach stomachNumber
		if (stomachArrayPtr[stomachIndex] == 0 && Graphics::foodQueue->size() <= 1) {

			killCow(); //kills daisy and plays sound effect
		}
		else {
			
			stomachArrayPtr[stomachIndex] = 0;
			Graphics::foodQueue[stomachIndex].push_back(stomachArrayPtr[stomachIndex]);
			Graphics::commandQueue[stomachIndex].push_back('F');
			
			refreshState();
		}

		updateGraphics();

	}
}

/*Flushes food from all 4 stomachs*/
void ComplexCow::flush() {

	//flush all 4 stomachs
	if (isAlive()) { //if alive
		for (int i = 0; i < 4; i++) {

			if (stomachArrayPtr[i] == 0 && Graphics::foodQueue->size() <= 1) {

				setState("DEAD");
			}
			else {

				stomachArrayPtr[i] = 0;
				Graphics::foodQueue[i].push_back(stomachArrayPtr[i]);
				Graphics::commandQueue[i].push_back('F');
				
				refreshState();
			}
			
		}
		updateGraphics();

	}
}

/*Passes specified amount of grass from the stomach indexed if next stomach is empty*/
void ComplexCow::digest(int amount, int stomachIndex) {

	if (!isDead() && !isExploded()) { 

		if (stomachArrayPtr[0] == 0 && Graphics::foodQueue->size() <= 1) {
			killCow();
		}

		if (stomachIndex < 3) {
			
				stomachArrayPtr[stomachIndex] -= amount;
				Graphics::foodQueue[stomachIndex].push_back(stomachArrayPtr[stomachIndex]);

				stomachArrayPtr[stomachIndex + 1] += amount;
				Graphics::foodQueue[stomachIndex + 1].push_back(stomachArrayPtr[stomachIndex + 1]);

				Graphics::commandQueue[stomachIndex].push_back('W');
				Graphics::commandQueue[stomachIndex].push_back('D');
				
				
			
		}
		else if (stomachIndex == 3) {

			stomachArrayPtr[stomachIndex] -= amount;
			Graphics::foodQueue[stomachIndex].push_back(stomachArrayPtr[stomachIndex]);

			Graphics::commandQueue[stomachIndex].push_back('W');
			Graphics::commandQueue[stomachIndex].push_back('D');
			

		}
		else {
			cerr << "Could not locate stomach specified" << endl;
		}

		refreshState();
		updateGraphics();
	}
}


/*Allocates dynamic memory for the stomach pointer array (defined in BaseCow)*/
void ComplexCow::initialiseStomachs() {

	stomachArrayPtr = new int[4];
	Graphics::foodQueue = new vector<int>[4];



	for (int i = 0; i < 4; i++) {

		stomachArrayPtr[i] = 0;
		Cow::isStomachEmpty[i] = true;
		
	}
}

/*Sets initial values for the mood of the cow*/
void ComplexCow::initialiseMoodLevels() {

	emptyLevel = 0;
	hungryLevel = 2;
	contentLevel = 5;
	bloatedLevel = 7;
	fullLevel = 10;

}

/*Alters state of all stomachs if contents change*/
void ComplexCow::refreshState() {

	Soundfx spx;
	int s0 = 0;
	int s1 = 0;
	int s2 = 0;
	int s3 = 0;

	/*s0-s3 are the cow's 4 stomachs*/
	if (!Graphics::foodQueue[0].empty()) { s0 = stomachArrayPtr[0]; };
	if (!Graphics::foodQueue[1].empty()) { s1 = stomachArrayPtr[1]; };
	if (!Graphics::foodQueue[2].empty()) { s2 = stomachArrayPtr[2]; };
	if (!Graphics::foodQueue[3].empty()) { s3 = stomachArrayPtr[3]; };


	if (s0 < emptyLevel || s1 < emptyLevel || s2 < emptyLevel || s3 < emptyLevel) {
		//if all stomachs are empty cow is dead
		killCow();
	}
	else if (s0 > fullLevel || s1 > fullLevel || s2 > fullLevel || s3 > fullLevel) {
		//if all stomachs contain more than the full level... KABOOM
		setState("EXPLODED");
		spx.playExplSound();
	}

	else if (s0 < contentLevel && s0 >= emptyLevel) {
		//if first stomach has between 0 and content level cow is hungry
		setState("HUNGRY");
		spx.playMooSound();
		isSatisfied = false;
	}
	else if (s3 <= fullLevel && s3 > contentLevel) {
		//if last stomach is bloated
		setState("BLOATED");
		spx.playMooSound();
		isSatisfied = false;
	}
	else {
		//cow is content... Yay!
		setState("CONTENT");
		isSatisfied = true;
	}
}
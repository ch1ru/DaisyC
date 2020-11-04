#include "Points.h"


float Points::dollars = 0.0f;

int Points::satisfaction = 3;


Points::Points() {

	moneyFontSize = 22;

	finalDollars = 0;
}


void Points::incrementDollars(int satisfaction) {

	float sf = 0.4f;

	dollars += float(satisfaction) * sf;
	
}

void Points::decrementDollars() {
	
	float decreaseBy = dollars / 10;

	if (dollars - decreaseBy > 0) {

		dollars -= decreaseBy;
	}
	else {
		dollars = 0;
	}

}


void Points::decrementDollars(int amount) {

	if (amount <= dollars) {

		dollars -= amount;
	}
}

float Points::getDollars() {

	return dollars;
}

void Points::setSatisfaction(int newSatisfaction) {

	if (newSatisfaction > 0 && newSatisfaction <= 5) {

		satisfaction = newSatisfaction;
	}
}

int Points::getSatisfaction() {

	return satisfaction;
}

int Points::getFontSize() {

	return moneyFontSize;
}

void Points::setFontSize(int fsize) {

	
	moneyFontSize = fsize;
}

void Points::setFinalDollars(float finDollars) {

	finalDollars = finDollars;
}

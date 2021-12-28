#include "TimeElapsed.h"

using namespace std;

using namespace chrono;


TimeElapsed::TimeElapsed() {

	isDay = true;

	numOfDays = 0;

	dayCounter = 0;

	lastTimeMinutes = NULL;

	transitioned = false;

	transparencyScaleFactor = 0.01;
}

void TimeElapsed::incrementTime() {

	numOfDays++;

	transitioned = true;

}

int TimeElapsed::getNumOfDays() {

	return numOfDays;
}

bool TimeElapsed::getIsDay() {

	return isDay;
}

int TimeElapsed::getDayCounter() {

	return dayCounter;
}

void TimeElapsed::incrementDayCounter() {

	dayCounter++;

	isDay = !isDay;

	transitioned = false;
}

int TimeElapsed::getLastTimeMinutes() {

	return lastTimeMinutes;
}

void TimeElapsed::setLastTimeMinutes(int lastTime) {

	lastTimeMinutes = lastTime;
}

bool TimeElapsed::getTransitioned() {

	return transitioned;
}

double TimeElapsed::getTranparencyScaleFactor() {

	return transparencyScaleFactor;
}

void TimeElapsed::setTransparencyScaleFactor(double scaleFactor) {

	if (scaleFactor <= 1 && scaleFactor > 0) {

		transparencyScaleFactor = scaleFactor;

	}
}


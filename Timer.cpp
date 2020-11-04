#include "Timer.h"
#include <iostream>

using namespace std; 

Timer* Timer::instance = nullptr;
Timer* Timer::timerAfterDeath = nullptr;
Timer* Timer::timerAfterExpl = nullptr;


Timer::Timer() {

	reset();

	timeAfterDeathCounter = NULL;
}

Timer::~Timer() {


}

Timer* Timer::timerInstance() {

	if (instance == nullptr) {
		instance = new Timer();
	}

	return instance;
}


void Timer::reset() {

	startTicks = SDL_GetTicks();

	elapsedTicks = 0;

	deltaTime = 0;
}

int Timer::getDeltaTime() {

	return deltaTime;
}

int Timer::getTimeAfterDeathCounter() {

	return timeAfterDeathCounter;
}

void Timer::setTimeAfterDeathCounter(int newVal) {

	if (timeAfterDeathCounter == NULL) {
		cout << "DEAD" << endl;
		timeAfterDeathCounter = newVal;
	}
	
}


void Timer::update() {

	elapsedTicks = SDL_GetTicks() - startTicks;

	deltaTime = elapsedTicks;
}

Timer* Timer::getTimerAfterDeath() {

	if (timerAfterDeath == nullptr) {
		timerAfterDeath = new Timer();
	}

	return timerAfterDeath;
}

Timer* Timer::getTimerAfterExpl() {

	if (timerAfterExpl == nullptr) {
		
		timerAfterExpl = new Timer();
	
	}

	return timerAfterExpl;
}

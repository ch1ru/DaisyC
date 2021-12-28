#ifndef TIMER
#define TIMER

#include <SDL.h>
#include <iostream>


class Timer {


private:

	/*instances for different timers*/
	static Timer* instance;
	static Timer* timerAfterDeath;
	static Timer* timerAfterExpl;

	unsigned int startTicks;
	unsigned int elapsedTicks;

	int deltaTime;
	float timeScale;

	int timeAfterDeathCounter;


public:

	Timer();

	~Timer();

	static Timer* timerInstance();

	static Timer* getTimerAfterDeath();

	static Timer* getTimerAfterExpl();

	void reset();

	int getDeltaTime(); //get time passed based on framerate

	void setTimeAfterDeathCounter(int newVal);

	int getTimeAfterDeathCounter();

	void update();


};

#endif // !TIMER



#ifndef TIME_ELAPSED
#define TIME_ELAPSED

#include <ctime>
#include <chrono>

using namespace std;

using namespace chrono;

class TimeElapsed {

private:

	int dayCounter; //counts int minutes as day passes

	int numOfDays;

	bool isDay;

	int lastTimeMinutes;

	bool transitioned; //transitioned to night

	double transparencyScaleFactor; //sf for darkness overlay

public:

	TimeElapsed();

	void incrementTime();

	int getNumOfDays();

	bool getIsDay();

	int getDayCounter();

	void incrementDayCounter();

	int getLastTimeMinutes();

	void setLastTimeMinutes(int lastTime);

	bool getTransitioned();

	double getTranparencyScaleFactor();

	void setTransparencyScaleFactor(double scaleFactor);

};

#endif // !TIME_ELAPSED

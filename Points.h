#pragma once


class Points {

private:

	static float dollars;

	float finalDollars; //final amount after game is over

	static int satisfaction;

	int moneyFontSize;


public:

	Points();

	static void incrementDollars(int satisfaction);

	static void decrementDollars();

	static void decrementDollars(int amount);

	static float getDollars();

	static void setSatisfaction(int newSatisfaction);

	static int getSatisfaction();

	int getFontSize();

	void setFontSize(int fsize);

	void setFinalDollars(float finDollars);

};


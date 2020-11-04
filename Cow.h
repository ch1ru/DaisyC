/*Base class for all cow implementations*/

/*          __n__n__
	 .------`-\00/-'
	/  ##  ## (oo)
   / \## __   ./
	  |//YY \|/
	  |||   |||    */

#ifndef COW
#define COW

#include <string>
#include <iostream>
#include "Thoughts.h"
#include <vector>
#include "Items.h"

using namespace std;

class Cow {

private:

	/* Enumerator for holding the constants assigned to the state of daisy */
	static enum state { DEAD = 1, HUNGRY = 2, CONTENT = 4, BLOATED = 8, EXPLODED = 16 };

	
	state stateOfCow; 

	/*Alters state if stomach contents change*/
	virtual void refreshState();


public: 

	
	static bool isStomachFull[4];

	static bool isStomachEmpty[4];

	static bool isSatisfied;

	static int grazesLeft;

	string currentThought = Thoughts::getThought();

	Cow();

	bool isDead();

	bool isAlive();

	bool isHungry();

	bool isContent();

	bool isBloated();

	bool isExploded();

	state getState() {

		return stateOfCow;
	}

	/*User defined thought up to 20 characters long*/
	void setThought(string);

	/*Removes food from ALL stomach(s)*/
	virtual void flush();

	//moves food from parameter given stomach to the next
	virtual void digest(int);

	/*Feed cow 1 piece of grass... Yum*/
	void graze();

	/*Feed cow specified pieces of grass... very yum*/
	void graze(int);

	void buyMoreGrazes();

	void buyMedicine();

	void buyMagicSoup();

	void killCow();


protected:

	int* stomachArrayPtr;

	vector<int>* foodQueue; //stores commands to move food

	

	int emptyLevel;

	int hungryLevel;

	int contentLevel;

	int bloatedLevel;

	int fullLevel;


	void updateGraphics();

	/*Initialises 1st stomach element to 0*/
	virtual void initialiseStomachs();

	void setState(string state);

};

#endif // !COW;


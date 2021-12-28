#pragma once
#include "Points.h"
#include <iostream>
#include "Cow.h"

using namespace std;

class Items {


public:

	Items();

	~Items();

	struct Item { //struct for 3 game items

		int amount;

		int cost;

		string description;
	};


	void updateGrazes();

	void buyMoreGrazes();

	void buyMedicine();

	void buyMagicSoup();

	
	Item getMoreGrazes();

	Item getMedicine();

	Item getMagicSoup();

	void decrementMagicSoup();

	void decrementMedicine();


private:

	Item moreGrazes, medicine, magicSoup;

	/*gives initial values at run time*/
	void initItems(Item& moreGrazes, Item& medicine, Item& magicSoup);

	void printItems();

	void addDescription();

};


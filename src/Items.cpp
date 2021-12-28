#include "Items.h"


Items::Items() {

	initItems(moreGrazes, medicine, magicSoup);

	addDescription();
}


Items::~Items() {


}


void Items::initItems(Item &moreGrazes, Item &medicine, Item &magicSoup) {

	moreGrazes.cost = 50.0;

	medicine.amount = 0;
	medicine.cost = 60;

	magicSoup.amount = 0;
	magicSoup.cost = 80;
}

void Items::updateGrazes() {

	moreGrazes.amount = Cow::grazesLeft;
}


void Items::buyMoreGrazes() {

	int extraAmount = 10;

	if (Points::getDollars() >= moreGrazes.cost) {

		Cow::grazesLeft += extraAmount;
		updateGrazes();
		Points::decrementDollars(moreGrazes.cost);
	}
	else {
		cerr << "Item More Grazes unbought" << endl;
	}
	printItems();
}

void Items::buyMedicine() {

	if (Points::getDollars() >= medicine.cost) {
		medicine.amount++;
		Points::decrementDollars(medicine.cost);
	}
	else {
		cerr << "Item Medicine unbought" << endl;
	}
	printItems();
}

void Items::buyMagicSoup() {

	if (Points::getDollars() >= magicSoup.cost) {
		magicSoup.amount++;
		Points::decrementDollars(magicSoup.cost);
	}
	else {
		cerr << "Item Magic Soup unbought" << endl;
	}
	printItems();
}

void Items::printItems() {

	cout << "More Grazes Item amount: " << moreGrazes.amount << endl;

	cout << "Medicine Item amount: " << medicine.amount << endl;

	cout << "Magic Soup Item amount: " << magicSoup.amount << endl << endl;

}

void Items::addDescription() {

	moreGrazes.description = "More yummy grass..? This item gives Daisy 10 extra grazes.";

	medicine.description = "Prepare for the worst! Medicine will Heal Daisy if she gets sick.";

	magicSoup.description = "Eh..? This Magic Soup will refill stomach levels even if they fall below zero!";

}


Items::Item Items::getMoreGrazes() {

	return moreGrazes;
}

Items::Item Items::getMedicine() {

	return medicine;
}

Items::Item Items::getMagicSoup() {

	return magicSoup;
}

void Items::decrementMagicSoup() {

	magicSoup.amount--;
}

void Items::decrementMedicine() {

	medicine.amount--;
}
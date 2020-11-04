#include "BackgroundImages.h"


using namespace std;


string BackgroundImages::backgroundPath = "";
string BackgroundImages::blinkBackgroundPath = "";

string BackgroundImages::itemsButtonPath = "Media/ItemsBtn/sack_default.png";
string BackgroundImages::medicinePath = "Media/Items/medicine.png";
string BackgroundImages::moreGrazesPath = "Media/Items/moreGrazes.png";
string BackgroundImages::magicSoupPath = "Media/Items/MagicSoup.png";



void BackgroundImages::setBackgroundPath(string path) {

	backgroundPath = path;

}

void BackgroundImages::setBlinkBackgroundPath(string path) {
	blinkBackgroundPath = path;
}


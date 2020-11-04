/*Defines how the UI is displayed to the user*/
#ifndef BACKGROUNDIMAGES
#define BACKGROUNDIMAGES

#include <string>


using namespace std;


class BackgroundImages {

private:

	static string backgroundPath;
	static string blinkBackgroundPath; //background path of cow with eyes shut

public:

	static string itemsButtonPath;
	static string magicSoupPath;
	static string medicinePath;
	static string moreGrazesPath;

	/*File paths for media*/
	string bubblePath = "Media/bubble.png";
	string s0Path = "Media/Stomachs/s0.png";
	string s1Path = "Media/Stomachs/s1.png";
	string s2Path = "Media/Stomachs/s2.png";
	string s3Path = "Media/Stomachs/s3.png";
	string grassPath = "Media/Textures/grass.png";
	string pinkBackingPath = "Media/pink backing.png";
	string redBackingPath = "Media/red backing.png";
	string paleBackingPath = "Media/pale backing.png";
	string cursorImagePath = "Media/daisy.png";
	string deadCowImagePath = "Media/Dead cows/Dead.png";
	string explodedCowImagePath = "Media/Dead cows/Explosion.png";
	string plaquePath = "Media/Items/plaque.png";
	
	


	static string getBackgroundPath() { return backgroundPath; }

	static string getblinkBackgroundPath() { return blinkBackgroundPath; }

	static void setBackgroundPath(string);

	static void setBlinkBackgroundPath(string);

};

#endif // !BACKGROUNDIMAGES
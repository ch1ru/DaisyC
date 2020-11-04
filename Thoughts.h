/*Class controlling which thoughts are retrieved and defines rules for setting custom thoughts*/
#ifndef THOUGHTS
#define THOUGHTS

#include<string>
#include<cmath>
#include <ctime> 
#include <cstdlib>
#include <fstream> 

using namespace std;

const class Thoughts {

private:

	static int getRandomLine();

	static const int getNumOfLinesInFile();

	static ifstream openFile(string fileName);

	/*Returns line to be used for random thought*/
	static const string returnLine(int lineNumber);


public:

	/*Returning random thought from file*/
	static string getThought();

	/*Sets thought to argument passed, first 30 characters*/
	static const string setThought(const string newThought);

};

#endif // !THOUGHTS


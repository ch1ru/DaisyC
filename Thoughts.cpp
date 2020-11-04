#include <iostream>
#include <fstream>
#include <string>
#include "Thoughts.h"


using namespace std;

/*Returns random integer to be used as the line number*/
int Thoughts::getRandomLine() {

	int range = getNumOfLinesInFile(); //max number of lines in text file

	/*seeds random int*/
	srand((unsigned)time(0));
	int i = (rand() % range) + 1;
	return i;
}

/*Returns number of lines in text file*/
const int Thoughts::getNumOfLinesInFile() {

	int lineCounter = 0; //counts line number
	string line; //line of text file
	ifstream file = openFile("DaisyThoughts.txt"); //opens text file containing thoughts

	while (getline(file, line)) {

		lineCounter++;
	}

	return lineCounter;
}

/*Opens file passed as parameter*/
ifstream Thoughts::openFile(string fileName) {

	ifstream streamReader;
	streamReader.open(fileName); //open file

	if (streamReader.is_open()) {
		return streamReader;
	}
	else { //if not open
		cout << "Thoughts file not open" << endl;
	}

}

/*Returns line from number passed*/
const string Thoughts::returnLine(int lineNumber) {

	string line;
	int numOfLines = 0;
	ifstream thoughtsFile = openFile("DaisyThoughts.txt");

	while (!thoughtsFile.eof()) { //loop until end of file
		while (getline(thoughtsFile, line)) { //get full line
			numOfLines++; //increment line number
			if (numOfLines == lineNumber) {
				//close file when line number is reached
				thoughtsFile.close();

				return line;

			}
		}
	}
}

/*Returning random thought from file*/
string Thoughts::getThought() {


	int randomLine = getRandomLine(); //random line number

	string thought = returnLine(randomLine); //random line assigned as thought

	return thought;

}

/*Sets thought to argument passed, first 20 characters*/
const string Thoughts::setThought(const string newThought) {
	string thought;
	if (newThought.length() > 20) { //bigger than 20 chars
		thought = newThought.substr(0, 20) + "...";
	}
	else {
		thought = newThought;
	}
	return thought;

}



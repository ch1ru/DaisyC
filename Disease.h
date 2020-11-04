#pragma once
#include <iostream>
#include <string>
#include "BackgroundImages.h"
#include<cmath>
#include <ctime> 
#include <cstdlib>

using namespace std;

class Disease {

private:

	double frequency = 1; //number of times on average within timeframe cow gets sick

	double genRandNum();


public:

	bool getIsSick(int timeFrameDays);

};


//Header file for playing sound effects

#ifndef SOUNDFX
#define SOUNDFX

#include <Windows.h> 
#pragma comment(lib, "Winmm.lib") //library to find by linker

class Soundfx {

public:

	void playDeadSound();

	void playExplSound();

	void playMooSound();
};

#endif // !SOUNDFX


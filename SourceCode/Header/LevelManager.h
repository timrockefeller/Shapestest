#pragma once
#include "Level.h"
#include <vector>
#include <string>
#include "dist/irrKlang/irrKlang.h"//audio engine

#pragma comment(lib,"irrKlang.lib")
class LevelManager {
public:

	LevelManager();
	~LevelManager();

	std::vector<Level*> playlist;

	//playsong
	void playLevel(Level level);
	
	irrklang::ISoundEngine* soundEngine;

};
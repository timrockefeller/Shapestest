#pragma once
#include "Level.h"
#include <vector>
#include <string>
class LevelManager {
public:

	LevelManager();

	std::vector<Level*> playlist;

	//playsong
	void playLevel(Level level);
	
	
};
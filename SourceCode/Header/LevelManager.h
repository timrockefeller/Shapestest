#pragma once
#include "Level.h"
#include "Player.h"
#include <vector>
#include <string>
//#include "dist/irrKlang/irrKlang.h"//audio engine
#include "SoundSystem.h"
//#pragma comment(lib,"irrKlang.lib")
class LevelManager {
public:

	LevelManager();
	~LevelManager();

	std::vector<Level*> playlist;

	void update();

	//playsong
	void playLevel(Level* level);
	
	//irrklang::ISoundEngine* soundEngine;
	SoundSystem * soundSystem;

	Player*			m_Player;
private:
	
	std::vector<HitObject*> pathBuffer_UP;
	std::vector<HitObject*> pathBuffer_RIGHT;
	std::vector<HitObject*> pathBuffer_Down;
	std::vector<HitObject*> pathBuffer_LEFT;
};
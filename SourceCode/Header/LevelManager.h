#pragma once
#include <vector>
#include <string>
#include "Level.h"
#include "Player.h"
#include "CommonClass.h"
//#include "dist/irrKlang/irrKlang.h"//audio engine
#include "SoundSystem.h"
//#pragma comment(lib,"irrKlang.lib")

enum GAME_STATS {
	
};
class LevelManager{
public:

	LevelManager();
	~LevelManager();

	std::vector<Level*> playlist;
	void init();
	void update();
	void keyDown(const int ikey);


	//开始关卡
	void playLevel(Level* level);
	//直接进入下一关卡
	void nextLevel();
	//储存正在运行的关卡
	Level* playingLevel;


	//声音系统
	SoundSystem * soundSystem;

	//note
	CSprite* m_NotePrefab;

	//玩家~
	Player*			m_Player;
private:
	
	std::vector<HitObject*> pathBuffer[4];

	float songPosition;
	float songPosInBeats;

	int nextHitObjectCur;

	const float beatsShownInAdvance = 5.0f;

	int _nextdelay = 1;//防误触
};
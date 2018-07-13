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
	GAME_STATS_INITIAL,
	GAME_STATS_PASSING,//����
	GAME_STATS_PLAYING,//����������
};
class LevelManager{
public:

	LevelManager();
	~LevelManager();

	std::vector<Level*> playlist;
	void init();
	void update();
	void keyDown(const int ikey);


	//��ʼ�ؿ�
	void playLevel(Level* level);
	//ֱ�ӽ�����һ�ؿ�
	void nextLevel();
	//�����������еĹؿ�
	Level* playingLevel;


	//����ϵͳ
	SoundSystem * soundSystem;

	//note
	CSprite* m_NotePrefab;

	//���~
	Player*			m_Player;
private:
	GAME_STATS stats;

	std::vector<HitObject> pathBuffer[4];

	float songPosition;
	float songPosInBeats;

	int nextHitObjectCur=0;

	const float beatsShownInAdvance = 1.0f;

	int _nextdelay = 1;//����
};
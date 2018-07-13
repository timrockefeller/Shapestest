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

	//noteԤ�裬���������½��Ǹ�С�׿�
	CSprite* m_NotePrefab;

	//���~
	Player*			m_Player;

	//������
	CSprite* m_ProccessBar;

private:
	GAME_STATS stats;

	std::vector<HitObject> pathBuffer[4];

	float songPosition;
	float songPosInBeats;

	//////////////////////////////////////////
	//////////////  Level Mode  //////////////
	
	//note
	int nextHitObjectCur=0;

	//������note�ٶ�
	const float beatsShownInAdvance = 1.0f;

	//������note������
	const float beatsSpawn = 500.0f;
	//////////////////////////////////////////
	//////////////  Pure Mode  ///////////////

	//puresong �����ã�����
	int _nextdelay = 1;
};
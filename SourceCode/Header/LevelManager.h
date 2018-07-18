#pragma once
#include <vector>
#include <map>
#include <string>
#include "Level.h"
#include "Player.h"

#include "CommonClass.h"

#include "Effects.h"
#include "Effects\Effect_process_bar.h"
#include "Effects\Effect_note_slide.h"
#include "Effects\Effect_handleFlash.h"

#include "stdEffects\Effect_Fade.h"
#include "stdEffects\Effect_Pos.h"
#include "stdEffects\Effect_Size.h"
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

	//��ʼ������
	void init();

	//����Ч
	void bindEffects();

	//ÿ֡����
	void update(float deltaTime);

	
	void keyDown(const int ikey);


	//�ؿ�ָ��
	int playIndex = 0;
	
	//��ʼ�ؿ�
	void playLevel(Level* level);
	//ֱ�ӽ�����һ�ؿ�
	void nextLevel();
	//�����������еĹؿ�
	Level* playingLevel;


	//����ϵͳ
	SoundSystem *soundSystem;

	

	//���~
	Player*			m_Player;



private:

	std::map<char*,Effect*>  effects;

	std::map<char*, Effect_Once*> effectsOnce;

	//std::map<char*, Effects*>  effects;

	GAME_STATS stats;

	float songPosition;
	float songPosInBeats;

	//////////////////////////////////////////
	//////////////  Level Mode  //////////////
	
	//noteԤ�裬���������½��Ǹ�С�׿�
	CSprite* m_NotePrefab;

	//notecur��ָ��beatmap����һ��Ԫ�ص�index
	int nextHitObjectCur=0;

	//level->songTempo / 70.0f  note�ٶ�
	float beatsShownInAdvance = 1.0f;

	//������note������
	const float beatsSpawn = 500.0f;


	//���������ĸ������note��ʱ����vector
	std::vector<HitObject> pathBuffer[4];


	//////////////////////////////////////////
	//////////////  Pure Mode  ///////////////

	//puresong �����ã�����
	int _nextdelay = 1;


	//////////////////////////////////////////
	//////////////   EFFECTS   ///////////////
	//CSprite* effect_processBar;

};
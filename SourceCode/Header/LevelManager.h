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

#define GAME_CHAT_LEFT -271
#define GAME_CHAT_RIGHT 260
#define GAME_CHAT_CENTER 0
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

	//����λ�û�����Ϣ
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

	//note�ж�
	void checkNote(bool);

	//���������ĸ������note��ʱ����vector
	std::vector<HitObject> pathBuffer[4];

	//////////////////////////////////////////
	//////////////  Chat Mode  ///////////////

	//textbox���
	CSprite * m_textBox = NULL;

	//����ģ���Ի�����
	CTextSprite * m_textInner = NULL;

	//ָ����һĻ��λ��
	int currentChatCur = 0;

	//ָ����һ���λ��
	int currentDiagCur = 0;

	//��̨
	CSprite* chatStage[3];
	
	//��һ�仰
	bool nextDiag();

	//////////////////////////////////////////
	//////////////  Pure Mode  ///////////////

	//puresong �����ã�����
	int _nextdelay = 1;


	//////////////////////////////////////////
	//////////////   EFFECTS   ///////////////
	//CSprite* effect_processBar;
	void alertSongInfo(std::string);
	CTextSprite*	m_text_songInfo = NULL;
	float		_text_songInfo_delay=-1;

	void alertMessage(std::string);
	CTextSprite*m_text_message = NULL;
	CSprite*	m_box_message=NULL;
	float		_text_message_delay=-1;
};
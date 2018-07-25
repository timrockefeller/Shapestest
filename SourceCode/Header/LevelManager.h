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
	GAME_STATS_PASSING,//过场
	GAME_STATS_PLAYING,//运行音乐中
};
class LevelManager{
public:

	LevelManager();
	~LevelManager();

	std::vector<Level*> playlist;

	//初始化歌曲
	void init();

	//绑定特效
	void bindEffects();

	//每帧更新
	void update(float deltaTime);

	
	void keyDown(const int ikey);


	//关卡指针
	int playIndex = 0;
	
	//开始关卡
	void playLevel(Level* level);
	//直接进入下一关卡
	void nextLevel();
	//储存正在运行的关卡
	Level* playingLevel;


	//声音系统
	SoundSystem *soundSystem;

	

	//玩家~
	Player*			m_Player;



private:

	std::map<char*,Effect*>  effects;

	std::map<char*, Effect_Once*> effectsOnce;

	//std::map<char*, Effects*>  effects;

	GAME_STATS stats;

	//音乐位置基本信息
	float songPosition;
	float songPosInBeats;

	//////////////////////////////////////////
	//////////////  Level Mode  //////////////
	
	//note预设，界面里左下角那个小白框
	CSprite* m_NotePrefab;

	//notecur，指向beatmap中下一个元素的index
	int nextHitObjectCur=0;

	//level->songTempo / 70.0f  note速度
	float beatsShownInAdvance = 1.0f;

	//常量，note出生点
	const float beatsSpawn = 500.0f;

	//note判定
	void checkNote(bool);

	//上右下左四个方向的note临时储存vector
	std::vector<HitObject> pathBuffer[4];

	//////////////////////////////////////////
	//////////////  Chat Mode  ///////////////

	//textbox句柄
	CSprite * m_textBox = NULL;

	//辣鸡模糊对话框句柄
	CTextSprite * m_textInner = NULL;

	//指向这一幕的位置
	int currentChatCur = 0;

	//指向这一句的位置
	int currentDiagCur = 0;

	//舞台
	CSprite* chatStage[3];
	
	//下一句话
	bool nextDiag();

	//////////////////////////////////////////
	//////////////  Pure Mode  ///////////////

	//puresong 防误触用，勿理
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
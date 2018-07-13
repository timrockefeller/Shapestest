#include "LevelManager.h"
#include "fmod_inc\fmod.h"
#include "MathHandle.h"
LevelManager::LevelManager()
{
	
	
	this->soundSystem = new SoundSystem();

	this->m_Player = new Player();

	this->m_NotePrefab = new CSprite ("note_prefab");
	
	this->init();

	//test song
	this->playLevel(playlist[0]);
}

LevelManager::~LevelManager()
{
	//this->soundEngine->drop();
	//this->soundEngine = 0;
}

void LevelManager::init()
{
	//将json放在这里声明
	// EXAMPLE: 
	// this->playlist.push_back(new Level("examplesong.json",GAME_LEVEL_TYPE_PURESONG));
	this->playlist.push_back(new Level());//defaule song

}

void LevelManager::update()
{
	soundSystem->update();
	m_Player->UpdateRender();
	
	if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_PURESONG) {
		//彦恺，你来调参数
		m_Player->currentSize = m_Player->DefaultSize + 1500.0f * soundSystem->getSpectrumCurruentTime();
	}
	else if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_LEVEL) {//dspTIME refresh
		

		songPosition = this->soundSystem->getPositionInMs();

		songPosInBeats = (songPosition - playingLevel->songOffset) / (60.f / playingLevel->songTempo);

		if (nextHitObjectCur < playingLevel->beatmap.size() && 
			playingLevel->beatmap[nextHitObjectCur].getPosInBeat() <= beatsShownInAdvance){

			//Instantiate( /* Music Note Prefab */);
			if (true) {
				playingLevel->beatmap[nextHitObjectCur].bindSprite->CloneSprite("note_prefab");
				pathBuffer[0].push_back(&playingLevel->beatmap[nextHitObjectCur]);
			}
			nextHitObjectCur++;

		}

		//update positions
		for (int _I=0; _I < 4; _I++) {
			for (int _J=0; _J < pathBuffer[_I].size(); _J++) {
				pathBuffer[_I][_J]->bindSprite->SetSpritePosition(
				MathHandle::LerpFloat(
					128,
					300,
					(beatsShownInAdvance - (pathBuffer[_I][_J]->getPosInBeat() - songPosInBeats)) / beatsShownInAdvance
				),
				0
				);
			
			}
		
		}

	}
}

void LevelManager::keyDown(const int iKey)
{
	HitObjectType type = HIT_UNDEFINE;
	switch (iKey) {
	case KEY_UP:
		type = HIT_UP;
		break;
	case KEY_DOWN:
		type = HIT_DOWN;
		break;
	case KEY_LEFT:
		type = HIT_LEFT;
		break;
	case KEY_RIGHT:
		type = HIT_RIGHT;
		break;
	}
	if (playingLevel->getLevelType()==GAME_LEVEL_TYPE_LEVEL||//按键只在游戏、对话里面响应方向。
		playingLevel->getLevelType()==GAME_LEVEL_TYPE_CHAT) {
		m_Player->OnKeyPressed(type);
	}
	else {//其他就提前结束
		_nextdelay--;//防误触
		if (_nextdelay < 1) { this->nextLevel(); _nextdelay = 1; }
	}
}

void LevelManager::playLevel(Level* level)
{
	// instantiate
	level->loadLevel();
	this->playingLevel = level;
	soundSystem->playMusic(level->getSongPath());
}

void LevelManager::nextLevel() {

}
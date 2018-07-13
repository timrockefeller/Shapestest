#include "LevelManager.h"
#include "fmod_inc\fmod.h"
#include "MathHandle.h"
LevelManager::LevelManager()
{
	
	this->stats = GAME_STATS_INITIAL;
	
	this->soundSystem = new SoundSystem();

	this->m_Player = new Player();

	this->m_NotePrefab = new CSprite ("note_prefab");
	
	this->init();

	this->playingLevel = NULL;
	//test song
	
}

LevelManager::~LevelManager()
{
	//this->soundEngine->drop();
	//this->soundEngine = 0;
}

void LevelManager::init()
{
	//��json������������
	// EXAMPLE: 
	// this->playlist.push_back(new Level("examplesong.json",GAME_LEVEL_TYPE_PURESONG));
	this->playlist.push_back(new Level());//defaule song

}

void LevelManager::update()
{
	soundSystem->update();
	m_Player->UpdateRender();
	if (stats == GAME_STATS_PLAYING) {
		if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_PURESONG) {
			//����������������
			m_Player->currentSize = m_Player->DefaultSize + 1500.0f * soundSystem->getSpectrumCurruentTime();
		}
		else if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_LEVEL) {//dspTIME refresh


			songPosition = this->soundSystem->getPositionInMs();

			songPosInBeats = (songPosition - playingLevel->songOffset) / (60000.0f / playingLevel->songTempo);

			if (nextHitObjectCur < playingLevel->beatmap.size() &&
				this->playingLevel->beatmap[nextHitObjectCur].getPosInBeat() <= beatsShownInAdvance) {

				//Instantiate( /* Music Note Prefab */);
				char tempName[128];
				sprintf(tempName, "note_%d", nextHitObjectCur);
				playingLevel->beatmap[nextHitObjectCur].bindSprite = new CSprite(tempName);
				if (playingLevel->beatmap[nextHitObjectCur].bindSprite->CloneSprite("note_prefab")) {

					pathBuffer[0].push_back(this->playingLevel->beatmap[nextHitObjectCur]);

					nextHitObjectCur++;
				}
			}

			//update positions
			for (int _I = 0; _I < 4; _I++) {
				for (int _J = 0; _J < pathBuffer[_I].size(); _J++) {
					pathBuffer[_I][_J].bindSprite->SetSpritePosition(
						MathHandle::LerpFloat(
							500,
							128,
							(beatsShownInAdvance - (pathBuffer[_I][_J].getPosInBeat() - songPosInBeats)) / beatsShownInAdvance
						),
						0
					);

				}

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
	if (stats == GAME_STATS_PLAYING) {
		if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_LEVEL ||//����ֻ����Ϸ���Ի�������Ӧ����
			playingLevel->getLevelType() == GAME_LEVEL_TYPE_CHAT) {
			m_Player->OnKeyPressed(type);
		}
		else {//��������ǰ����
			_nextdelay--;//����
			if (_nextdelay < 1) { this->nextLevel(); _nextdelay = 1; }
		}
	}

	if (iKey == KEY_R) {//test
		
		this->playLevel(playlist[0]);
	}
}

void LevelManager::playLevel(Level* level)
{
	this->stats = GAME_STATS_PASSING;
	nextHitObjectCur = 0;

	soundSystem->killPlaying();

	// instantiate
	if (level->loadLevel()) {
		this->playingLevel = level;
		soundSystem->playMusic(level->getSongPath());
		this->stats = GAME_STATS_PLAYING;
	}
	else printf("failed to play Level.");
		
}

void LevelManager::nextLevel() {

}
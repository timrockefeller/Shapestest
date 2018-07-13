#include "LevelManager.h"
#include "fmod_inc\fmod.h"

LevelManager::LevelManager()
{
	
	
	this->soundSystem = new SoundSystem();

	this->m_Player = new Player();
	
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
	//彦恺，你来调参数
	m_Player->currentSize = m_Player->DefaultSize + 1500.0f * soundSystem->getSpectrumCurruentTime();

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
	m_Player->OnKeyPressed(type);
}

void LevelManager::playLevel(Level* level)
{
	// instantiate
	soundSystem->playMusic(level->getSongPath());
}

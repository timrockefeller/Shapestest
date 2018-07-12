#include "LevelManager.h"
#include "fmod_inc\fmod.h"

LevelManager::LevelManager()
{
	
	this->playlist.push_back(new Level());
	this->soundSystem = new SoundSystem();

	this->m_Player = new Player();

	//test song
	this->playLevel(playlist[0]);
}

LevelManager::~LevelManager()
{
	//this->soundEngine->drop();
	//this->soundEngine = 0;
}

void LevelManager::update()
{
	soundSystem->update();
	m_Player->UpdateRender();
	//彦恺，你来调参数
	m_Player->currentSize = m_Player->DefaultSize + 1500.0f * soundSystem->getSpectrumCurruentTime();

}

void LevelManager::playLevel(Level* level)
{
	// instantiate
	soundSystem->playMusic(level->getSongPath());
}

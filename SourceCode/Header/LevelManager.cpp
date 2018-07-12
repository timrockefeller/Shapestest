#include "LevelManager.h"

LevelManager::LevelManager()
{
	this->soundEngine = irrklang::createIrrKlangDevice();
	this->playlist.push_back(new Level());
}

LevelManager::~LevelManager()
{
	this->soundEngine->drop();
	this->soundEngine = 0;
}

void LevelManager::playLevel(Level level)
{
	// instantiate

}

#pragma once
#include "HitObject.h"
#include <string>
#include <vector>
class Level {

private:
	std::string songPath;
	//song info
	float tempo;
	float offset;
	std::vector<HitObject> beatmap;
public:
	Level();
	Level(std::string _songPath, float _tempo, float _offset);
	
	//º”‘ÿHit Objects
	void loadMap();
};
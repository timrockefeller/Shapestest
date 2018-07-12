#pragma once
#include "HitObject.h"
#include <string>
#include <vector>
class Level {

private:
	std::string songName;
	std::string songPath;
	//song info
	float songTempo;
	float songOffset;
	std::vector<HitObject> beatmap;
public:
	Level();
	Level(std::string mapname);
	
	
	//º”‘ÿHit Objects
	void loadMap(std::string songInfoFilePath);
};
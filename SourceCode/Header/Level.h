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
	
	void loadSongInfo();
	
	//º”‘ÿHit Objects
	void loadMap(std::string songInfoFilePath);
};
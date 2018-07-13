#pragma once
#include "HitObject.h"
#include <string>
#include <vector>
#include "dist\json\json.h"
enum GAME_LEVEL_TYPE {
	GAME_LEVEL_TYPE_PURESONG,
	GAME_LEVEL_TYPE_LEVEL,
	GAME_LEVEL_TYPE_CHAT
};
class Level {

private:
	std::string levelPath;

	GAME_LEVEL_TYPE type;

	std::string songName;
	std::string songPath;

	//song info
	float songTempo;
	float songOffset;

	/*
		临时beatmap储存库。
	*/
	std::vector<HitObject> beatmap;


	//1.加载关卡 (加载Hit Objects)
	void loadMap(Json::Value root);
	//2.加载歌曲 (Pure song)
	void loadSong(Json::Value root);
	//3.加载对话
	void loadChat(Json::Value root);

public:
	Level();
	Level(std::string mapname,GAME_LEVEL_TYPE _type);

	//加载地图
	void loadLevel();
	
	std::string getSongPath();
};
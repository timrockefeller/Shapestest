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
		��ʱbeatmap����⡣
	*/
	std::vector<HitObject> beatmap;


	//1.���عؿ� (����Hit Objects)
	void loadMap(Json::Value root);
	//2.���ظ��� (Pure song)
	void loadSong(Json::Value root);
	//3.���ضԻ�
	void loadChat(Json::Value root);

public:
	Level();
	Level(std::string mapname,GAME_LEVEL_TYPE _type);

	//���ص�ͼ
	void loadLevel();
	
	std::string getSongPath();
};
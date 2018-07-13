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
	//�ؿ��ļ�·��
	std::string levelPath;

	

	std::string songName;
	std::string songPath;

	

	//�ؿ�ģʽ
	GAME_LEVEL_TYPE type = GAME_LEVEL_TYPE_PURESONG;
	


	//1.���عؿ� (����Hit Objects)
	void loadMap(Json::Value root);
	//2.���ظ��� (Pure song)
	void loadSong(Json::Value root);
	//3.���ضԻ�
	void loadChat(Json::Value root);

public:
	Level();
	Level(std::string mapname,GAME_LEVEL_TYPE _type);

	//song info
	float songTempo;
	float songOffset;

	//��ʱbeatmap����⡣
	std::vector<HitObject> beatmap;

	//���ص�ͼ
	boolean loadLevel();
	
	std::string getSongPath();
	GAME_LEVEL_TYPE getLevelType();


};
#pragma once
#include "HitObject.h"
#include "Chat.h"
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
	//关卡文件路径
	std::string levelPath;

	std::string songPath;

	//关卡模式
	GAME_LEVEL_TYPE type = GAME_LEVEL_TYPE_PURESONG;
	


	//1.加载关卡 (加载Hit Objects)
	void loadMap(Json::Value root);
	//2.加载歌曲 (Pure song)
	void loadSong(Json::Value root);
	//3.加载对话
	void loadChat(Json::Value root);

public:
	Level();
	Level(std::string mapname,GAME_LEVEL_TYPE _type);

	//song info
	
	//歌曲bpm
	float songTempo;
	
	//歌曲偏移量
	float songOffset;
	std::string songName;
	//临时beatmap储存库。
	std::vector<HitObject> beatmap;

	//
	int notenum;

	//临时chat储存库
	std::vector<Chat>      chats;

	//加载地图
	boolean loadLevel();
	
	std::string getSongPath();
	GAME_LEVEL_TYPE getLevelType();


};
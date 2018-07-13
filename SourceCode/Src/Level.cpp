#include <fstream>
#include "Level.h"


Level::Level()
{
	this->levelPath = "../../Assets/Songs/level0.json";
	this->type = GAME_LEVEL_TYPE_LEVEL;
}

Level::Level(std::string mapname, GAME_LEVEL_TYPE _type)
{
	this->levelPath = "../../Assets/Songs/" + mapname;
	this->type = _type;
}

void Level::loadLevel()
{
	std::ifstream ifs;
	ifs.open(this->levelPath);
	if (!ifs.is_open()) {
		printf("Error to open file");
		return;
	}
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
		printf("parse failed \n");
		return;
	}

	this->songName = root["songName"].asString();
	this->songPath = root["songPath"].asString();
	this->songOffset = root["songOffset"].asFloat();
	this->songTempo = root["songTempo"].asFloat();

	switch (this->type) {
	case GAME_LEVEL_TYPE_LEVEL:
		this->loadMap(root);
		break;
	case GAME_LEVEL_TYPE_CHAT:
		this->loadChat(root);
		break;
	case GAME_LEVEL_TYPE_PURESONG:
		this->loadSong(root);
		break;
	}
}

void Level::loadMap(Json::Value root)
{
	//load beatmap
	//把json里面的数据一一对应到这个类的各个成员
	
	//尝试新东西
	int beatmap_size = root["beatmap"].size();
	for (int i = 0; i < beatmap_size; i++)
	{
		HitObject temp;
		temp.setPosInBeat(root["beatmap"][i]["posInBeat"].asFloat());
		//1 == HIT_UP;
		HitObjectType temptype=HIT_UNDEFINE;
		switch (root["beatmap"][i]["type"].asInt())
		{
		case HIT_UP:temptype = HIT_UP; break;
		case HIT_RIGHT:temptype = HIT_RIGHT; break;
		case HIT_DOWN:temptype = HIT_DOWN; break;
		case HIT_LEFT:temptype = HIT_LEFT; break;
		case HIT_EFFECT: temptype = HIT_EFFECT; break;
		default:temptype = HIT_UNDEFINE;
		}
		temp.setType(temptype);
		beatmap.push_back(temp);
	}

}
void Level::loadSong(Json::Value root)
{
	//load effect? NO. just song.
}
void Level::loadChat(Json::Value root)
{
	//load Chat
}

std::string Level::getSongPath()
{
	return "../../Assets/Songs/"+this->songPath;
}
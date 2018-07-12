#include <fstream>
#include "Level.h"
#include "dist\json\json.h"

Level::Level()
{
	this->loadMap("../../Assets/Songs/level0.json");
}

Level::Level(std::string mapname)
{
	this->loadMap("../../Assets/Songs/" + mapname);
}

void Level::loadMap(std::string songInfoFilePath)
{
	std::ifstream ifs;
	ifs.open(songInfoFilePath);
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

	//��json���������һһ��Ӧ�������ĸ�����Ա
	this->songName = root["songName"].asString();
	this->songPath = root["songPath"].asString();
	this->songOffset = root["songOffset"].asFloat();
	this->songTempo = root["songTempo"].asFloat();
	//�����¶���
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
std::string Level::getSongPath()
{
	return "../../Assets/Songs/"+this->songPath;
}
//this->songname=root["people"][0]["lastName"].asString();
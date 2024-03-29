#include <fstream>
#include "Level.h"
#include<string>
using std::string;
//
//#include <direct.h>

Level::Level()
{
	this->levelPath = "../SourceCode/Assets/Songs/level1.json";
	this->type = GAME_LEVEL_TYPE_CHAT;
}

Level::Level(std::string mapname, GAME_LEVEL_TYPE _type)
{
	this->levelPath = "../SourceCode/Assets/Songs/" + mapname;
	this->type = _type;
}

boolean Level::loadLevel()
{
	this->notenum = 0;
	std::ifstream ifs;
	ifs.open(this->levelPath);
	if (!ifs.is_open()) {
		printf("Error to open file");
		return false;
	}
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
	 	printf("parse failed \n");
		return false;
	}

	this->songName = root["songName"].asString();
	this->songPath = root["songPath"].asString();
	this->songOffset = root["songOffset"].asFloat();
	this->songTempo = root["songTempo"].asFloat();

	switch (this->type) {
	case GAME_LEVEL_TYPE_LEVEL:
		this->type = GAME_LEVEL_TYPE_LEVEL;
		this->loadMap(root);
		break;
	case GAME_LEVEL_TYPE_CHAT:
		this->type = GAME_LEVEL_TYPE_CHAT;
		this->loadChat(root);
		break;
	case GAME_LEVEL_TYPE_PURESONG:
		this->type = GAME_LEVEL_TYPE_PURESONG;
		this->loadSong(root);
		break;
	}
	return true;
}

void Level::loadMap(Json::Value root)
{
	//load beatmap
	//把json里面的数据一一对应到这个类的各个成员
	
	//delete beatmap first
	beatmap.clear();
	std::vector<HitObject>(beatmap).swap(beatmap);
	//尝试新东西
	int beatmap_size = root["beatmap"].size();
	for (int i = 0; i < beatmap_size; i++)
	{
		HitObject temp;
		temp.setPosInBeat(root["beatmap"][i]["posInBeat"].asFloat());
		temp.setPosInMs(temp.getPosInBeat() * 60000.0f / this->songTempo + this->songOffset);
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
		if (temptype != HIT_EFFECT&&temptype!=HIT_UNDEFINE) { this->notenum++; }
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
	//erase saki
	chats.clear();
	std::vector<Chat>(chats).swap(chats);
	//load Chat
	int chat_size = root["chat"].size();
	for (int chat_index = 0; chat_index < chat_size; chat_index++)
	{
		Chat temp;
		int diags_size = root["chat"][chat_index]["dialogue"].size();
		for (int diags_index = 0; diags_index < diags_size; diags_index++)
			temp.diags.push_back(root["chat"][chat_index]["dialogue"][diags_index].asString());
		string tempLeftChara = root["chat"][chat_index]["left"].asString();
		string tempRightChara = root["chat"][chat_index]["right"].asString();
		temp.left_str = tempLeftChara;
		temp.right_str = tempRightChara;
		int tempOnChating = root["chat"][chat_index]["onChating"].asInt();//0代表左边说话，1代表右边说话
		temp.onChating = tempOnChating;
		this->chats.push_back(temp);
	}
}

std::string Level::getSongPath()
{
	return "../SourceCode/Assets/Songs/"+this->songPath;
}

GAME_LEVEL_TYPE Level::getLevelType()
{
	return type;
}


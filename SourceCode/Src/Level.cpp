#include <fstream>
#include "Level.h"
#include<string>
using std::string;
//
//#include <direct.h>

Level::Level()
{
	this->levelPath = "../SourceCode/Assets/Songs/level2.json";
	this->type = GAME_LEVEL_TYPE_LEVEL;
}

Level::Level(std::string mapname, GAME_LEVEL_TYPE _type)
{
	this->levelPath = "../SourceCode/Assets/Songs/" + mapname;
	this->type = _type;
}

boolean Level::loadLevel()
{
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
	int chat_size = root["chat"].size();
	for (int chat_index = 0; chat_index < chat_size; chat_index++)
	{
		Chat temp;
		int diags_size = root["chat"][chat_index]["dialogue"].size();
		for (int diags_index = 0; diags_index < diags_size; diags_index++)
			//temp=Chatdiags(root["chat"][chat_index]["dialogue"].asString());
			temp.diags.push_back(root["chat"][chat_index]["dialogue"].asString());
		string tempLeftChara = root["chat"][chat_index]["left"].asString();
		string tempRightChara = root["chat"][chat_index]["right"].asString();
		int tempOnChating = root["chat"][chat_index]["onChating"].asInt();//0代表左边说话，1代表右边说话
		/*switch (root["chat"][i]["left"].asInt())
		{
		case Syncopy:tempLeftChara = Syncopy; break;
		case Crescendia:tempLeftChara = Crescemdo; break;
		default blank:tempLeftChara = blank; break;
		}
		switch (root["chat"][i]["right"].asInt())
		{
		case Syncopy:tempRightChara = Syncopy; break;
		case Crescendia:tempRightChara = Crescemdo; break;
		default blank:tempRightChara = blank; break;
		}*/
		temp.setleft_str(tempLeftChara);
		temp.setright_str(tempRightChara);
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


#include "LevelManager.h"
#include "fmod_inc\fmod.h"
#include "MathHandle.h"

//构造函数：初始化
LevelManager::LevelManager()
{
	
	this->stats = GAME_STATS_INITIAL;
	
	LevelManager::soundSystem = new SoundSystem();

	this->m_Player = new Player();

	this->m_NotePrefab = new CSprite("note_prefab");

	this->m_textBox = new CSprite("textBox");

	this->m_textInner = new CTextSprite("innerText");

	this->m_text_songInfo = new CTextSprite("songinfo_text");

	this->m_text_message = new CTextSprite("message_text");

	this->m_box_message = new CSprite("message_box");

	

	this->_text_songInfo_delay = this->_text_message_delay = -1;

	_nextdelay = 1;

	this->init();

	this->bindEffects();

	this->playingLevel = NULL;
	//test song
	
}

LevelManager::~LevelManager()
{
	//this->soundEngine->drop();
	//this->soundEngine = 0;
}

void LevelManager::init()
{


	//将json放在这里声明
	// EXAMPLE: 
	// this->playlist.push_back(new Level("examplesong.json",GAME_LEVEL_TYPE_PURESONG));
	//song 1
	this->playlist.push_back(new Level("level1.json",GAME_LEVEL_TYPE_CHAT));//defaule song
	this->playlist.push_back(new Level("level_shelter.json", GAME_LEVEL_TYPE_LEVEL));
	this->playlist.push_back(new Level("level4.json", GAME_LEVEL_TYPE_CHAT));
	//song 2
	this->playlist.push_back(new Level("level5.json", GAME_LEVEL_TYPE_CHAT));
	this->playlist.push_back(new Level("level2.json", GAME_LEVEL_TYPE_LEVEL));
	this->playlist.push_back(new Level("level6.json", GAME_LEVEL_TYPE_CHAT));
	//song 3
	this->playlist.push_back(new Level("level7.json", GAME_LEVEL_TYPE_CHAT));
	this->playlist.push_back(new Level("level_bassTelekinesis.json", GAME_LEVEL_TYPE_LEVEL));
	this->playlist.push_back(new Level("level8.json", GAME_LEVEL_TYPE_CHAT));
	this->playlist.push_back(new Level("level9.json", GAME_LEVEL_TYPE_CHAT));

	//song 4

	this->playlist.push_back(new Level("level10.json", GAME_LEVEL_TYPE_CHAT));
	this->playlist.push_back(new Level("level11.json", GAME_LEVEL_TYPE_CHAT));

	this->playlist.push_back(new Level("level_EyesHalfClosed.json", GAME_LEVEL_TYPE_LEVEL));
	this->playlist.push_back(new Level("level12.json", GAME_LEVEL_TYPE_CHAT));

}

//绑定特效
void LevelManager::bindEffects()
{
	//bind
	effects.insert(std::pair<char*, Effect*>("process_bar",new Effect_ProcessBar()));
	effects.insert(std::pair<char*, Effect*>("noteSlide_UP", new Effect_NoteSlide_Up()));
	effects.insert(std::pair<char*, Effect*>("noteSlide_RIGHT", new Effect_NoteSlide_Right()));
	effects.insert(std::pair<char*, Effect*>("noteSlide_DOWN", new Effect_NoteSlide_Down()));
	effects.insert(std::pair<char*, Effect*>("noteSlide_LEFT", new Effect_NoteSlide_Left()));
	effects.insert(std::pair<char*, Effect*>("handleFlash", new Effect_HandleFlash()));
		
	
	//once
	effectsOnce.insert(std::pair<char*, Effect_Once*>("fade_in", new Effect_FadeIn()));
	effectsOnce.insert(std::pair<char*, Effect_Once*>("fade_out", new Effect_FadeOut()));
	effectsOnce.insert(std::pair<char*, Effect_Once*>("fade_128", new Effect_Fade128()));
	effectsOnce.insert(std::pair<char*, Effect_Once*>("move_x", new Effect_Pos_MovetoX()));
	//effectsOnce.insert(std::pair<char*, Effect_Once*>("move_y", new Effect_Pos_MovetoY()));
	effectsOnce.insert(std::pair<char*, Effect_Once*>("size_h", new Effect_Size_Height()));
	//effectsOnce.insert(std::pair<char*, Effect_Once*>("size_w", new Effect_Size_Width()));
	//how to use:
	// effectsOnce["move_y"]->addObject(m_NotePrefab,2);

}

void LevelManager::update(float deltaTime)
{
	soundSystem->update();
	m_Player->UpdateRender(deltaTime);
	
	if (stats == GAME_STATS_PLAYING) {
		
		/////////
		//effects
		std::map<char*, Effect*>::iterator _it;
		_it = effects.begin();
		while (_it != effects.end())
		{
			_it->second->loop(deltaTime);
			_it++;
		}

		/////////
		//effects once
		std::map<char*, Effect_Once*>::iterator _it2;
		_it2 = effectsOnce.begin();
		while (_it2 != effectsOnce.end())
		{
			_it2->second->update(deltaTime);
			_it2++;
		}

		//effect list
		((Effect_ProcessBar*)effects["process_bar"])->setSongPos(soundSystem->getPositionInMs()*1.0f / soundSystem->getSongLengthInMs());
		if (_text_songInfo_delay >= 0) {
			_text_songInfo_delay += deltaTime;
			if (_text_songInfo_delay > 5) {
				_text_songInfo_delay = -1;
				effectsOnce["fade_out"]->addObject(m_text_songInfo);
			}
		}
		if (_text_message_delay >= 0) {
			_text_message_delay += deltaTime;
			if (_text_message_delay > 2) {
				_text_message_delay = -1;
				effectsOnce["fade_out"]->addObject(m_box_message);
				effectsOnce["fade_out"]->addObject(m_text_message);
				effectsOnce["size_h"]->addObject(m_box_message, 0);
			}
		}


		/////////
		//in play
		if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_PURESONG) {
			//彦恺，你来调参数
			m_Player->currentSize = m_Player->DefaultSize + 1500.0f * soundSystem->getSpectrumCurruentTime(7);
		}
		else if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_LEVEL) {//dspTIME refresh
			
			//path effects
			effects["noteSlide_UP"]->currents =
			effects["noteSlide_DOWN"]->currents =
			effects["noteSlide_LEFT"]->currents =
			effects["noteSlide_RIGHT"]->currents =
				MathHandle::ClampFloat(50, 128, (50 + 1000 * soundSystem->getSpectrumCurruentTime(2)));

			//other effects
			//slap
			if (beatsOfNextSlap >= 0 && beatsOfNextSlap < songPosInBeats) {
				//generate slap
				CSprite* slap = new CSprite("slap");
				slap->CloneSprite("effect_slap");
				slap->SetSpritePosition(0, 0);
				slap->SetSpriteLifeTime(2);
				slap->SpriteAlpha = 255;
				effectsOnce["fade_out"]->addObject(slap);
				beatsOfNextSlap = -1;
			}

			songPosition = soundSystem->getPositionInMs();

			songPosInBeats = (songPosition - playingLevel->songOffset) / (60000.0f / playingLevel->songTempo);

			//load NextClick
			if (nextHitObjectCur < playingLevel->beatmap.size() &&
				this->playingLevel->beatmap[nextHitObjectCur].getPosInBeat() <= beatsShownInAdvance + songPosInBeats) {

				if (playingLevel->beatmap[nextHitObjectCur].getType() == HIT_EFFECT) {
					beatsOfNextSlap = playingLevel->beatmap[nextHitObjectCur].getPosInBeat();
				}
				else 
				{
					//Instantiate( /* Music Note Prefab */);
					char tempName[10];
					sprintf(tempName, "note_%d", nextHitObjectCur);
					playingLevel->beatmap[nextHitObjectCur].bindSprite = new CSprite(tempName);
					std::string  currentSprite = "note_prefab";
					//check double
					if (nextHitObjectCur > 0 &&
						playingLevel->beatmap[nextHitObjectCur - 1].getType()!=HIT_EFFECT && 
						playingLevel->beatmap[nextHitObjectCur - 1].getPosInBeat() == playingLevel->beatmap[nextHitObjectCur].getPosInBeat() ||
						nextHitObjectCur < playingLevel->beatmap.size() - 1 && 
						playingLevel->beatmap[nextHitObjectCur + 1].getType()!=HIT_EFFECT&&
						playingLevel->beatmap[nextHitObjectCur + 1].getPosInBeat() == playingLevel->beatmap[nextHitObjectCur].getPosInBeat()) {
						currentSprite = "note_prefab_double";
					}
					if (playingLevel->beatmap[nextHitObjectCur].bindSprite->CloneSprite(currentSprite.c_str())) {

						//pathBuffer[0].push_back(this->playingLevel->beatmap[nextHitObjectCur]);
						int _I = 0;//"_I"用来确定方向
						switch (playingLevel->beatmap[nextHitObjectCur].getType()) {
						case HIT_UP:
							_I = 0; break;
						case HIT_RIGHT:
							_I = 1; break;
						case HIT_DOWN:
							_I = 2; break;
						case HIT_LEFT:
							_I = 3; break;
						default:
							_I = -1;
						}
						if (_I != -1)
							pathBuffer[_I].push_back(this->playingLevel->beatmap[nextHitObjectCur]);
					}
					
				}
				nextHitObjectCur++;
			}
			//checking end
			if (songPosition >= (int)(soundSystem->getSongLengthInMs()) - 200) {
				nextLevel();
			}
			//update notes positions and check miss
			for (int _I = 0; _I < 4; _I++) {
				for (int _J = 0; _J < pathBuffer[_I].size(); _J++) {
					
					pathBuffer[_I][_J].bindSprite->SetSpritePosition(
						MathHandle::LerpFloat(
							beatsSpawn,
							(m_Player->HitSize + m_Player->DefaultSize) / 4.0f,
							(beatsShownInAdvance - (pathBuffer[_I][_J].getPosInBeat() - songPosInBeats)) / beatsShownInAdvance
						)*(_I == 1 ? 1 : _I == 3 ? -1 : 0),
						MathHandle::LerpFloat(
							beatsSpawn,
							(m_Player->HitSize + m_Player->DefaultSize) / 4.0f,
							(beatsShownInAdvance - (pathBuffer[_I][_J].getPosInBeat() - songPosInBeats)) / beatsShownInAdvance
						)*(_I == 0 ? -1 : _I == 2 ? 1 : 0)
					);
					
				}
				////////////////////////////////////
				//判定！！在这里！！
				//对每一边的第一个元素进行判定
				if (pathBuffer[_I].size() > 0) {
					//到达底线
					if (pathBuffer[_I][0].getPosInMs() - songPosition < - HIT_CHECKTIME_MISS) {
						
						//Miss Event Here
						this->checkNote(false);
						
						
						//destroy
						pathBuffer[_I][0].bindSprite->DeleteSprite();
						pathBuffer[_I][0].bindSprite = NULL;
						std::vector<HitObject>::iterator it = pathBuffer[_I].begin();
						pathBuffer[_I].erase(it);
					}
				}
			}
		}
		else if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_CHAT) {
			//依晨你来写
			m_Player->currentSize = m_Player->DefaultSize + 1500.0f * soundSystem->getSpectrumCurruentTime(7);

		}
	}
}
//按键按下
void LevelManager::keyDown(const int iKey)
{
	if (iKey == KEY_R) {//test
		CSprite * a = new CSprite("title_img");
		a->SpriteAlpha = 255;
		effectsOnce["fade_out"]->addObject(a);
		m_Player->reset();
		this->playIndex = 0;
		this->playLevel(playlist[playIndex]);
		this->m_box_message->SetSpriteColorAlpha(this->m_box_message->SpriteAlpha=255);
		alertMessage("仅需要按下WASD或↑→↓←哦~");
		return;
	}
	if (iKey == KEY_P) {//test
		if(this->playingLevel->getLevelType()==GAME_LEVEL_TYPE_LEVEL)
			this->nextLevel();
		return;
	}
	if (iKey == KEY_O) {//test
		alertMessage("Hi");
		return;
	}
	HitObjectType type = HIT_UNDEFINE;
	int _I = -1;
	bool isHit = true;
	switch (iKey) {
	case KEY_UP:case KEY_W:
		type = HIT_UP;
		_I = 0;
		break;
	case KEY_DOWN:case KEY_S:
		type = HIT_DOWN;
		_I = 2;
		break;
	case KEY_LEFT:case KEY_A:
		type = HIT_LEFT;
		_I = 3;
		break;
	case KEY_RIGHT:case KEY_D:
		type = HIT_RIGHT;
		_I = 1;
		break;
	default:
		isHit = false;
	}

	if (stats == GAME_STATS_PLAYING) {//正在玩？
		if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_LEVEL) {//按键只在游戏、对话里面响应方向。
			//Level Mode
			m_Player->OnKeyPressed(type);//传入数据
			if (isHit) { 
				//音效
				soundSystem->playFX(SOUND_FX_CLICK); 
				//判定
				if (pathBuffer[_I].size() > 0) {
					if (MathHandle::AbsFloat(pathBuffer[_I][0].getPosInMs() - songPosition) < HIT_CHECKTIME_MISS) {
						//Hit Event Here
						
						this->checkNote(true);

						//flash effects
						effects["handleFlash"]->trigger();

						//destroy
						pathBuffer[_I][0].bindSprite->DeleteSprite();
						pathBuffer[_I][0].bindSprite = NULL;
						std::vector<HitObject>::iterator it = pathBuffer[_I].begin();
						pathBuffer[_I].erase(it);
					}
				}
			}
		}
		else if (playingLevel->getLevelType() == GAME_LEVEL_TYPE_CHAT) {
			//Chat Mode
			if (!this->nextDiag()) this->nextLevel();
			//依晨你来写
		}
		else {//PureSong Mode
			_nextdelay--;//防误触
			//再按一次跳过
			if (_nextdelay < 1) { this->nextLevel(); _nextdelay = 1; }
		}
	}
}

void LevelManager::playLevel(Level* level)
{
	//切换游戏状态
	this->stats = GAME_STATS_PASSING;

	/////
	//重置Level关卡的设置
	nextHitObjectCur = 0;
	for (int __I = 0; __I < 4; __I++) { 
		for (int __J = 0; __J < pathBuffer[__I].size(); __J++) {
			pathBuffer[__I][__J].bindSprite->DeleteSprite();
			pathBuffer[__I][__J].bindSprite = NULL;
		}
		this->pathBuffer[__I].clear(); 
	}

	/////
	//重置显示设置
	

	/////
	//重置音乐
	soundSystem->killPlaying();
	
	/////
	//重置chat对话框等元素
	this->m_textBox->SetSpriteColorAlpha(0);
	m_Player->combo_text->SetTextString("");
	/////
	//instantiate
	if (level->loadLevel()) {
		this->playingLevel = level;
		if (level->getLevelType() == GAME_LEVEL_TYPE_LEVEL) {
			//重置游戏内特效
			
			effects["noteSlide_UP"]->start(); 
			effects["noteSlide_DOWN"]->start(); 
			effects["noteSlide_LEFT"]->start(); 
			effects["noteSlide_RIGHT"]->start();
			effects["handleFlash"]->start();
			m_Player->start();
			beatsOfNextSlap = -1;
			beatsShownInAdvance = level->songTempo / 70.0f;

			effectsOnce["fade_in"]->addObject(m_Player->score_text);
		}
		else {
			effectsOnce["fade_out"]->addObject(m_Player->score_text);
			effects["noteSlide_UP"]->currents =
			effects["noteSlide_DOWN"]->currents =
			effects["noteSlide_LEFT"]->currents =
			effects["noteSlide_RIGHT"]->currents = 0;
			if (level->getLevelType() == GAME_LEVEL_TYPE_CHAT) {
				//加载Chat模式的必要信息
				this->currentDiagCur = 999;//infinity
				this->currentChatCur = -1;
				this->chatStage[0] = this->chatStage[1] = this->chatStage[2]= new CSprite("chr_blank");
				this->m_textBox->SetSpriteColorAlpha(100);
				m_textInner->SetTextString("");
			}
		}
		if (soundSystem->playMusic(level->getSongPath())) {
			this->stats = GAME_STATS_PLAYING;
			this->alertSongInfo(level->songName);
		}
		else {
			printf("playLevel Failed! retry..");
			playLevel(level);//tryAnain

		}
	}
	else printf("failed to play Level.");
		
}

void LevelManager::nextLevel() {
	if (playIndex < playlist.size() - 1) {
		playIndex++;
		playLevel(playlist[playIndex]);
	}
}

void LevelManager::checkNote(bool isHitted)
{
	if (isHitted) {
		m_Player->Hitted(1);
	}
	else {
		if (m_Player->getCombo() >= 100) 
			soundSystem->playFX(SOUND_FX_MISS);
		m_Player->Hitted(0);
	}
	if (m_Player->getHitCount() >= playingLevel->notenum) {
		std::string alertInfo = "";
		if (m_Player->getAcc() == 100.f) {
			alertInfo += "Full Combo!!   收听率：全球100%";
		}
		else {
			if (m_Player->getAcc() >= 90.f) {
				alertInfo += "太棒了！  收听率 : ";
			}
			else if (m_Player->getAcc() >= 80.f) {
				alertInfo += "很有潜力哦   收听率 : ";
			}
			else if (m_Player->getAcc() >= 70.f) {
				alertInfo += "勉勉强强~   收听率 : ";
			}
			else {
				alertInfo += "再接再厉！  收听率 : ";
			}
			alertInfo += std::to_string((int)m_Player->getAcc());
			alertInfo += ".";
			alertInfo += std::to_string((int)(m_Player->getAcc() * 100) % 100);
			alertInfo += " %";
		}
		alertMessage(alertInfo);
	}
}

bool LevelManager::nextDiag()
{
	if (currentChatCur >= 0 && 
		playingLevel->chats[currentChatCur].diags.size() > currentDiagCur) {
		//load next Diag text
		m_textInner->SetTextString(playingLevel->chats[currentChatCur].diags[currentDiagCur].c_str());
		currentDiagCur++;
		return true;
	}
	else {
		if ((int)playingLevel->chats.size() > currentChatCur+1) {
			//load next chat scene
			//+ available to insert CGs
			//reset
			currentChatCur++;
			if (!(this->chatStage[0] != NULL &&
				strcmp(this->chatStage[0]->GetName(), playingLevel->chats[currentChatCur].left_str.c_str())) == 0) {
				effectsOnce["fade_out"]->addObject(this->chatStage[0]);
				this->chatStage[0] = new CSprite(playingLevel->chats[currentChatCur].left_str.c_str());
				this->chatStage[0]->SpriteAlpha = 0;
			}
			if (!(this->chatStage[1] != NULL &&
				strcmp(this->chatStage[1]->GetName(), playingLevel->chats[currentChatCur].right_str.c_str())) == 0) {
				effectsOnce["fade_out"]->addObject(this->chatStage[1]);
				this->chatStage[1] = new CSprite(playingLevel->chats[currentChatCur].right_str.c_str());
				this->chatStage[1]->SpriteAlpha = 0;
			}
			if(playingLevel->chats[currentChatCur].onChating==-1){
				this->chatStage[2]= new CSprite(playingLevel->chats[currentChatCur].left_str.c_str());
				this->chatStage[2]->SpriteAlpha = 0;
				effectsOnce["move_x"]->addObject(this->chatStage[2], GAME_CHAT_CENTER);
				effectsOnce["fade_in"]->addObject(this->chatStage[2]);
			}
			else {
				effectsOnce["fade_out"]->addObject(this->chatStage[2]);

				effectsOnce["move_x"]->addObject(this->chatStage[0], GAME_CHAT_LEFT);
				effectsOnce["move_x"]->addObject(this->chatStage[1], GAME_CHAT_RIGHT);
				if (playingLevel->chats[currentChatCur].onChating == 0) {
					effectsOnce["fade_in"]->addObject(chatStage[0]);
					effectsOnce["fade_128"]->addObject(chatStage[1]);
				}
				else if(playingLevel->chats[currentChatCur].onChating == 1){
					effectsOnce["fade_128"]->addObject(chatStage[0]);
					effectsOnce["fade_in"]->addObject(chatStage[1]);
				}
				else {
					effectsOnce["fade_128"]->addObject(chatStage[0]);
					effectsOnce["fade_128"]->addObject(chatStage[1]);
				}
			}
			currentDiagCur = 0;

			return nextDiag();
		}
		else {
			effectsOnce["fade_out"]->addObject(this->chatStage[0]);
			effectsOnce["fade_out"]->addObject(this->chatStage[1]);
			m_textInner->SetTextString("");
			return false;
		}
	}
}

void LevelManager::alertSongInfo(std::string name)
{
	this->m_text_songInfo->SetTextString(name.c_str());
	_text_songInfo_delay = 0;
	effectsOnce["fade_in"]->addObject(this->m_text_songInfo);
}

void LevelManager::alertMessage(std::string info)
{
	if (_text_message_delay < 0) {
		this->m_text_message->SetTextString(info.c_str());
		_text_message_delay = 0;
		effectsOnce["size_h"]->addObject(this->m_box_message, 60);
		effectsOnce["fade_in"]->addObject(this->m_box_message);
		effectsOnce["fade_in"]->addObject(this->m_text_message);
	}
}
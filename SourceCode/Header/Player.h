#pragma once
#include "HitObject.h"
#include "CommonClass.h"
#include <iostream>
class Player {

public:
	//construtor
	Player();

	//handles
	CSprite *	handle_up;
    CSprite *	handle_right;
	CSprite *	handle_down;
	CSprite *	handle_left;

	//hit effects
	CSprite *	check_miss;
	CSprite *	check_great;
	CTextSprite*combo_text;

	CTextSprite*score_text;
	
	//optional Sizes
	const float HitSize = 160;
	const float DefaultSize = 128;
	//const float JudgeSize = 500;
	float currentSize=128;
	void reset() {
		this->score = this->_score = this->hitCount = 0;
	}
	void start() {
		this->combo = this->hitCount = this->miss = 0;
		check_miss->SpriteAlpha = check_great->SpriteAlpha = 0;
		currentSize = DefaultSize;
	}
	//insert Update from clicks
	void UpdateRender(float deltaTime);


	void OnKeyPressed(HitObjectType type);
	//计分相关
	void Hitted(int isHitted);
	int getCombo() { return this->combo; }
	int getHitCount() { return this->hitCount; }
	float getAcc() { 
		return (float)((int)((1.0f - this->miss * 1.0f / this->hitCount) * 10000)) / 100;
	}
private:
	//just set sprite size..
	void OnKeyAction(CSprite* obj);
	
	int hitCount = 0;
	int miss = 0;
	int combo = 0;
	int score = 0;
	int _score;
};

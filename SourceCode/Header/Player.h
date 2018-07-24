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

	//optional Sizes
	const float HitSize = 160;
	const float DefaultSize = 128;
	float currentSize=128;

	void start() {
		this->combo = 0;
		check_miss->SpriteAlpha = 0;
		check_great->SpriteAlpha = 0;
		currentSize = DefaultSize;
	}
	//insert Update from clicks
	void UpdateRender(float deltaTime);


	void OnKeyPressed(HitObjectType type);

	void Hitted(int isHitted);
private:
	//just set sprite size..
	void OnKeyAction(CSprite* obj);

	int combo = 0;
};

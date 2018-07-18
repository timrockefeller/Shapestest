#pragma once
#include "HitObject.h"
#include "CommonClass.h"
class Player {

public:
	//construtor
	Player();

	//handles
	CSprite *	handle_up;
    CSprite *	handle_right;
	CSprite *	handle_down;
	CSprite *	handle_left;

	//optional Sizes
	const float HitSize = 160;
	const float DefaultSize = 128;
	float currentSize=128;

	//insert Update from clicks
	void UpdateRender();


	void OnKeyPressed(HitObjectType type);

	void Hitted(int isHitted);
private:
	//just set sprite size..
	void OnKeyAction(CSprite* obj);

	int combo = 0;
};

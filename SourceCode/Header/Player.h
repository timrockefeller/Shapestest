#pragma once
#include "HitObject.h"
#include "CommonClass.h"
class Player {

public:
	CSprite *	handle_up;
    CSprite *	handle_right;
	CSprite *	handle_down;
	CSprite *	handle_left;

	const float HitSize = 160;

	const float DefaultSize = 128;

	void UpdateRender();

	Player();

	void OnKeyPressed(HitObjectType type);


	void OnKeyAction(CSprite* obj);
};

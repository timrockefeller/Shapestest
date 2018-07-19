#pragma once
#include <vector>
#include "../Effects.h"

class Effect_HandleFlash :public Effect {
private:
	int indexOfPresent=0;
	const float voyageSpeed = 2500.f;
	std::vector<CSprite*> copies;
public:
	Effect_HandleFlash();
	virtual void start();
	virtual void loop(float deltaTime);
	virtual void trigger();
};
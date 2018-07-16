#pragma once
#include "../Effects.h"

class Effect_ProcessBar :public Effect {

public:
	Effect_ProcessBar();
	virtual void start();
	
	virtual void loop();
	void setSongPos(float pos);
};
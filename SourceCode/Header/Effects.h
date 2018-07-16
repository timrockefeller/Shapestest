#pragma once
#include "CommonClass.h"
#include "MathHandle.h"
class  Effect {


public:

	float currents = 0;
	CSprite * transfrom=NULL;

	virtual void start() = 0;

	
	virtual void loop() = 0;
	

};
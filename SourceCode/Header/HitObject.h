#pragma once
﻿#pragma once
#include "CommonClass.h"
#define HIT_CHECKTIME_MISS 33.f
enum HitObjectType {
	HIT_UNDEFINE,
	HIT_UP,
	HIT_RIGHT,
	HIT_DOWN,
	HIT_LEFT,
	HIT_EFFECT
};
class HitObject{
private:
    float posInMs;
	float posInBeat;
	HitObjectType type;
public:
	HitObject();
	HitObject(float _posInBeat, HitObjectType _type);
	~HitObject();
    void setPosInMs(float ms);
	float getPosInMs();
	void setPosInBeat(float beat);
	float getPosInBeat();
	void setType(HitObjectType _type);
	HitObjectType getType();
	float getPosInBeatByBpm(float tempo,float offset);
	
	

	CSprite* bindSprite = NULL;
};
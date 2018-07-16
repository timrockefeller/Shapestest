#pragma once
#include "CommonClass.h"
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
	float getPosInMs(float ms);
	void setPosInBeat(float beat);
	float getPosInBeat();
	void setType(HitObjectType _type);
	HitObjectType getType();
	float getPosInBeatByBpm(float tempo,float offset);
	
	CSprite* bindSprite = NULL;
};
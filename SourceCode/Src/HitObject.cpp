#include "stdref.h"

HitObject::HitObject()
{
	posInMs = -1;
	posInBeat = -1;
	type = HIT_UNDEFINE;
}
HitObject::HitObject(float _posInBeat, HitObjectType _type) {
	this->posInBeat = _posInBeat;
	this->type = _type;
}
HitObject::~HitObject()
{
}

void HitObject::setPosInMs(float ms){
    this->posInMs = ms;
}

float HitObject::getPosInMs(float ms)
{
	return this->posInMs;
}

void HitObject::setPosInBeat(float beat)
{
	this->posInBeat = beat;
}

void HitObject::setType(HitObjectType _type)
{
	this->type = _type;
}

HitObjectType HitObject::getType()
{
	return type;
}

float HitObject::getPosInBeatByBpm(float tempo,float offset)
{
	this->posInMs;
	float secPerBeat = 60.f / tempo;
	this->posInBeat = (this->posInMs - offset) / (secPerBeat * 1000.f);
	return this->posInBeat;
}

float HitObject::getPosInBeat()
{
	return this->posInBeat;
}

#pragma once
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
	float getPosInBeatByBpm(float tempo,float offset);
};
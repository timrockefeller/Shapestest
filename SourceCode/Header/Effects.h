#pragma once
#include <vector>
#include "CommonClass.h"
#include "MathHandle.h"
class  Effect {
public:
	float currents = 0;
	CSprite * transfrom=NULL;
	virtual void start() = 0;
	virtual void loop(float deltaTime) = 0;
	virtual void trigger() = 0;
};


//highlevel Effect
class Effect_Once {
protected:
	std::vector<CSprite*> ctn;
	std::vector<float> spec;
public:
	//确认是否为空
	bool isCtnEmpty() {
		return ctn.size() > 0 ? false : true;
	}
	//添加元素
	void addObject(CSprite* child,float value=0) {
		if (child != NULL) {
			this->ctn.push_back(child);
			this->spec.push_back(value);
		}
	}
	//删除元素
	void eraseObject(int the) {
		std::vector<CSprite*>::iterator itC = ctn.begin();
		std::vector<float>::iterator itF = spec.begin();
		if (the < ctn.size()) {
			ctn.erase(itC + the);
			spec.erase(itF + the);
		}
	}
	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	
};
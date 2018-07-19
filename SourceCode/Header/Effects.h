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
	bool setVisible(bool isVisible) {
		if (this->transfrom != NULL) {
			this->transfrom->SetSpriteVisible(isVisible);
			return true;
		}
		return false;
	}
};


//highlevel Effect
class Effect_Once {
protected:
	std::vector<CSprite*> ctn;
	std::vector<float> spec;
	std::vector<int> counter;
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
			this->counter.push_back(0);
		}
	}
	//删除元素
	void eraseObject(int the) {
		if (the < ctn.size()) {
			std::vector<CSprite*>::iterator itC = ctn.begin();
			std::vector<float>::iterator itF = spec.begin();
			std::vector<int>::iterator itG = counter.begin();
			ctn.erase(itC + the);
			spec.erase(itF + the);
			counter.erase(itG + the);
		}
	}
	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
};
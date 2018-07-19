#pragma once 
#include "Effects.h"
//Fade out and delete the curent object
class Effect_FadeOut :public Effect_Once {
public:
	virtual void start() {}
	virtual void update(float deltaTime) {
		for (int _I = 0; _I < ctn.size(); _I++) {
			int a = ctn[_I]->GetSpriteColorAlpha();
			ctn[_I]->SpriteAlpha = (int)MathHandle::LerpFloat(ctn[_I]->SpriteAlpha, 0, 0.05);
			ctn[_I]->SetSpriteColorAlpha(ctn[_I]->SpriteAlpha);
			if (ctn[_I]->SpriteAlpha < 5) {
				ctn[_I]->SpriteAlpha = 0;
				ctn[_I]->SetSpriteColorAlpha(0);
				eraseObject(_I);
			}
		}
	}
	
};

//Fade in and delete the curent object
class Effect_FadeIn :public Effect_Once {
public:
	virtual void start() {}
	virtual void update(float deltaTime) {
		for (int _I = 0; _I < ctn.size(); _I++) {
			counter[_I]++;
			ctn[_I]->SpriteAlpha = MathHandle::LerpFloat(ctn[_I]->SpriteAlpha, 255, 0.05);
			ctn[_I]->SetSpriteColorAlpha(ctn[_I]->SpriteAlpha);
			if (ctn[_I]->SpriteAlpha > 250 || counter[_I]>20/*超过40帧(将近一秒)*/) {
				ctn[_I]->SpriteAlpha = 255;
				ctn[_I]->SetSpriteColorAlpha(255);
				eraseObject(_I);
			}
		}
	}
};

//Fade 128 and delete the curent object
class Effect_Fade128 :public Effect_Once {
public:
	virtual void start() {}
	virtual void update(float deltaTime) {
		for (int _I = 0; _I < ctn.size(); _I++) {
			ctn[_I]->SpriteAlpha = (int)MathHandle::LerpFloat(ctn[_I]->SpriteAlpha, 128, 0.05);
			ctn[_I]->SetSpriteColorAlpha(ctn[_I]->SpriteAlpha);
			if (MathHandle::AbsFloat(ctn[_I]->GetSpriteColorAlpha() - 5) < 128.0f) {
				ctn[_I]->SpriteAlpha = 128;
				ctn[_I]->SetSpriteColorAlpha(128);
				eraseObject(_I);
			}
		}
	}
};
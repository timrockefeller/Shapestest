#pragma once 
#include "Effects.h"
//Fade out and delete the curent object
class Effect_FadeOut :public Effect_Once {
public:
	virtual void start() {}
	virtual void update(float deltaTime) {
		for (int _I = 0; _I < ctn.size(); _I++) {
			ctn[_I]->SetSpriteColorAlpha((int)MathHandle::LerpFloat(ctn[_I]->GetSpriteColorAlpha(),0,0.01));
			if (ctn[_I]->GetSpriteColorAlpha() < 5) {
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
			ctn[_I]->SetSpriteColorAlpha(MathHandle::LerpFloat(ctn[_I]->GetSpriteColorAlpha(), 255, 0.01));
			if (ctn[_I]->GetSpriteColorAlpha() < 5) {
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
			ctn[_I]->SetSpriteColorAlpha((int)MathHandle::LerpFloat(ctn[_I]->GetSpriteColorAlpha(), 128, 0.01));
			if (MathHandle::AbsFloat(ctn[_I]->GetSpriteColorAlpha() - 5) < 128.0f) {
				ctn[_I]->SetSpriteColorAlpha(128);
				eraseObject(_I);
			}
		}
	}
};
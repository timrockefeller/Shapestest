#pragma once
#include "Effects.h"

class Effect_Size_Width :public Effect_Once {
public :
	virtual void start() {}
	virtual void update(float deltaTime) {
		for (int _I = 0; _I < ctn.size(); _I++) {
			counter[_I]++;
			ctn[_I]->SetSpriteWidth(MathHandle::LerpFloat(ctn[_I]->GetSpriteWidth(), spec[_I], 0.05));
			if (MathHandle::AbsFloat(ctn[_I]->GetSpriteWidth()- spec[_I]) < 1|| counter[_I]>40) {
				ctn[_I]->SetSpriteWidth(spec[_I]);
				eraseObject(_I);
			}
		}
	}
};
class Effect_Size_Height :public Effect_Once {
public:
	virtual void start() {}
	virtual void update(float deltaTime) {
		for (int _I = 0; _I < ctn.size(); _I++) {
			counter[_I]++;
			ctn[_I]->SetSpriteHeight(MathHandle::LerpFloat(ctn[_I]->GetSpriteHeight(), spec[_I], 0.1));
			if (MathHandle::AbsFloat(ctn[_I]->GetSpriteHeight() - spec[_I]) < 1|| counter[_I]>60) {
				ctn[_I]->SetSpriteHeight(spec[_I]);
				eraseObject(_I);
			}
		}
	}
};
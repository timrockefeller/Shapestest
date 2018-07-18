#pragma once
#include "Effects.h"

class Effect_Size_Width :public Effect_Once {
public :
	virtual void start() {}
	virtual void update(float deltaTime) {
		for (int _I = 0; _I < ctn.size(); _I++) {
			ctn[_I]->SetSpriteWidth((int)MathHandle::LerpFloat(ctn[_I]->GetSpriteWidth(), spec[_I], 0.01));
			if (MathHandle::AbsFloat(ctn[_I]->GetSpriteWidth()- spec[_I]) < 1) {
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
			ctn[_I]->SetSpriteHeight((int)MathHandle::LerpFloat(ctn[_I]->GetSpriteHeight(), spec[_I], 0.01));
			if (MathHandle::AbsFloat(ctn[_I]->GetSpriteHeight() - spec[_I]) < 1) {
				ctn[_I]->SetSpriteHeight(spec[_I]);
				eraseObject(_I);
			}
		}
	}
};
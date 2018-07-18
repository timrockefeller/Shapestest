#pragma once 
#include "Effects.h"

//moveto X
class Effect_Pos_MovetoX :public Effect_Once {
public:
	virtual void start() {}
	virtual void update(float deltaTime) {
		for (int _I = 0; _I < ctn.size(); _I++) {
			ctn[_I]->SetSpritePositionX((int)MathHandle::LerpFloat(ctn[_I]->GetSpritePositionX(), spec[_I], 0.01));
			if (MathHandle::AbsFloat(ctn[_I]->GetSpritePositionX() - spec[_I]) < 1) {
				ctn[_I]->SetSpritePositionX(spec[_I]);
				eraseObject(_I);
			}
		}
	}
};
//moveto Y
class Effect_Pos_MovetoY :public Effect_Once {
public:
	virtual void start() {}
	virtual void update(float deltaTime) {
		for (int _I = 0; _I < ctn.size(); _I++) {
			ctn[_I]->SetSpritePositionY((int)MathHandle::LerpFloat(ctn[_I]->GetSpritePositionY(), spec[_I], 0.01));
			if (MathHandle::AbsFloat(ctn[_I]->GetSpritePositionX() - spec[_I]) < 1) {
				ctn[_I]->SetSpritePositionY(spec[_I]);
				eraseObject(_I);
			}
		}
	}
};
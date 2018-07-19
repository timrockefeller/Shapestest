#include "Effect_handleFlash.h"

Effect_HandleFlash::Effect_HandleFlash()
{
	this->transfrom = new CSprite("effect_handleFlash_UP");
}

void Effect_HandleFlash::start()
{
	this->indexOfPresent = 0;
	//Çå¿ÕÄÚºË
	for (int _I = 0; _I < this->copies.size(); _I++) {
		this->copies[_I]->DeleteSprite();
	}
	this->copies.clear();
	std::vector<CSprite*>(this->copies).swap(this->copies);
}

void Effect_HandleFlash::loop(float deltaTime)
{
	for (int _I = 0; _I < this->copies.size(); _I++) {
		float te = this->copies[_I]->GetSpriteWidth() + voyageSpeed * deltaTime;
		if (te > voyageSpeed) {
			this->copies[_I]->DeleteSprite();
			std::vector<CSprite*>::iterator it = this->copies.begin();
			this->copies.erase(it + _I);
		}
		else {
			this->copies[_I]->SetSpriteWidth(te);
			this->copies[_I]->SetSpriteHeight(te);
		}
	}
}

void Effect_HandleFlash::trigger()
{
	
	char tempName[128];
	sprintf(tempName, "effect_handleFlash_UP_%d", indexOfPresent);
	CSprite* clones = new CSprite(tempName);
	if (clones->CloneSprite("effect_handleFlash_UP")) {
		this->copies.push_back(clones);
		indexOfPresent++;
	}
}

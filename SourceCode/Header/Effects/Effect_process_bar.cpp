#include "Effect_process_bar.h"

Effect_ProcessBar::Effect_ProcessBar() {

	this->transfrom = new CSprite("process_bar");
}

void Effect_ProcessBar::start()
{
	
}

void Effect_ProcessBar::loop(float deltaTime)
{
	transfrom->SetSpriteWidth(MathHandle::LerpFloat(transfrom->GetSpriteWidth(), currents, 0.02f));
}

void Effect_ProcessBar::setSongPos(float pos)
{
	this->currents = pos * 1600;
}

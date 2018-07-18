#include "Effect_note_slide.h"

Effect_NoteSlide_Up::Effect_NoteSlide_Up()
{
	this->transfrom = new CSprite("effect_noteSlide_UP");
}

void Effect_NoteSlide_Up::loop(float deltaTime)
{
	this->transfrom->SetSpriteWidth(MathHandle::LerpFloat(this->transfrom->GetSpriteWidth(),currents,0.01));
}

Effect_NoteSlide_Down::Effect_NoteSlide_Down()
{
	this->transfrom = new CSprite("effect_noteSlide_DOWN");
}

void Effect_NoteSlide_Down::loop(float deltaTime)
{
	this->transfrom->SetSpriteWidth(MathHandle::LerpFloat(this->transfrom->GetSpriteWidth(), currents, 0.01));
}

Effect_NoteSlide_Right::Effect_NoteSlide_Right()
{
	this->transfrom = new CSprite("effect_noteSlide_RIGHT");
}

void Effect_NoteSlide_Right::loop(float deltaTime)
{
	this->transfrom->SetSpriteHeight(MathHandle::LerpFloat(this->transfrom->GetSpriteHeight(), currents, 0.01));
}



Effect_NoteSlide_Left::Effect_NoteSlide_Left()
{
	this->transfrom = new CSprite("effect_noteSlide_LEFT");
}

void Effect_NoteSlide_Left::loop(float deltaTime)
{
	this->transfrom->SetSpriteHeight(MathHandle::LerpFloat(this->transfrom->GetSpriteHeight(), currents, 0.01));
}

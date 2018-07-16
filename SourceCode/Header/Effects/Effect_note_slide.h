#pragma once
#include "../Effects.h";


class Effect_NoteSlide_Up :public Effect {
public:
	Effect_NoteSlide_Up();
	virtual void start() {}
	virtual void loop();
};
class Effect_NoteSlide_Down :public Effect {
public:
	Effect_NoteSlide_Down();
	virtual void start() {}

	virtual void loop();
};
class Effect_NoteSlide_Right :public Effect {
public:
	Effect_NoteSlide_Right();
	virtual void start() {}

	virtual void loop();
};
class Effect_NoteSlide_Left :public Effect {
public:
	Effect_NoteSlide_Left();
	virtual void start() {}
	virtual void loop();
};
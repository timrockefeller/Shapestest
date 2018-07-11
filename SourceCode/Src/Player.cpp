#include "Player.h"
#include "HitObject.h"
#include "MathHandle.h"
void Player::UpdateRender()
{
	handle_up->SetSpriteHeight(MathHandle::LerpDouble(handle_up->GetSpriteHeight(),DefaultSize,0.01));
	handle_up->SetSpriteWidth(MathHandle::LerpDouble(handle_up->GetSpriteWidth(), DefaultSize, 0.01));

	handle_right->SetSpriteHeight(MathHandle::LerpDouble(handle_right->GetSpriteHeight(), DefaultSize, 0.01));
	handle_right->SetSpriteWidth(MathHandle::LerpDouble(handle_right->GetSpriteWidth(), DefaultSize, 0.01));
	
	handle_down->SetSpriteHeight(MathHandle::LerpDouble(handle_down->GetSpriteHeight(), DefaultSize, 0.01));
	handle_down->SetSpriteWidth(MathHandle::LerpDouble(handle_down->GetSpriteWidth(), DefaultSize, 0.01));
	
	handle_left->SetSpriteHeight(MathHandle::LerpDouble(handle_left->GetSpriteHeight(), DefaultSize, 0.01));
	handle_left->SetSpriteWidth(MathHandle::LerpDouble(handle_left->GetSpriteWidth(), DefaultSize, 0.01));
}

Player::Player() {
	handle_up = new CSprite("Handle_UP");
	handle_right = new CSprite("Handle_RIGHT");
	handle_left = new CSprite("Handle_LEFT");
	handle_down = new CSprite("Handle_DOWN");
}

void Player::OnKeyPressed(HitObjectType type)
{
	switch (type) {
	case HIT_UP:
		this->OnKeyAction(handle_up);;
		break;
	case HIT_DOWN:
		this->OnKeyAction(handle_down); 
		break;
	case HIT_LEFT:
		this->OnKeyAction(handle_left); 
		break;
	case HIT_RIGHT:
		this->OnKeyAction(handle_right); 
		break;
	}
}

void Player::OnKeyAction(CSprite * obj)
{
	obj->SetSpriteHeight(HitSize);
	obj->SetSpriteWidth(HitSize);
}

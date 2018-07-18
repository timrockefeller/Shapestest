#include "Player.h"
#include "HitObject.h"
#include "MathHandle.h"
void Player::UpdateRender()
{
	handle_up->SetSpriteHeight((float)MathHandle::LerpDouble(handle_up->GetSpriteHeight(), currentSize, 0.01f));
	handle_up->SetSpriteWidth((float)MathHandle::LerpDouble(handle_up->GetSpriteWidth(), currentSize, 0.01f));

	handle_right->SetSpriteHeight((float)MathHandle::LerpDouble(handle_right->GetSpriteHeight(), currentSize, 0.01f));
	handle_right->SetSpriteWidth((float)MathHandle::LerpDouble(handle_right->GetSpriteWidth(), currentSize, 0.01f));
	
	handle_down->SetSpriteHeight((float)MathHandle::LerpDouble(handle_down->GetSpriteHeight(), currentSize, 0.01f));
	handle_down->SetSpriteWidth((float)MathHandle::LerpDouble(handle_down->GetSpriteWidth(), currentSize, 0.01f));
	
	handle_left->SetSpriteHeight((float)MathHandle::LerpDouble(handle_left->GetSpriteHeight(), currentSize, 0.01f));
	handle_left->SetSpriteWidth((float)MathHandle::LerpDouble(handle_left->GetSpriteWidth(), currentSize, 0.01f));
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

void Player::Hitted(int isHitted)
{
	if (isHitted > 0) {
		this->combo++;
	}
	else {
		this->combo = 0;
		
	}
}

void Player::OnKeyAction(CSprite * obj)
{
	obj->SetSpriteHeight(HitSize);
	obj->SetSpriteWidth(HitSize);
}

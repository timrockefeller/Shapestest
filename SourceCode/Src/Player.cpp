#include "Player.h"
#include "HitObject.h"
#include "MathHandle.h"
void Player::UpdateRender(float deltaTime)
{
	handle_up->SetSpriteHeight((float)MathHandle::LerpDouble(handle_up->GetSpriteHeight(), currentSize, 0.01f));
	handle_up->SetSpriteWidth((float)MathHandle::LerpDouble(handle_up->GetSpriteWidth(), currentSize, 0.01f));

	handle_right->SetSpriteHeight((float)MathHandle::LerpDouble(handle_right->GetSpriteHeight(), currentSize, 0.01f));
	handle_right->SetSpriteWidth((float)MathHandle::LerpDouble(handle_right->GetSpriteWidth(), currentSize, 0.01f));
	
	handle_down->SetSpriteHeight((float)MathHandle::LerpDouble(handle_down->GetSpriteHeight(), currentSize, 0.01f));
	handle_down->SetSpriteWidth((float)MathHandle::LerpDouble(handle_down->GetSpriteWidth(), currentSize, 0.01f));
	
	handle_left->SetSpriteHeight((float)MathHandle::LerpDouble(handle_left->GetSpriteHeight(), currentSize, 0.01f));
	handle_left->SetSpriteWidth((float)MathHandle::LerpDouble(handle_left->GetSpriteWidth(), currentSize, 0.01f));


	
	//alpha of check objs
	check_great->SetSpriteColorAlpha(check_great->SpriteAlpha);
	check_miss->SetSpriteColorAlpha(check_miss->SpriteAlpha);
	check_great->SpriteAlpha = MathHandle::ClampInt(0, 255, check_great->SpriteAlpha - 2);
	check_miss->SpriteAlpha = MathHandle::ClampInt(0, 255, check_miss->SpriteAlpha - 2);
	_score = MathHandle::LerpInt(_score, score, 0.05);
	score_text->SetTextValue(_score);
}

Player::Player() {
	handle_up = new CSprite("Handle_UP");
	handle_right = new CSprite("Handle_RIGHT");
	handle_left = new CSprite("Handle_LEFT");
	handle_down = new CSprite("Handle_DOWN");

	check_great = new CSprite("check_great");
	check_miss = new CSprite("check_miss");
	check_great->SpriteAlpha = check_miss->SpriteAlpha= 0;

	combo_text = new CTextSprite("combo_text");
	score_text = new CTextSprite("score_text");
	_score = score = combo = 0;
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
	this->hitCount++;
	if (isHitted > 0) {
		this->combo++;
		score += (combo / 10 + 1) + (combo / 100 + 1)*20;
		if (combo >= 5) {
			char b[10];
			sprintf_s(b, "%dx", combo);
			combo_text->SetTextString(b);
		}
		else {
			combo_text->SetTextString("");
		}
		check_great->SpriteAlpha = 250;
		check_miss->SpriteAlpha = MathHandle::ClampInt(0, 20, check_great->SpriteAlpha);
	}
	else {
		this->combo = 0;
		this->miss++;
		combo_text->SetTextString("");
		check_miss->SpriteAlpha = 200;
		check_great->SpriteAlpha = MathHandle::ClampInt(0, 20, check_great->SpriteAlpha);
	}
}

void Player::OnKeyAction(CSprite * obj)
{
	obj->SetSpriteHeight(HitSize);
	obj->SetSpriteWidth(HitSize);
}
